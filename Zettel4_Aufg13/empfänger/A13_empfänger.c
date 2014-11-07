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
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int empfangstarten(){
	int fd, err;
	struct sockaddr_in addr;    //addresssocket
	fd = socket(AF_INET ,SOCK_DGRAM ,0);    //socket erstellen
	if (fd<0) {       //fehlerprüfung
		printf("socket kann nicht erstellt werden!");
		return -1;
	}
	addr.sin_family = AF_INET;         //addresssocket setzen
	addr.sin_port = htons(0);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//printf("tüdelü");
	int sizeaddr=sizeof(addr);

	err = bind(fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));  //socket binden
	if (err<0){         //fehlerprüfung
		printf("bind() fehler");
		return -1;
	}

	if(getsockname(fd, (struct sockaddr *)&addr,&sizeaddr)!=0){      //socketinformationen (ip/port) erhalten
		printf("Fehler!");
		return -1;
	}

	printf("Ip addresse ist: %s\n", inet_ntoa(addr.sin_addr));      //ausgabe der ip und des ports
	   printf("Port ist: %hu\n", (int) ntohs(addr.sin_port));


	return fd;
}

int datenerhalten(int fd){
	char msg[128];
	char name[32];
	char serv[32];

	int len, flen;

	struct sockaddr_in from;      //anfragersocket

	flen =sizeof(struct sockaddr_in);

	len = recvfrom(fd, msg, sizeof(msg), 0, (struct sockaddr*) &from, &flen);   //auf nachricht warten

	if (len<0){    //fehlerüberprüfung
		printf("Fehler beim Empfangen");
		return -1;
	}

	if(getnameinfo((struct sockaddr*)&from, sizeof(from), name,61*sizeof(char),serv, 64*sizeof(char),NI_NOFQDN) != 0){     //informationen über anfragesocket

	}

	printf("Ip-Adresse: %u Port: %hu Hostname: %s \n" ,from.sin_addr.s_addr, from.sin_port, name);     //ausgabe der informationen des anfragenden

	if(msg[0]==' '		){
		close(fd);
	}else{
		printf("nachricht: %s", msg);    //nachricht ausgeben
	}

	return 0;
}


int main(){
	//printf("tüdelü");
	//datenerhalten(empfangstarten());
	int n=empfangstarten();  //socket als rückgabewert
	datenerhalten(n);        // socket übergeben
	return 0;
}
