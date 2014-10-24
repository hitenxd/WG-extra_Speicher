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
	int *max=aktuposi(b);	//aktuelle position bestimmen
	b->felder[max[0]+x][max[1]+y]=b->felder[max[0]][max[1]]+1;// neue Position (bestimmt mit aktueller Position +x,+y)auf den wert von der aktuellen Posi. +1 setzen 
	free(max);//speicher von temporär bestimmter Position freigeben
	return 1;
}

int entferne_sprung(struct t_brett *b, int x, int y){
	int *max=aktuposi(b);//aktuelle position bestimmen
	b->felder[max[0]][max[1]]=0; //aktuelle position auf 0 (zurück)setzen
	free(max);//speicher von temporär bestimmter Position freigeben
	return 1;
}

int besuchte_felder(struct t_brett *b){
	int *max=aktuposi(b);//aktuelle position bestimmen
	int temp=b->felder[max[0]][max[1]];//wert aus der aktuellen position auslesen
	free(max);//speicher von temporär bestimmter Position freigeben
	return temp;
}

void print(struct t_brett *b){
	int i,j;
	for(i=0; i<b->lang;i++){// n (höhe des bretts) durchläufe
		for(j=0;j<b->lang;j++){//n (breite des bretts) durchläufe
			printf("+---"); // trennlinie schreiben
		}
		printf("+\n");
		for(j=0;j<b->lang;j++){//n (breite des bretts) durchläufe
			printf("+%3i",b->felder[i][j]);//besuch reihenfolge der felder angeben
		}
		printf("+\n");
	}
	for(j=0;j<b->lang;j++){
		printf("+---");
	}
	printf("+\n");
}

int frei(struct t_brett *b, int x, int y){
	int *max=aktuposi(b);//aktuelle position bestimmen
	//aus dem brett?
	if((max[0]+x)>(b->lang-1)||(max[0]+x)<0||(max[1]+y)>(b->lang-1)||(max[1]+y)<0){//prüfen ob außerhabl des feldes
		free(max);//speicher von temporär bestimmter Position freigeben
		return 0;
	}else{
		//feld frei?
		if(b->felder[max[0]+x][max[1]+y]==0){//prüfen ob das feld noch nicht besucht wurde
			free(max);//speicher von temporär bestimmter Position freigeben
			return 1;
		}else{
			//feld nicht frei!
			free(max);//speicher von temporär bestimmter Position freigeben
			return 0;
		}
	}

}

int *aktuposi(struct t_brett *b){
	int i,j;
	int *max=malloc(2*sizeof(int));//speicher allocieren in der die position des aktuellen feldes gespeichert werden  kann
	max[0]=0;
	max[1]=0;
	for (i=0;i<b->lang;i++){// n (höhe des bretts) durchläufe
		for(j=0;j<b->lang;j++){// n (breite des bretts) durchläufe
			if(b->felder[i][j]>b->felder[max[0]][max[1]]){//prüfen ob das aktuelle feld später besucht wurde als das feld des momentanen durchlauf
				max[0]=i;//wenn nicht aktuelles feld auf die aktuellen zählvariablen setzen
				max[1]=j;
			}
		}
	}
	return max;
}

int init_brett(struct t_brett *b, int n, int x, int y){
	b->felder=malloc(n*sizeof(int*));//speicher für n (höhe des bretts) int pointer allocieren
	int i,j;
	for (i=0;i<n;i++){
		b->felder[i]=malloc(n*sizeof(int));// allen n pointern speicher für n ints allocieren und zuweisen (insgesamt speicher  für nxn ints allocieren die als felder dienen, in denen die besuch reihenfolge gespeichert wird)
	}
	b->lang=n;//höhe / breite des feldes auf die angegeben n setzen
	for (i=0;i<b->lang;i++){
		for(j=0;j<b->lang;j++){
			b->felder[i][j]=0;//alle n x n felder auf 0 initialisieren
		}
	}
	b->felder[x][y]=1;//angegebene start position auf 1 setzen
	return 0;
}

void loesche_brett(struct t_brett *b){
//nicht ganz fertig
	free(b->felder);
}
