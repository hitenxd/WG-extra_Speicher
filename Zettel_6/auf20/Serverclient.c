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
	int max;
	char* abfrage=malloc(12*sizeof(char));
	char* recmsg=malloc(12*sizeof(char));
	char* money=malloc(12*sizeof(char));
	read(fd,recmsg,sizeof(recmsg));
	max = antwortauswerten(recmsg);

	while(!strcmp(abfrage,"abheben") || strcmp(abfrage,"einzahlen") || strcmp(abfrage,"abbrechen")){
		printf("wollen sie Geld abheben, einzahlen oder abbrechen ?\n");

		scanf("%s",abfrage);
		if(strcmp(abfrage,"abheben") || strcmp(abfrage,"einzahlen") || strcmp(abfrage,"abbrechen")){
			printf("ungültige eingabe!...\n");
		}
	}
	if(!strcmp(abfrage,"abbrechen")){
		close(fd);
		return 0;
	}else{
		write(fd, abfrage, sizeof(abfrage));
		sprintf(money,"%i",loop(abfrage, max));
		write(fd, money, sizeof(money));
		beende(fd);
	}

	return 0;
}
 int loop(char* msg, int max){
	 char* eingabe;
	 int count, money;

	 count=0;
	 eingabe="ja";
	 if(!strcmp(msg,"einzahlen")){
		 while(!strcmp(eingabe,"ja")>0){
			 printf("wie viel wollen sie einzahlen? \n");
			 scanf("%i",&money);
			 if(money<0){
				 printf("es können keine minuszahlen eingezahlt werden!\n");
			 }else{
					 count += money;
			}
			 printf("weiter einzahlen? [ja/nein]\n");
			 scanf("%s",eingabe);
		}
	 }
	 if(!strcmp(msg,"abheben")){
		 while(!strcmp(eingabe,"ja")>0){
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
			 printf("weiter abheben? [ja/nein]\n");
			 scanf("%s",eingabe);
		}
		 printf("es wurde insgesamt [%i] Euro abgehoben, verbindung wird geschlossen\n", count);
		 return count;
	 }
	 return 0;
 }

int antwortauswerten(char* msg){
	printf("du kannst maximal %s abheben \n", msg);
	int e=atoi(msg);
	return e;
}
int main(){
	int fd,Port;
	char *host=malloc(15*sizeof(char));
	printf("IP eingeben: ");
	scanf("%s",host);

	printf("\n Port eingeben: ");
	scanf("%i",&Port);
	fd = sock();
	if(!verbinden(fd,host,Port)){
		schreiben(fd);
	}
	return 0;
}

