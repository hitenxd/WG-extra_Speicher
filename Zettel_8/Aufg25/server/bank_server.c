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

struct node {
    int fd;
    int konto;
    int status;
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
    tmp->konto=-1;
    tmp->status=0;
    tmp->next=NULL;
    return tmp;
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
        printf("fehler  beim bind!\n");
        return -2;
    }
printf("ip: %s!\n",inet_ntoa(addr.sin_addr));
	return fd;
}

int lesen(int fdcl){
    int msgsize,fall;
    fall=0;
    char nachri[64];
    msgsize=read(fdcl,nachri,64*sizeof(char));
    if(msgsize<=0){
        printf("error beim lesen\n");
        return -3;
    }

    if(!strcmp(nachri,"einzahlen\n")){
        fall=-1;
    }
    else if(!strcmp(nachri,"abheben\n")){
        fall=-2;
    }
    else if(!strcmp(nachri,"abbrechen\n")){
        fall=-4;
    }
    else{
        fall=atoi(nachri);
    }


    return fall;
}


void sendnewkonto(struct node* head,int konto,int belegt){
    struct node* curs=head;
    char msg[64];
    int i;

    while(curs->next!=NULL){
        curs=curs->next;
        if(curs->konto==-1){
            for(i=0;i<64;i++){
                msg[i]='\0';
            }
            if(belegt){
                sprintf(msg,"Konto %i jetzt belegt!\n",konto);
            }
            else{
                sprintf(msg,"Konto %i jetzt frei!\n",konto);
            }
            write(curs->fd,msg,sizeof(msg));
        }
    }
}

int main(int argc,char* Argv[]){
    if(argc!=2){
        printf("error - anzahl an konten zum starten benötigt - beende \n");
        return -1;
    }
    fd_set sset;
    int port,err,anzkont,hfd,oflags,neednewhfd;
    int i,j;
    struct node* head=malloc(sizeof(struct node));
    struct node* curs=head;
    socklen_t addrlen;
    struct sockaddr_in addr;
    printf("port eingeben\n");
    scanf("%i",&port);
    addrlen=sizeof(struct sockaddr_in);
    head->fd=sock(port);
    head->konto=-1;
    head->status=0;
    head->prev=NULL;
    head->next=NULL;
    char msg[64];
    int kontostand[atoi(Argv[1])];
    int kontobelegt[atoi(Argv[1])];
    neednewhfd=0;
    hfd=head->fd;
    oflags = fcntl(head->fd, F_GETFL, 0);
    err=fcntl(head->fd, F_SETFL,oflags | O_NONBLOCK);
    if(err<0){
        printf("problem mit noblock!\n");
        return -1;
    }
    err=listen(head->fd,5);
    if(err<0){
        printf("problem beim listen!\n");
        return -1;
    }

    anzkont=atoi(Argv[1]);
    printf("%s konten im server angelegt\n",Argv[1]);


    for(i=0;i<anzkont;i++){
        kontostand[i]=100;
        kontobelegt[i]=0;
    }

while(1){
        FD_ZERO(&sset);
        FD_SET(head->fd, &sset);
        curs=head;
        while(curs->next!=NULL){
            curs=curs->next;
            FD_SET(curs->fd, &sset);
        }

        select(hfd+1,&sset,NULL,NULL,NULL);
        if(FD_ISSET(head->fd,&sset)){
            curs=newnode(head,accept(head->fd,(struct sockaddr *) &addr,&addrlen));
            if(curs->fd>0){
                if(curs->fd>hfd){
                    hfd=curs->fd;
                }
                printf("verbunden mit: %s \n",inet_ntoa(addr.sin_addr));
            }
            for(i=0;i<anzkont;i++){
                if(!kontobelegt[i]){
                    for(j=0;j<64;j++){
                        msg[j]='\0';
                    }
                    sprintf(msg,"Konto %i frei!",i);
                    write(curs->fd,msg,sizeof(msg));
                }
            }
        }
        curs=head;
        while(curs->next!=NULL){
            curs=curs->next;

                if(FD_ISSET(curs->fd,&sset)){

                    if(curs->konto!=-1){
                        for(i=0;i<64;i++){
                            msg[i]='\0';
                        }
                        if(!curs->status){
                            curs->status=lesen(curs->fd);
                        }
                        else if(curs->status==-1){
                            curs->status=lesen(curs->fd);
                            if(curs->status==-4){
                                curs->status=0;
                            }
                            else if(curs->status>0){
                                kontostand[curs->konto]+=curs->status;
                                printf("client %i hat %i  auf konto %i eingezahlt\n",curs->fd,curs->status,curs->konto);
                                curs->status=0;
                            }

                        }else if(curs->status==-2){
                            curs->status=lesen(curs->fd);
                            if(curs->status==-4){
                                curs->status=0;
                            }
                            else if(curs->status>0){
                                kontostand[curs->konto]-=curs->status;
                                printf("client %i hat %i  von konto %i abgehoben\n",curs->fd,curs->status,curs->konto);
                                curs->status=0;
                            }
                        } else if(curs->status==-3||curs->status==-4){
                            if(curs->fd==hfd){
                                neednewhfd=1;
                            }
                            kontobelegt[curs->konto]=0;
                            printf("konto %i ist jetzt wieder frei\n",curs->konto);
                            sendnewkonto(head,curs->konto,0);
                            beende(curs);
                            if(neednewhfd){
                                hfd=find_hfd(head);
                                neednewhfd=0;
                            }


                        }

                    }
                    else{
                        for(i=0;i<64;i++){
                            msg[i]='\0';
                        }
                        err=read(curs->fd,msg,sizeof(msg));
                        if(!kontobelegt[atoi(msg)]&&err>0){
                            kontobelegt[atoi(msg)]=1;
                            curs->konto=atoi(msg);
                            sendnewkonto(head,curs->konto,1);
                            for(i=0;i<64;i++){
                                msg[i]='\0';
                            }
                            printf("client %i greift jetzt auf konto %i zu \n",curs->fd,curs->konto);
                            sprintf(msg,"%i",curs->konto);
                            err=write(curs->fd,msg,sizeof(msg));
                            for(i=0;i<64;i++){
                                msg[i]='\0';
                            }
                            sprintf(msg,"%i",kontostand[curs->konto]);
                            err=write(curs->fd,msg,sizeof(msg));
                        }
                        else if(err>0){
                            for(i=0;i<64;i++){
                                msg[i]='\0';
                            }
                            sprintf(msg,"-1");
                            err=write(curs->fd,msg,sizeof(msg));
                        }
                        else{
                            printf("verbindung verloren zu client %i!\n",curs->fd);
                            beende(curs);
                            if(curs->fd==hfd){
                                neednewhfd=1;
                            }
                            if(neednewhfd){
                                hfd=find_hfd(head);
                                neednewhfd=0;
                            }

                        }
                    }
                }
         }

}
    return 0;
}


