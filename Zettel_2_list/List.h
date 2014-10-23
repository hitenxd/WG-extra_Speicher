/*
 * List.h
 *
 *  Created on: 23.10.2014
 *      Author: Duria
 */

#ifndef LIST_H_
#define LIST_H_

struct node{
	struct node *next;
	char *nachname;
	char *vorname;
	char *geburtsdatum;
	char *wohnort;
};

struct node *head;

void deque(struct node *vorentf);//entf=element vor zu entfernendes element
void enque(struct node *startelement, struct node *element);
struct node* neueListe(struct node erstesElement);
struct node *sort(struct node *start);
#endif /* LIST_H_ */
