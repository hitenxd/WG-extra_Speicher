#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "Send.h"

int senden(int port, char* host){
	int fd, err;
	char msg[64];       //nachricht
	struct sockaddr_in addr;           //addresssocket
	fd = socket(AF_INET,SOCK_DGRAM,0);    //socket erstellen
	if (fd<0) {         //fehlerprüfung
		printf("Fehler beim erstellen des Sockets.");
		return 0;
	}
	addr.sin_family = AF_INET;        //addresssocket setzen
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host);
	while(1){
		printf("Gebe zu sendende Nachricht ein, exit zum verlassen.\n");
		scanf("%63s",&msg[0]);       // zu sendende Nachricjt einlesen
		if(strcmp(msg,"exit")==0){    //abbruchkriterium
			break;
		}
		err = sendto(fd, msg,strlen(msg)+1,0, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));  //senden
		if (err<0) {     //fehlerprüfung
			printf("Fehler beim Senden.");
			close(fd);        //schließen nicht vergessen
			return 0;
		}
	}
	close(fd);
	return 1;
}


int main(){


	senden(1361,"0.0.0.0");     //port und ip angeben


	return 1;

}
