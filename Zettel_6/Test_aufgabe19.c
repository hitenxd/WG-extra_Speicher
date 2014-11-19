#include <stdio.h>
int schaltjahr(int *year);
int main(void) {
 printf("Dies ist ein Programm zur Erkennung von Schaltjahren.\n\n");

 int year = 1;

 do {
 printf("Bitte geben Sie eine positive Jahreszahl ein: ");
 scanf("%i", &year);
 printf("\n");
 if (year<=0)
 printf("Positiv?\n"); } while(year<=0);
 if(schaltjahr(&year))
 printf("Das Jahr %i ist ein Schaltjahr.\n", year); //nicht referenzieren!
 else
 printf("Das Jahr %i ist kein Schaltjahr.\n", year);
 return 0;
}
int schaltjahr(int *year){
 if(((0==year%4) & (0!=year%100)) | (0==year%400))
 return 1;
 else
 return 0;
}
