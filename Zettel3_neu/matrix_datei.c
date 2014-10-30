/*
 * matrix_datei.c
 *
 *  Created on: 30.10.2014
 *      Author: Duria
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Matrix_op.h"

int Mread(struct matrix *table){
	int n=0,m=0,l=0,x=0,y=0;
	FILE *Zahlen;
	Zahlen = fopen("Zahlen.txt", "r");
	if (Zahlen == NULL){
		printf("Fehler beim öffnen der Datei");
		return 0;
	}
	else{
		char *zeichen=malloc(200*sizeof(char));
		char *zahlen=malloc(sizeof(char)*200);
		while (fgets(zeichen,200, Zahlen) != NULL){
			for(n=0;n<table->spalten;n++){
				l=0;
				while(zeichen[m] != ' ' || zeichen[m] == '\r' || zeichen[m] == '\n'){
					zahlen[l]=zeichen[m];
					//zahlen[l+1]=' ';
					m++;
			 		l++;
				}
				m++;
				table->inhalt[y][x] = strtol(zahlen,NULL,0);
				x++;
			}
			x=0;
			y++;
			m=0;
		}
		return 1;
	}
}

void ausgabe(struct matrix *table){
	int i,j;
	for(i=0;i<table->zeilen;i++){
		for(j=0;j<table->spalten;j++){
 			printf("%lu    ",table->inhalt[i][j]);
		}
		printf("\n");
	}
}

int datausgabe(struct matrix *table){
	FILE *zahlen;
	zahlen=fopen("Zahlen.txt","w");
	int n,m;
	for (n=0;n<table->zeilen;n++){
		for(m=0;m<table->spalten;m++){
			fprintf(zahlen,"%lu ",table->inhalt[n][m]);
		}
		fprintf(zahlen," \r\n");
	}
}
int main(){
	struct matrix *table=erstellematrix(3,3);
	Mread(table);
	ausgabe(table);
	datausgabe(table);
	ausgabe(table);
	ausgabe(addmatrix(table,table));
	ausgabe(mulmatrix(table,table));
	//befreie(table);
}
