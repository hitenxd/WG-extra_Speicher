/*
 * Serverclient.h
 *
 *  Created on: 19.11.2014
 *      Author: Duria
 */

#ifndef SERVERCLIENT_H_
#define SERVERCLIENT_H_

int antwortauswerten(char* msg);
int schreiben(int fd);
int beende(int fd);
int verbinden(int fd, char* host, int port);
int sock();
int loop(char* msg, int max);
#endif /* SERVERCLIENT_H_ */
