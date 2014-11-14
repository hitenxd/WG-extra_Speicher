#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "Tcpclient.h"
#include "unp_readline.h"
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

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

	memset( &addr, 0, sizeof (addr));

	struct hostent *hp;

	if((hp = gethostbyname("net.cs.uni-bonn.de")) == NULL){
		perror("gethostbyname");
		return 0;
	}
	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	printf("vebrindungsaufbau...");
	if((connect(fd, (struct sockaddr*)&addr, sizeof(addr))<0)){
		printf("Fehler beim connecten\n");
		return -1;
	}

	printf("#verbindung erfolgreich\n");
	return 0;
}

int schreiben(int fd, char *page, char *host){
	char recmsg[8192];
	int i,j;

	if (write(fd,
			"GET /wg/cs/teaching/wt-201415/sysprog/ HTTP/1.1\r\nHost: net.cs.uni-bonn.de\r\n\r\n",
			strlen("GET http://www.net.cs.uni-bonn.de/wg/cs/teaching/wt-201415/sysprog/ HTTP/1.1\r\nHost: net.cs.uni-bonn.de\r\n\r\n")) < 0){
		printf("fehler beim senden");
	}
	else printf("Successfully sent html fetch request\n");

	FILE *fp = fopen("zettel.html", "w");
	for(i=0;i<13;i++){
		if((readline(fd, recmsg, 8192))<8192){
			printf("%s", recmsg);
		}
	}
	char Uebungsblatt[]= "Uebungsblatt";
	char *tempmsg;

	printf("###Aktuelle Übungszettel:###\n");
	while((readline(fd, recmsg, 8192))<8192){
		tempmsg = recmsg;

		for(j=0;j<8192;j++){
			tempmsg = strstr(tempmsg, Uebungsblatt);

			if(tempmsg!=NULL){

				for(i=0;i<18;i++){
					printf("%c", tempmsg[i]);
				}
				tempmsg += strlen(Uebungsblatt);
				printf("\n");

			}
			else break;

		}
		fputs(recmsg, fp);
		if(!(strcmp(recmsg, "</body>\n"))) break;
	}
	beende(fd);
	return 0;
}


int lesen(int fd){
	char msg[512];
	ssize_t err;
	printf("lesen() beginnt");
	err = read(fd, msg, sizeof(msg));
	printf("size der gelesenen Daten: %i", err);
	if(err == 0){
		printf("socket wird geschlossen...\n");
		beende(fd);
		return 0;
	}
	if(err == -1){
		printf("fehler beim lesen\n");
		return -1;
	}
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

int main(){
	int fd;
	char *host = "net.cs.uni-bonn.de";
	char *page = "wg/cs/teaching/wt-201415/sysprog/";
	fd = sock();
	if(!verbinden(fd,host,80)){
		if(schreiben(fd,page, host)>0){
			lesen(fd);
		}
	}
	return 0;
}

