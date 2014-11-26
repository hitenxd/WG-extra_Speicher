/*
 * Tcpclient.c
 *
 *  Created on: 12.11.2014
 *      Author: julian
 */
#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include "Tcpclient.h"

int sock(){
	int fd;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets.");
		return -1;
	}

	return fd;
}

int verbinden(int fd, char* host, int port){
	printf("baue verbindung auf zu Webserver %s auf...", host);
	int err;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(host);

	err = connect(fd ,(struct sockaddr *)&addr ,sizeof(struct sockaddr_in));
	if(err<0){
		printf("Fehler beim connecten");
		return -1;
	}

	printf("#verbindung erfolgreich");
	return 0;
}

int schreiben(int fd){
	char* msg= {"GET /wg/cs/teaching/wt-201415/sysprog/ HTTP/1.1\r\nHost:net.cs.uni-bonn.de\r\n\r\n"};
	int size;
	size=write(fd, msg, sizeof(msg));
	if(size<0){
		printf("fehler beim write() ");
		return -1;
	}
	return size;
}


int lesen(int fd){
	char msg[512];
	int err;

	err = read(fd, msg, sizeof(msg));

	if(err == 0){
		printf("socket wird geschlossen...");
		beende(fd);
	}
	if(err == -1){
		printf("fehler beim lesen");
		return -1;
	}
	return 0;
}

int beende(int fd){
	int err;

	err = close(fd);

	if(err == -1){
		printf("fehler beim schließen");
		return -1;
	}

	printf("socker geschlossen!");
	return 0;
}

int main(){
	int fd;
	fd = sock();
	if(!verbinden(fd,"iv.cs.uni-bonn.de", 80)){
		if(!schreiben(fd)){
			if(!lesen(fd)){
				return 0;
			}
		}
	}
	return -1;
}
