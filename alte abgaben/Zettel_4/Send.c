#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>

int send(int port, char* host){
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
	addr.sin_addr.s_addr = inet_addr(host);
	while(){
		printf("Gebe zu sendende Nachricht ein, exit zum verlassen.");
		scanf("%63s",&msg[0]);
		if(msg=='exit')break;
		err = sendto(fd, msg,strlen(msg)+1,0, (struct sockaddr *) &addr, sizeof(struct sockaddr_in));
		if (err<0) {
			printf("Fehler beim Senden.");
			return 0;
		}
	}
	return 1;
}


int main(){


	send(4711,'localhost');


	return 1;




}
