#include <netinet/in.h>
#include <stdio.h>

int big_endian(){
	int i=2;
	if(i & 1<<0){
		return 1;
	}	
	else{
		return 0;		
	}
	//printf(byte(&i);
}

int main(){
int i=big_endian();
printf("ist es big  endian? %i \n",i);
return 0;
}


