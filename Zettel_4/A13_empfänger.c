/*
 * A13_empfänger.c
 *
 *  Created on: 06.11.2014
 *      Author: julian
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <netdb.h>

int empfangstarten(){
	int fd, err;
	struct sockaddr_in addr;
	fd = socket(AF_INET ,SOCK_DGRAM ,0);
	if (fd<0) {
		printf("socket kann nicht erstellt werden!");
		return -1;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(0);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	int sizeaddr=sizeof(addr);

	err = bind(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
	if (err<0){
		printf("bind() fehler");
		return -1;
	}

	printf("eigene portnummer: "+ getsockname(fd, (struct sockaddr *)&addr,&sizeaddr) );

	return fd;
}

int datenerhalten(int fd){
	char msg[128];
	char name[32];
	char serv[32];

	int len, flen;

	struct sockaddr_in from;

	flen =sizeof(struct sockaddr_in);

	len = recvfrom(fd, msg, sizeof(msg), 0, (struct sockaddr*) &from, &flen);

	if (len<0){
		printf("Fehler beim Empfangen");
		return -1;
	}

	if(getnameinfo((struct sockaddr*)&from, sizeof(from), name,61*sizeof(char),serv, 64*sizeof(char),NI_NOFQDN) != 0){

	}

	printf("Ip-Adresse: %i Port: %i Hostname: %s \n" ,from.sin_addr, from.sin_port, name);

	if(msg[0]==' '		){
		close(fd);
	}else{
		printf("nachricht: %s", msg);
	}

	return 0;
}


int main(){
	datenerhalten(empfangstarten());
	return 0;
}
