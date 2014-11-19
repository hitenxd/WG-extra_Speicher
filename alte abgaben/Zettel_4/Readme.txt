#include <string.h> 
#include <ctype.h>

->damit funkitonen bekannt sind,wenn diese aufgerufen werden.

aus:
if (toupper(st1[i]) != toupper(st1[st1_len -i])) return 0;
mache:
if (toupper((unsigned int)st1[i]) != toupper((unsigned int)st1[st1_len -i])) return 0;
da toupper ein int erwartet.


genauso:
st2[i] = toupper((unsigned int)st1[st1_len -1 -i]); 

aus:
 char *exit = 'exit';
mache:
 char *exit = "exit";
da es ein string und kein zeichen ist.