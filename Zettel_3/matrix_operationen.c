/*
 * matrix_operationen.c
 *
 *  Created on: 30.10.2014
 *      Author: Jonas
 */

#include <stdlib.h>
#include "matrix_operationen.h"

struct matrix *matrix_erstellen(int zeilen, int spalten){
	struct matrix *neueMatrix=malloc(sizeof(struct matrix));

	neueMatrix->zeilen_anzahl=zeilen;
	neueMatrix->spalten_anzahl=spalten;
	neueMatrix->zeilen=malloc(zeilen*sizeof(long));
	neueMatrix->spalten=malloc(spalten*sizeof(long));

	return neueMatrix;
}


//struct matrix *matrix_generiere(){
//}

void matrix_befreie(struct matrix *matrixBefreie){
	free(matrixBefreie->spalten);
	free(matrixBefreie->zeilen);
	free(matrixBefreie);
}
