/*
 * springerproblem.c
 *
 *  Created on: 20.10.2014
 *      Author: Duria
 */
#include "brett.h"
#include <stdlib.h>
#include <stdio.h>

int n = 5;
int start_x = 0;
int start_y = 0;
int lsgnr = 1;
int moves[8][2] = {{2,1}, {1,2}, {-2,1}, {-1,2}, {2,-1}, {1,-2}, {-2,-1}, {-1,-2}};
struct t_brett b;

void setze_springer(struct t_brett *b);

int main()
{
  if (init_brett(&b,n,start_x,start_y)>0) return EXIT_FAILURE;
  setze_springer(&b);
  loesche_brett(&b);

  return EXIT_SUCCESS;
}

void setze_springer(struct t_brett *b)
{
  if (besuchte_felder(b)>= n*n) {
	printf("Loesung %i\n", lsgnr);
    lsgnr++;
    print(b);
    printf("\n");
  }
  else {
    int i;
    for (i=0;i<8;i++) {
      if (frei(b, moves[i][0], moves[i][1])) {
        neuer_sprung(b, moves[i][0], moves[i][1]);
        setze_springer(b);
        entferne_sprung(b, moves[i][0], moves[i][1]);
      }
    }
  }
}

