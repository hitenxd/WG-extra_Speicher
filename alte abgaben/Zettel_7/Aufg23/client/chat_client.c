#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int sock(){

	int fd;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets. \n");
		return -1;
	}

	return fd;
}



int verbinden(int fd, char* host, int port){
	printf("baue verbindung auf zu: \n Webserver %s auf...\n", host);
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr  = inet_addr(host);
	printf("vebrindungsaufbau...\n");
	if((connect(fd, (struct sockaddr*)&addr, sizeof(addr))<0)){
		printf("Fehler beim connecten\n");
		return -1;
	}

	printf("#verbindung erfolgreich\n");
	return 0;
}




int beende(int fd){
	int err;

	err = close(fd);

	if(err == -1){
		printf("fehler beim schließen\n");
		return -1;
	}

	printf("###Verbindung getrennt###\n");
	return 0;
}

int schreiben(int fd){
	int err;
    err=0;
	//err=read(fd,recmsg,sizeof(recmsg));

    if(err<0){
        printf("ERROR! beim lesen des kontostand");
        return 0;
	}
	return 0;

}

void msg_empf(char* msg){
	printf("%s \n",msg);
}
int main(int argc,char* argv[]){
    char myname[32];
    char myip[15];
    char hostip[15];
    char msg[256];
    char tmp_msg[256];
	int fd,done,err,res,i;
	socklen_t myaddrlen;
    int defport=4711;
    struct sockaddr_in myaddr;
    fd_set cset;
    done=1;
    sprintf(myname,"noname");
    sprintf(msg," ");
    sprintf(tmp_msg," ");
    for(i=0;i<256;i++){
        msg[i]='\0';
        tmp_msg[i]='\0';
    }
    if(argc==2){
        sprintf(myname,"%s",argv[1]);
    }

	printf("IP eingeben: \n");
	scanf("%s",hostip);

	fd = sock();
	if(!verbinden(fd,hostip,defport)){
        myaddrlen=sizeof(myaddr);
        err=getsockname(fd, (struct sockaddr *) &myaddr, &myaddrlen);
        sprintf(myip,"%s",inet_ntoa(myaddr.sin_addr));
		while(done){
            FD_ZERO(&cset);
            FD_SET(fd, &cset);
            FD_SET(fileno(stdin), &cset);
            res=select(fd+1,&cset,NULL,NULL,NULL);
            if(res>0){
            if(FD_ISSET(fileno(stdin),&cset)){
                for(i=0;i<256;i++){
                    msg[i]='\0';
                    tmp_msg[i]='\0';
                }
                err=read(STDIN_FILENO,tmp_msg,sizeof(tmp_msg));
                if(err<=0){
                    printf("error beim lesen der eingegebenen msg\n");
                    beende(fd);
                    return -1;
                }
                sprintf(msg,"%s: %s - %s",myname,myip,tmp_msg);
                err=write(fd,msg,sizeof(msg));
                if(err<=0){
                    printf("error! nachricht nicht gesendet - beende!\n");
                    beende(fd);
                    return -1;
                }

            }
            if(FD_ISSET(fd,&cset)){
                    for(i=0;i<256;i++){
                        msg[i]='\0';
                    }

                err=read(fd,msg,sizeof(msg));
                if(err<=0){
                    printf("error! nachricht nicht erhalten - beende! \n");
                    beende(fd);
                    return -1;
                }
                else{
                    msg_empf(msg);

                }
            }
            }

		}
		beende(fd);
	}
	return 0;
}

