#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>


int sock(int port){
	int fd,err;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets. \n");
		return -1;
	}

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(fd,(struct sockaddr *) &addr,sizeof(struct sockaddr_in));
    if (err<0) {
        printf("fehler  beim bind!");
        return -2;
    }
printf("ip: %s!\n",inet_ntoa(addr.sin_addr));
	return fd;
}

int lesen(int fdcl){
    int msgsize,fall;
    fall=0;
    char nachri[64];
    msgsize=read(fdcl,nachri,sizeof(nachri));
    if(msgsize<0){
        printf("error beim lesen,verbindung getrennt \n");
        close(fdcl);
        return -3;

    }
    if(!strcmp(nachri,"exit")){
        printf("Admin beendet den server \n");
        fall=-4;
    }
    else if(!strcmp(nachri,"einzahlen")){
        printf("client will einzahlen \n");
        fall=-1;
    }
    else if(!strcmp(nachri,"abheben")){
        printf("client will abheben  \n");
        fall=-2;
    }
    else if(!strcmp(nachri,"abbrechen")){
        printf("client versucht verbindung zu beenden  \n");
        return -3;
    }
    else{
        fall=atoi(nachri);
    }


    return fall;
}




int main(int args,char* Argv[]){
    int port,err,fd,fdcl,money,fall,betrag;
    char moneystr[64];
    char ans[128];
    socklen_t addrlen;
    struct sockaddr_in addr;
    port=atoi(Argv[1]);
    addrlen=sizeof(struct sockaddr_in);
    fd=sock(port);
    money=0;
    err=listen(fd,1);
    if(err<0){
        printf("problem beim listen! \n");
        close(fd);
        return -1;
    }


    while(fall!=(-4)){
    printf("warte auf verbindung ... \n");
    fall=0;
    fdcl=accept(fd,(struct sockaddr *) &addr,&addrlen);
    printf("verbunden mit: %s\n",inet_ntoa(addr.sin_addr));

    while(fall!=-3 && fall!=-4){
        sprintf(moneystr, "%i", money);
        err=write(fdcl,moneystr,sizeof(moneystr));
        fall=lesen(fdcl);
        if(fall==-1){
            betrag=lesen(fdcl);
            if(betrag>=0){
                money+=betrag;
                printf("neuer betrag: %i!\n",money);
                sprintf(ans, "ERFOLG! %i eingezahlt!", betrag);
                write(fdcl,ans,sizeof(ans));
            }
            else{
                sprintf(ans, "ERROR!,betrag <0");
                write(fdcl,ans,sizeof(ans));
                fall=0;
            }

        }
        else if(fall==-2){
           betrag=lesen(fdcl);

            if(betrag>=0){
                if(betrag <=money){
                    money-=betrag;
                    printf("neuer betrag: %i!\n",money);
                    sprintf(ans, "ERFOLG! %i abgehoben", betrag);
                    write(fdcl,ans,128*sizeof(char));
                }
                else{
                    sprintf(ans, "ERROR,betrag muss kleiner sein als guthabe: %i", money);
                    write(fdcl,ans,128*sizeof(char));
                }

            }
            else{
                sprintf(ans, "ERROR!,betrag <0");
                write(fdcl,ans,sizeof(ans));
                fall=0;
            }
        }
        else{
            close(fdcl);
            printf("verbindung beendet! \n");
        }
    }
}
    close(fd);
    return 0;
}
