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


int main(int argc,char *argv[]){
    int gofirst=0;
    int fdempf=sockempf();
    int fdsend=socksend();
    int port,err,i;
    char ip[15];
    char msg[256];
    struct sockaddr_in sendaddr;


    printf("gib die ip ein\n");
    scanf("%s",ip);
    printf("gib den port ein\n");
    scanf("%i",&port);
    sendaddr.sin_family = AF_INET;
    sendaddr.sin_port = htons(port);
    sendaddr.sin_addr.s_addr = htonl(inet_addr(ip));
    if(argc==2){
        if(!strcmp(argv[1],"1")){
            gofirst=1;
            printf("du sendest zuerst\n");
        }
        else if(!strcmp(argv[1],"0")){
            printf("du erhälst zuerst eine nachricht\n");
            gofirst=0;
        }
        else{
            printf("unbekannter input - 1 für anfangen mit senden 0 für anfangen mit erhalten - beende\n");
            return -1;
        }
        while(1){
            for(i=0;i<256;i++){
                msg[i]='\0';
            }
            if(gofirst){

                err=read(fileno(stdin),msg,sizeof(msg));
                if(err<=0){
                    printf("cant read stdin\n");
                    close(fdempf);
                    close(fdsend);
                    return -1;
                }

                else{
                    err=sendto(fdsend,msg,sizeof(msg),0, (struct sockaddr*) &sendaddr, sizeof(sendaddr));
                    printf("send %s to %s:%i\n",msg,inet_ntoa(sendaddr.sin_addr),ntohs(sendaddr.sin_port));
                    if(err<=0){
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
                if(err<=0){
                    printf("error beim erhalten einer nachricht");
                }
                printf("%s\n",msg);
                gofirst=1;

            }


        }
    }
    else{
        printf("kein input!\n");
        close(fdempf);
        close(fdsend);
        return -1;
    }
    close(fdempf);
    close(fdsend);
    return 0;
}
