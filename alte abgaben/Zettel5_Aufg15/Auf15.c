#include <stdio.h>
#include <stdlib.h>
#define MB 1024

size_t alloc_test(char *c){
  size_t mb=1;

  while ((c=(char*) malloc(mb*MB))!=NULL) {
  	free (c);
	mb++;
  }
  while ((c=(char*) malloc((--mb)*MB)) == NULL);

  return mb;
}

int main(void){
  char* c;
  long int size;
  size = alloc_test(c);
  printf("Zur Verfügung stehender Speicher in Megabyte: %lu\n", size);
  if (size>0) {
    printf("Reservierter Speicher mit Addresse %s wird nun freigegeben...\n", c);
    free (c);
  }
  return 0;
}
