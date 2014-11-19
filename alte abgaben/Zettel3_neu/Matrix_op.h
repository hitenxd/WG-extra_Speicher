/*
 * Matrix_op.h
 *
 *  Created on: 30.10.2014
 *      Author: Duria
 */

#ifndef MATRIX_OP_H_
#define MATRIX_OP_H_

struct matrix{
	long **inhalt;
	int zeilen;
	int spalten;
};
struct matrix *erstellematrix(int anzahlz, int anzahls);
void befreie(struct matrix *M);
struct matrix *mulmatrix(struct matrix *a, struct matrix *b);
struct matrix *addmatrix(struct matrix *a, struct matrix *b);

#endif /* MATRIX_OP_H_ */
