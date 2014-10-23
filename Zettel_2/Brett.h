/*
 * Brett.h
 *
 *  Created on: 20.10.2014
 *      Author: Duria
 */

#ifndef BRETT_H_
#define BRETT_H_
struct t_brett{
	int **felder;
	int lang;
	int count;
};

int *aktuposi(struct t_brett *b);
int frei(struct t_brett *b,int x, int y);
void print(struct t_brett *b);
int besuchte_felder(struct t_brett *b);
int entferne_sprung(struct t_brett *b,int x, int y);
int neuer_sprung(struct t_brett *b,int x, int y);
#endif /* BRETT_H_ */
