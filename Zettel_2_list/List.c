/*
 * List.c
 *
 *  Created on: 23.10.2014
 *      Author: Duria
 */
#include "List.h"
#include <stdlib.h>

void deque(struct node *vorentf){
	struct node *temp=vorentf->next;
	vorentf->next=vorentf->next->next;
	//befreie(temp);
}

void enque(struct node *startelement, struct node *element){
	if(isEmpty(startelement)){
		element->next=startelement->next;
		startelement->next=element;
	}
}

struct node *neueListe(struct node erstesElement){
	struct node *head = erstesElement;
	return head;
}

int isEmpty(struct node *head){
	if(head==NULL){
		printf("Die Liste ist leer!");
		return 0;
	}else{
		return 1;
	}
}
