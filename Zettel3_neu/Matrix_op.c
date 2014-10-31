/*
 * Matrix_op.c
 *
 *  Created on: 30.10.2014
 *      Author: Duria
 */
#include "Matrix_op.h"
#include <stdio.h>
#include <stdlib.h>

struct matrix *erstellematrix(int anzahlz, int anzahls){
	int i=0;
	struct matrix *M=malloc(sizeof(struct matrix));//speicher allocieren für eine matrix struct
	M->spalten=anzahls;//spalten und zeilen auf die angegebenen parameter setzen
	M->zeilen=anzahlz;
	M->inhalt=malloc(anzahls*sizeof(long*)); //speicher für die  spalten  allocieren 
	for(;i<anzahls;i++){
		M->inhalt[i]=malloc(anzahlz*sizeof(long)); //speicher für die felder in den spalten allocieren
	}
	return (M);
}

void befreie(struct matrix *M){
	int i=0;
	for(;i<(M->spalten);i++){//alle spalten durchgehen
			free(M->inhalt[i]);//speicher aller felder in der spalte freigeben
	}
	free(M->inhalt);//speicher der spalten freigeben
	free(M);//allocierter speicher für die matrix freigeben
}

struct matrix *addmatrix(struct matrix *a, struct matrix *b){
	if(a->spalten!=b->spalten||a->zeilen!=b->zeilen){ //format der beiden matritzen auf gleichheit prüfen
		printf("matritzen passen nicht zueinander, addition und so, probier es noch einmal");
	}else{
		struct matrix *c=erstellematrix(a->zeilen,a->spalten);//neue matrix zum speichern des ergebnis erstellen
		int n,m;
		for(n=0;n<a->zeilen;n++){
			for(m=0;m<a->spalten;m++){//spalten und zeilen durchgehen
				c->inhalt[n][m]=a->inhalt[n][m]+b->inhalt[n][m];//die neue matrix an der aktuellen stelle  auf die summe der beiden anderen matritzen an der aktuellen stelle setzen 
			}
		}
		return c;
	}
	return a;
}

struct matrix *mulmatrix(struct matrix *a, struct matrix *b){
	if(a->spalten!=b->zeilen){//format der beiden matritzen prüfen
		printf("matritzen passen nicht zueinander, multiplikation und so, probier es noch einmal");
	}else{
		struct matrix *c=erstellematrix(a->zeilen,b->spalten);//neue matrix zum speichern des ergebnis erstellen
		long d=0;
		int n,m,pelz;
		for(pelz=0;pelz<b->spalten;pelz++){
			for(n=0;n<a->zeilen;n++){//spalten und zeilen durchgehen
				for(m=0;m<b->spalten;m++){
					d=a->inhalt[n][m]*b->inhalt[m][pelz]+d; //skalarprodukt von aktueller zeile und aktueller spalte berechnen
				}
				c->inhalt[n][pelz]=d; //ergebnis in die neue matrix in die entsprechende zeile und spalte schreiben
				d=0;//ergebnis auf  0 zurücksetzen
			}
		}
		return c;
	}
	return a;
}
