#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "sock.h"

int main(int argc,char**argv){
	int anzverbindungen=-1;
	int portnummer=0;
	printf("Bitte Portnummer angeben:");
	while(portnummer<=1024){
		scanf("%i",portnummer);
		if(portnummer<=1024)printf("Muss größer als 1024 sein!");
	}
	printf("Bitte Anzahl an Verbindungen angeben:");
	while(anzverbindungen<1){
		scanf("%i",anzverbindungen);
		if(anzverbindungen<1)printf("Muss größer als 0 sein!");
	}


	if(prepare_socket(portnummer)){
		printf("Fehler beim Erzeugen/Binden des Sockets \n");
		return 1;
	}
	anzverbindungen=manage_connections(anzverbindungen,&manager);
	printf("%d Verbindungen wurden abgearbeitet\n",anzverbindungen);
	close_socket();
	return 0;
}

