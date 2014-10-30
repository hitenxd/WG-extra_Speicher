/*
 * matrix_datei.c
 *
 *  Created on: 30.10.2014
 *      Author: Duria
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


int Mread(FILE *Zahlen, int n){
	if (Zahlen == NULL){
		printf("Fehler beim öffnen der Datei");
		return 0;
	}
	else{
		char *zeichen=malloc(100*sizeof(char));
		char *zeilen=malloc(100*sizeof(char));
		int i = 0, j = 0, m = 0, p = 0;
		long **tabel;
		while (fgets(zeilen, 100, Zahlen) != NULL){
			for(;p<n;p++){
				while(zeilen[i] != ' ' || zeilen[i]==NULL){
					zeichen[i] = zeilen[i];
					zeilen[i]='a';
					i++;
				}
				i++;
				tabel[j][m] = atol(zeichen);
				m++;
			}
			i = 0;
			m = 0;
		}
		free(zeichen);
		free(zeilen);
		return 1;
	}
}

void ausgabe(long **tabel, int n, int m){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			printf("%lu    ",tabel[i][j]);
		}
		printf("\n");
	}
}
int main(){
	int n=4;
	long **tabel;
	FILE *Zahlen;
	Zahlen = fopen("zahlen.txt", "r");
	if(Mread(Zahlen,n)){
		ausgabe(tabel, n, 2);
	}
}


