#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "handler.h"

int serversocket=0;
int prepare_socket(int portnum ){
	int  err;
	struct sockaddr_in addr;
	serversocket = socket(AF_INET,SOCK_STREAM,0);
	if (serversocket<0) {
		return 0;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(portnummer);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	err = bind(serversocket, (struct sockaddr *) &addr,sizeof(struct sockaddr_in));
	if (err<0) {
		return 0;
	}
	return 1;
}

void close_socket(void){
	close(serversocket);
}

int manage_connections(int anzverbindungen,int(*managerfunction)(FILE* datastream,char* information)){
	int newsock;
	int listen(int serversocket, int anzverbindungen);
	newsock = accept(serversocket,(struct sockaddr *) &addr,&addrlen);
	manager(newsock,inet_ntoa(addr.sin_addr));
	close(newsock);
	return anzverbindungen;
}

