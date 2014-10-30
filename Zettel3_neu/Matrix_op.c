/*
 * Matrix_op.c
 *
 *  Created on: 30.10.2014
 *      Author: Duria
 */
#include "Matrix_op.h"
#include <stdlib.h>

struct matrix *erstellematrix(int anzahlz, int anzahls){
	int i=0;
	struct matrix *M=malloc(sizeof(struct matrix));
	M->spalten=anzahls;
	M->zeilen=anzahlz;
	M->inhalt=malloc(anzahls*sizeof(long*));
	for(;i<anzahls;i++){
		M->inhalt[i]=malloc(anzahlz*sizeof(long));
	}
	return (M);
}

void befreie(struct matrix *M){
	int i=0;
	for(;i<(M->spalten);i++){
			free(M->inhalt[i]);
	}
	free(M->inhalt);
	free(M);
}

struct matrix *addmatrix(struct matrix *a, struct matrix *b){
	if(a->spalten!=b->spalten||a->zeilen!=b->zeilen){
		printf("matritzen passen nicht zueinander, addition und so, probier es noch einmal");
	}else{
		struct matrix *c=erstellematrix(a->zeilen,a->spalten);
		int n,m;
		for(n=0;n<a->zeilen;n++){
			for(m=0;m<a->spalten;m++){
				c->inhalt[n][m]=a->inhalt[n][m]+b->inhalt[n][m];
			}
		}
		return c;
	}
	return a;
}

struct matrix *mulmatrix(struct matrix *a, struct matrix *b){
	if(a->spalten!=b->zeilen){
		printf("matritzen passen nicht zueinander, multiplikation und so, probier es noch einmal");
	}else{
		struct matrix *c=erstellematrix(a->zeilen,b->spalten);
		long d=0;
		int n,m,pelz;
		for(pelz=0;pelz<b->spalten;pelz++){
			for(n=0;n<a->zeilen;n++){
				for(m=0;m<b->spalten;m++){
					d=a->inhalt[n][m]*b->inhalt[m][pelz]+d;
				}
				c->inhalt[n][pelz]=d;
				d=0;
			}
		}
		return c;
	}
	return a;
}
