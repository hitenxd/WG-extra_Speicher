#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

int sockempf(){
	int fd,err;
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets. \n");
		return -1;
	}

    struct sockaddr_in addr;
    struct sockaddr_in myaddr;
    socklen_t myaddrlen=sizeof(myaddr);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(fd,(struct sockaddr *) &addr,sizeof(struct sockaddr_in));
    if (err<0) {
        printf("fehler  beim bind!");
        return -2;
    }
    getsockname(fd,(struct sockaddr *)&myaddr,&myaddrlen);
    printf("ip: %s port: %i!\n",inet_ntoa(myaddr.sin_addr),htons(myaddr.sin_port));
	return fd;
}

int socksend(){
    int fd;
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets. \n");
		return -1;
	}
	return fd;
}


int main(){
    int gofirst=0;
    int fdempf=sockempf();
    int fdsend=socksend();
    int port,err,i,oflags;
    char ip[15];
    char msg[256];
    struct sockaddr_in sendaddr;
    struct timeval delay;


    printf("gib die ip ein\n");
    scanf("%s",ip);
    printf("gib den port ein\n");
    scanf("%i",&port);
    sendaddr.sin_family = AF_INET;
    sendaddr.sin_port = htons(port);
    sendaddr.sin_addr.s_addr = htonl(inet_addr(ip));
    oflags = fcntl(fileno(stdin), F_GETFL, 0);
    fcntl(fileno(stdin), F_SETFL,oflags | O_NONBLOCK);
    oflags = fcntl(fdempf, F_GETFL, 0);
    fcntl(fdempf, F_SETFL,oflags | O_NONBLOCK);
    oflags = fcntl(fdsend, F_GETFL, 0);
    fcntl(fdsend, F_SETFL,oflags | O_NONBLOCK);
    gofirst=1;
    while(1){
        delay.tv_sec=1;
        delay.tv_usec=0;

            for(i=0;i<256;i++){
                msg[i]='\0';
            }
            if(gofirst){

                err=read(fileno(stdin),msg,sizeof(msg));

                if (errno != EWOULDBLOCK){
                    printf("cant read stdin\n");
                    close(fdempf);
                    close(fdsend);
                    return -1;

                }
                else{
                    if(err>0){
                        err=sendto(fdsend,msg,sizeof(msg),0, (struct sockaddr*) &sendaddr, sizeof(sendaddr));
                        printf("send %s to %s:%i\n",msg,inet_ntoa(sendaddr.sin_addr),ntohs(sendaddr.sin_port));
                    }
                    else if (errno != EWOULDBLOCK){
                        printf("cant send msg: %s\n",msg);
                        close(fdempf);
                        close(fdsend);
                        return -1;
                    }

                }
                gofirst=0;
            }
            else{
                err=recvfrom(fdempf,msg,sizeof(msg),0, NULL, NULL);
                if (errno != EWOULDBLOCK){
                    printf("error beim erhalten einer nachricht");
                    close(fdempf);
                    close(fdsend);
                    return -1;
                }

                if(err>0){
                    printf("%s\n",msg);
                }
                gofirst=1;

            }

        select(0,NULL,NULL,NULL,&delay);
        }
    close(fdempf);
    close(fdsend);
    return 0;
}
