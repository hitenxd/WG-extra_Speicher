#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

struct node {
     int fd;
     struct node* next;
     struct node* prev;

};

struct node *newnode(struct node* head,int newfd){
    struct node* crs=head;
    struct node* tmp=malloc(sizeof(struct node));
    while(crs->next!=NULL){
        crs=crs->next;

    }
    tmp->prev=crs;
    crs->next=tmp;
    tmp->fd=newfd;
    tmp->next=NULL;
    return tmp;
}



int sock(int port){
	int fd,err;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if (fd<0) {
		printf("Fehler beim erstellen des Sockets. \n");
		return -1;
	}

    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    err = bind(fd,(struct sockaddr *) &addr,sizeof(struct sockaddr_in));
    if (err<0) {
        printf("fehler  beim bind!");
        return -2;
    }
printf("ip: %s!\n",inet_ntoa(addr.sin_addr));
	return fd;
}


int find_hfd(struct node *head){
    int hfd=head->fd;
    struct node *tmp=head;
    while(tmp->next!=NULL){
        tmp=tmp->next;
        if(tmp->fd>hfd){
            hfd=tmp->fd;
        }
    }
    return hfd;
}
void beende(struct node* fdcl){
    close(fdcl->fd);
    if(fdcl->next!=NULL){fdcl->next->prev=fdcl->prev;}
    if(fdcl->prev!=NULL){fdcl->prev->next=fdcl->next;}
    free(fdcl);
}

void emergencyshutdownofdoom(struct node *head){
    struct node *akt=head;
    if(akt!=NULL){
        while(akt->next!=NULL){
            akt=akt->next;
            beende(akt->prev);
        }
        beende(akt);
    }
    printf("WOOOAW!!! das war ja nochmal knapp - gut gemacht mr. president \n");
}

int main(int args,char* Argv[]){
    fd_set sset;
    int port,err,timeo,oflags,hfd,neednewhfd,i;
    port=4711;
    neednewhfd=0;
    struct node* head=malloc(sizeof(struct node));
    struct node* curs=head;
    struct node* curs_alt=head;
    head->fd=sock(port);
    head->prev=NULL;
    head->next=NULL;
    char msg[256];
    sprintf(msg," ");
    socklen_t addrlen;
    struct sockaddr_in addr;
    addrlen=sizeof(struct sockaddr_in);
    hfd=head->fd;
    oflags = fcntl(head->fd, F_GETFL, 0);
    err=fcntl(head->fd, F_SETFL,oflags | O_NONBLOCK);
    err=listen(head->fd,5);
    if(err<0){
        printf("problem beim listen! \n");
        beende(head);
        return -1;
    }


    while(1){

        FD_ZERO(&sset);
        FD_SET(head->fd, &sset);
        FD_SET(fileno(stdin),&sset);
        curs=head;
        while(curs->next!=NULL){
            curs=curs->next;
            FD_SET(curs->fd, &sset);
        }

        timeo=select(hfd+1,&sset,NULL,NULL,NULL);
        if(timeo>0){
            if(FD_ISSET(fileno(stdin),&sset)){
                    for(i=0;i<256;i++){
                        msg[i]='\0';
                    }
                    read(fileno(stdin),msg,sizeof(msg));
                    if(msg[0]=='e' && msg[1]=='x' && msg[2]=='i' && msg[3]=='t'){
                        emergencyshutdownofdoom(head);
                        return 0;
                    }
            }
            if(FD_ISSET(head->fd,&sset)){
                curs=newnode(head,accept(head->fd,(struct sockaddr *) &addr,&addrlen));
                if(curs->fd>0){
                    if(curs->fd>hfd){
                        hfd=curs->fd;
                    }
                    printf("verbunden mit: %s \n",inet_ntoa(addr.sin_addr));
                }
            }
            curs=head;
            while(curs->next!=NULL){
                curs=curs->next;

                if(FD_ISSET(curs->fd,&sset)){
                    //sprintf(msg," ");
                    for(i=0;i<256;i++){
                        msg[i]='\0';
                    }
                    err=read(curs->fd,msg,sizeof(msg));
                    if(err>0){
                        curs_alt=head;
                        printf("%s \n",msg);

                        while(curs_alt->next!=NULL){
                            curs_alt=curs_alt->next;
                            err=write(curs_alt->fd,msg,sizeof(msg));
                            if(err<0){
                                printf("problem beim senden an socket %i - beende verbindung  \n",curs_alt->fd);
                                if(curs_alt->fd==hfd){
                                    neednewhfd=1;
                                }
                                curs_alt=curs_alt->prev;
                                beende(curs_alt->next);
                                if(neednewhfd){
                                    find_hfd(head);
                                    neednewhfd=0;
                                }
                            }
                        }
                    }
                    else {
                        if(curs->fd==hfd){
                            neednewhfd=1;
                        }
                        curs=curs->prev;
                        beende(curs->next);
                        if(neednewhfd){
                            find_hfd(head);
                            neednewhfd=0;
                        }

                        printf("ein client hat die verbindung verloren  \n");
                    }
                }
            }
        }
    }
    beende(head);
    return 0;
}

