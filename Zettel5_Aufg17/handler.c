#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "unp_readline.h"

int manager(FILE* datastream,char* information){
	char msg[512], ans[512],tmp[512];
	int n=0,m,b=0,a,i=0;
	ssize_t read(datastream, msg, size_t count);
	//readline(datastream, msg, 512);
	while(msg[n]!=' '){
		 tmp[n]=msg[n];
		 n++;
	}
	if(tmp!="GET"){
		ans="HTTP/1.1 501 Not implemented";
		b=1;
	}
	n++;
	while(msg[n]!='\n'){
		a=n-10;
		n++;
	}
	if((msg[n-1]!="1" || msg[n-2]!="." || msg[n-3]!="1") && b==0){
		ans="HTTP/1.1 505 HTTP Version Not Supported";
		b=1;
	}
	n++;
	while(msg[n]!='\n'){
				 n++;
		}
	n++;
	m=n;
	while(msg[n]!='\n'){
			n++;
		}
	if((msg[m]!='H' || msg[m+1]!='o' || msg[m+2]!='s' || msg[m+3]!='t' || msg[m+4]!=':' ||msg[m+5]!=' ') && b==0){
		ans="HTTP/1.1 400 Bad Request";
		b=1;
	} else if(msg[n+1]=='\n' && b==0){
		ans="HTTP/1.1 400 Bad Request";
		b=1;
	}
	n=4;
	char temp[a-n];
	while(n!=a+1){
		temp[i]=msg[n];
		n++;
		i++;
	}

	if(b==0){
		ans="HTTP/1.1 200 OK \n Content - Type: text/plain \n Anfrage entgegengenommen \n Ressource: %s \n Client ID: %s",temp,information;
	}

	printf("%s \n \n %s", msg, ans);
	ssize_t write(datastream, ans, size_t count=512);
}

