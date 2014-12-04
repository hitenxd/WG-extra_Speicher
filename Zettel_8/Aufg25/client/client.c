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
#include <ctype.h>


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


int main(int argc,char* argv[]){
    fd_set cset,altset;
    int fd,Port,done,konto,i,guthaben,betrag,gotans,err;
	char msg[64];
	char *host=malloc(15*sizeof(char));
	printf("IP eingeben: \n");
	scanf("%s",host);
    done=0;
    konto=-1;
    betrag=0;
    guthaben=-1;
	printf("\nPort eingeben: ");
	scanf("%i",&Port);
	fd = sock();

	if(!verbinden(fd,host,Port)){
        printf("wähle ein konto zum bearbeiten(nur die zahl eingeben!)\n");
		while(konto==-1){
            FD_ZERO(&cset);
            FD_SET(fd, &cset);
            FD_SET(fileno(stdin), &cset);
            select(fd+1,&cset,NULL,NULL,NULL);
            if(FD_ISSET(fileno(stdin), &cset)){
                for(i=0;i<64;i++){
                    msg[i]='\0';
                }
                read(fileno(stdin),msg,sizeof(msg));
                if(!strcmp(msg,"abbrechen\n")){
                    beende(fd);
                    free(host);
                    return 0;
                }
                    write(fd,msg,sizeof(msg));
                    for(i=0;i<64;i++){
                        msg[i]='\0';
                    }
                    gotans=0;
                    while(!gotans){
                        FD_ZERO(&altset);
                        FD_SET(fd, &altset);
                        select(fd+1,&altset,NULL,NULL,NULL);
                        if(FD_ISSET(fd,&altset)){
                            read(fd,msg,sizeof(msg));
                            konto=atoi(msg);
                            gotans=1;
                        }
                    }

                    if(konto==-1){
                        printf("konto nicht verfügbar, versuch ein anderes \n");
                    }


            }
            if(FD_ISSET(fd,&cset)){
                for(i=0;i<64;i++){
                    msg[i]='\0';
                }
                err=read(fd,msg,sizeof(msg));
                if(err<=0){
                    printf("verbindung zum server verloren - beende\n");
                    beende(fd);
                    free(host);
                    return -1;
                }

                printf("server: %s \n",msg);
            }

		}
        printf("greife auf konto zu - warte auf guthaben\n");
        while(guthaben<0){
            FD_ZERO(&cset);
            FD_SET(fd, &cset);
            select(fd+1,&cset,NULL,NULL,NULL);
            if(FD_ISSET(fd,&cset)){
                for(i=0;i<64;i++){
                    msg[i]='\0';
                }
                err=read(fd,msg,sizeof(msg));
                if(err<=0){
                    printf("verbindung zum server verloren - beende\n");
                    beende(fd);
                    free(host);
                    return -1;
                }
                guthaben=atoi(msg);
                printf("verfügbares Guthaben: %i\n",guthaben);
            }

        }

		printf("wollen sie Geld abheben, einzahlen oder abbrechen ?\n");

		while(!done){
            FD_ZERO(&cset);
            FD_SET(fd, &cset);
            FD_SET(fileno(stdin), &cset);
            select(fd+1,&cset,NULL,NULL,NULL);
            if(FD_ISSET(fileno(stdin),&cset)){
                for(i=0;i<64;i++){
                    msg[i]='\0';
                }
                read(fileno(stdin),msg,sizeof(msg));
                if(!strcmp(msg,"abheben\n")){
                    if(guthaben>0){
                        write(fd,msg,sizeof(msg));
                        betrag=0;
                        printf("wieviel möchten sie abheben? (oder abbrechen)\n");
                        while(!betrag){
                            FD_ZERO(&altset);
                            FD_SET(fileno(stdin), &altset);
                            select(fd+1,&altset,NULL,NULL,NULL);
                            if(FD_ISSET(fileno(stdin),&cset)){
                                for(i=0;i<64;i++){
                                    msg[i]='\0';
                                }
                                read(fileno(stdin),msg,sizeof(msg));
                                betrag=atoi(msg);
                                if(betrag<=0){
                                    if(!strcmp(msg,"abbrechen\n")){
                                        write(fd,msg,sizeof(msg));
                                        betrag=-1;
                                    }
                                    else{
                                        betrag=0;
                                        printf("ungültiger betrag(keine zahl oder <=0) - wieviel möchten sie abheben? (oder abbrechen)\n");
                                    }
                                }
                                else{
                                    if(betrag>guthaben){
                                        betrag=0;
                                        printf("ungültiger betrag(betrag>guthaben) - wieviel möchten sie abheben? (oder abbrechen)\n");
                                    }
                                    else{
                                        guthaben-=atoi(msg);
                                        write(fd,msg,sizeof(msg));
                                        printf("neues guthaben: %i\n",guthaben);
                                    }

                                }
                            }
                        }
                    }
                    else{
                        printf("kein guthabe zum abheben verfügbar! - wollen sie Geld einzahlen oder abbrechen ?\n");
                    }
                    printf("wollen sie Geld abheben, einzahlen oder abbrechen ?\n");
                }
               else if(!strcmp(msg,"einzahlen\n")){
                        write(fd,msg,sizeof(msg));
                        betrag=0;
                        printf("wieviel möchten sie einzahlen? (oder abbrechen)\n");
                        while(!betrag){
                            FD_ZERO(&altset);
                            FD_SET(fileno(stdin), &altset);
                            select(fd+1,&altset,NULL,NULL,NULL);
                            if(FD_ISSET(fileno(stdin),&cset)){
                                for(i=0;i<64;i++){
                                    msg[i]='\0';
                                }
                                read(fileno(stdin),msg,sizeof(msg));
                                betrag=atoi(msg);
                                if(betrag<=0){
                                    if(!strcmp(msg,"abbrechen\n")){
                                        write(fd,msg,sizeof(msg));
                                        betrag=-1;
                                    }
                                    else{
                                        betrag=0;
                                        printf("ungültiger betrag(keine zahl oder <=0) - wieviel möchten sie einzahlen? (oder abbrechen)\n");
                                    }
                                }
                                else{
                                    guthaben+=atoi(msg);
                                    write(fd,msg,sizeof(msg));
                                    printf("neues guthaben: %i\n",guthaben);
                                }
                            }
                        }

                    printf("wollen sie Geld abheben, einzahlen oder abbrechen ?\n");
                }
                else if(!strcmp(msg,"abbrechen\n")){
                    konto=-1;
                    guthaben=0;
                    write(fd,msg,sizeof(msg));
                    done=1;
                }
            }
            if(FD_ISSET(fd,&cset)){
                for(i=0;i<64;i++){
                    msg[i]='\0';
                }
                err=read(fd,msg,sizeof(msg));
                if(err<=0){
                    printf("verbindung zum server verloren - beende\n");
                    beende(fd);
                    free(host);
                    return -1;
                }
                printf("server: %s\n",msg);
            }

		}
		beende(fd);
		free(host);
	}
	return 0;
	}

