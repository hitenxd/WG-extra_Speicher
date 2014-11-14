/*
 * Tcpclient.h
 *
 *  Created on: 13.11.2014
 *      Author: julian
 */

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_
int beende(int fd);
int lesen(int fd);
int schreiben(int fd, char *page, char *host);
int verbinden(int fd, char* host, int port);
int sock();
#endif /* TCPCLIENT_H_ */
