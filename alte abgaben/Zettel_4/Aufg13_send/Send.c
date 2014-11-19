#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
int senden(int port, char* host){
	int fd, err;
	char msg[64];
	struct sockaddr_in addr;
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets.");
		return 0;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr("100.000.000.001");
	while(1){
		printf("Gebe zu sendende Nachricht ein, exit zum verlassen.");
		scanf("%63s",&msg[0]);
		if(strcmp(msg,"exit")==0){
			break;
		}
		err = sendto(fd, msg,strlen(msg)+1,0, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
		if (err<0) {
			printf("Fehler beim Senden.");
			close(fd);
			return 0;
		}
	}
	close(fd);
	return 1;
}


int main(){


	senden(4711,"localhost");


	return 1;

}
