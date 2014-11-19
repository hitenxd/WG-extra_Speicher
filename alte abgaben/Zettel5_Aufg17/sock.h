

#ifndef SOCK_H_
#define SOCK_H_

int manage_connections(int anzverbindungen,int(*managerfunction)(FILE* datastream,char* information));
int prepare_socket(int portnum );
#endif /* SOCK_H_ */
