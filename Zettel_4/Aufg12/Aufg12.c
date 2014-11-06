#include <netinet/in.h>
#include <stdio.h>

int big_endian(){   
   int a = 0x00000001;
   char *byte = (char*)(&a);
   if (*byte == 0x01){
      	printf("little-endian\n");
	return 0;
	}
   else{
     	printf("big-endian\n");
	return 1;
	}
}

char *my_inet_ntoa(struct in_addr in)
{

unsigned int addr = *(unsigned int *)&in;
}


int main(){
int i=big_endian();

return 0;

}
