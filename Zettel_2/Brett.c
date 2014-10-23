/*
 * Brett.c
 *
 *  Created on: 20.10.2014
 *      Author: Duria
 */
#include <stdio.h>
#include <stdlib.h>
#include "Brett.h"

int neuer_sprung(struct t_brett *b, int x, int y){
	int *max=aktuposi(b);
	b->felder[max[0]+x][max[1]+y]=b->felder[max[0]][max[1]]+1;
	free(max);
	return 1;
}

int entferne_sprung(struct t_brett *b, int x, int y){
	int *max=aktuposi(b);
	b->felder[max[0]][max[1]]=0;
	free(max);
	return 1;
}

int besuchte_felder(struct t_brett *b){
	int *max=aktuposi(b);
	int temp=b->felder[max[0]][max[1]];
	free(max);
	//printf("count: %i  \n",temp);
	return temp;
}

void print(struct t_brett *b){
	int i,j;
	for(i=0; i<b->lang;i++){
		for(j=0;j<b->lang;j++){
			printf("+---");
		}
		printf("+\n");
		for(j=0;j<b->lang;j++){
			printf("+%3i",b->felder[i][j]);
		}
		printf("+\n");
	}
	for(j=0;j<b->lang;j++){
		printf("+---");
	}
	printf("+\n");
}

int frei(struct t_brett *b, int x, int y){
	int *max=aktuposi(b);
	//aus dem brett?
	if((max[0]+x)>(b->lang-1)||(max[0]+x)<0||(max[1]+y)>(b->lang-1)||(max[1]+y)<0){
		free(max);
		return 0;
	}else{
		//feld frei?
		if(b->felder[max[0]+x][max[1]+y]==0){
			free(max);
			return 1;
		}else{
			//feld nicht frei!
			free(max);
			return 0;
		}
	}

}

int *aktuposi(struct t_brett *b){
	int i,j;
	int *max=malloc(2*sizeof(int));
	max[0]=0;
	max[1]=0;
	for (i=0;i<b->lang;i++){
		for(j=0;j<b->lang;j++){
			if(b->felder[i][j]>b->felder[max[0]][max[1]]){
				max[0]=i;
				max[1]=j;
			}
		}
	}
	return max;
}

int init_brett(struct t_brett *b, int n, int x, int y){
	b->felder=malloc(n*sizeof(int*));
	int i,j;
	for (i=0;i<n;i++){
		b->felder[i]=malloc(n*sizeof(int));
	}
	b->lang=n;
	for (i=0;i<b->lang;i++){
		for(j=0;j<b->lang;j++){
			b->felder[i][j]=0;
		}
	}
	b->felder[x][y]=1;
	return 0;
}

void loesche_brett(struct t_brett *b){
	free(b->felder);
}
