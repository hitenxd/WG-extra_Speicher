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
#include "Serverclient.h"

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
	int max,err;
	char abfrage[16];
	char recmsg[128];
	char money[64];
	err=read(fd,recmsg,sizeof(recmsg));

    if(err<0){
        printf("ERROR! beim lesen des kontostand");
        return 0;
	}
	max = antwortauswerten(recmsg);
	sprintf(abfrage,"default");
	if(max!=0){
		while(strcmp(abfrage,"abheben") && strcmp(abfrage,"einzahlen") && strcmp(abfrage,"abbrechen")){
			printf("wollen sie Geld abheben, einzahlen oder abbrechen ?\n");

			scanf("%s",abfrage);
			if(strcmp(abfrage,"abheben") && strcmp(abfrage,"einzahlen") && strcmp(abfrage,"abbrechen")){
				printf("ungültige eingabe!...\n");
			}
		}
		if(!strcmp(abfrage,"abbrechen")){
			err=write(fd,abfrage,sizeof(abfrage));

			    if(err<0){
                    printf("ERROR! beim senden des abbruches");
                    return 0;
                }

			beende(fd);
			return 0;
		}else{
			err=write(fd, abfrage, sizeof(abfrage));

			    if(err<0){
                    printf("ERROR! beim senden der anfrage");
                    return 0;
                }

			sprintf(money,"%i",loop(abfrage, max));
			err=write(fd, money, sizeof(money));

                if(err<0){
                    printf("ERROR! beim senden des betrages");
                    return 0;
                }

            err=read(fd,recmsg,sizeof(recmsg));

                if(err<0){
                    printf("ERROR! beim lesen der antwort auf die anfrage");
                    return 0;
                }
            printf("%s\n",recmsg);
		}
	}else{
		while(strcmp(abfrage,"einzahlen") && strcmp(abfrage,"abbrechen")){
					printf("wollen sie Geld einzahlen oder abbrechen ?\n");

					scanf("%s",abfrage);
					if(strcmp(abfrage,"einzahlen") && strcmp(abfrage,"abbrechen")){
						printf("ungültige eingabe!...\n");
					}
				}
				if(!strcmp(abfrage,"abbrechen")){
					err=write(fd,abfrage,sizeof(abfrage));

					    if(err<0){
                            printf("ERROR! beim senden des abbruches");
                            return 0;
                        }

					beende(fd);
					return 0;
				}else{
					err=write(fd, abfrage, sizeof(abfrage));

					    if(err<0){
                            printf("ERROR! beim senden der anfrage");
                            return 0;
                        }

					sprintf(money,"%i",loop(abfrage, max));
					err=write(fd, money, sizeof(money));

					    if(err<0){
                            printf("ERROR! bei senden des betrages");
                            return 0;
                        }

                    err=read(fd,recmsg,sizeof(recmsg));

                        if(err<0){
                            printf("ERROR! beim lesen der antwort auf die anfrage");
                            return 0;
                        }

                    printf("%s\n",recmsg);
				}
	}
	return 1;
}
 int loop(char* msg, int max){
	 char eingabe[32];
	 int count, money;
     sprintf(eingabe,"ja");

	 count=0;
	 if(!strcmp(msg,"einzahlen")){
		 while(!strcmp(eingabe,"ja")){
			 printf("wie viel wollen sie einzahlen? (%i aktuell) \n",count);
			 scanf("%i",&money);
			 if(money<0){
				 printf("es können keine minuszahlen eingezahlt werden!\n");
			 }else{
					 count += money;
			 }
			 printf("mehr einzahlen? [ja/ bel. eing fuer nein]\n");
			 scanf("%s",eingabe);
		}
	 return count;

	 }
	 if(!strcmp(msg,"abheben")){
		 while(!strcmp(eingabe,"ja")){
			 printf("wie viel wollen sie abheben?\n");
			 scanf("%i",&money);
			 if(money<0){
				 printf("es können keine minuszahlen abgehoben werden!\n");
			 }else{
				 if(max-(count+money)<0){
					 printf("sie haben nicht genug geld dafür\n");
				 }else{
					 count += money;
				 }
			}
			 printf("mehr abheben? [ja/ bel. eing fuer nein]\n");
			 scanf("%s",eingabe);
		}
        return count;
	 }
	 return 0;
 }

int antwortauswerten(char* msg){
	printf("du kannst maximal %s abheben \n", msg);
	int e=atoi(msg);
	return e;
}
int main(int argc,char* argv[]){
    char exit[4];
    sprintf(exit,"def");
    if(argc==2){
        sprintf(exit,"%s",argv[1]);
    }
	int fd,Port,done;
	char *host=malloc(15*sizeof(char));
	printf("IP eingeben: ");
	scanf("%s",host);
    done=1;
	printf("\nPort eingeben: ");
	scanf("%i",&Port);
	fd = sock();
	if(!verbinden(fd,host,Port)){
	if(!strcmp(exit,"exit")){
        write(fd,exit,sizeof(exit));

        done=0;
	}
		while(done){
            done=schreiben(fd);
		}
		beende(fd);
		free(host);
	}
	return 0;
}

