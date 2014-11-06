#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <arpa/inet.h>

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

char *my_inet_ntoa(struct in_addr in){
int i=0,j=0,k=0,temp_calc=0,zeroAmmount=0,endian=big_endian();
printf("%i \n",endian);
char *temp =malloc(sizeof(char)*15);
unsigned int addr = *(unsigned int *)&in;


for(i=0;i<4;i++){
	for(j=0;j<8;j++){
		temp_calc=temp_calc+pow(2,j)*getBit(addr,(int)(j+(endian*3+pow(-1,endian)*i)*8));

	}

	for(k=0;k<3;k++){
		if(temp_calc>=pow(10,(2-k))){
		temp[i*4+k-zeroAmmount]='0'+getDigit(temp_calc,k);

		}
		else{zeroAmmount++;}
	}
	temp_calc=0;
	if(i!=3){
		temp[i*4+3-zeroAmmount]='.';	
	}
	
}

return temp;
}

int getDigit(int a, int b){
	int hDig=0,zDig=0,eDig=0;
	hDig=a/100;
	zDig=(a-hDig*100)/10;
	eDig=(a-hDig*100-zDig*10);
	if(b==0)return hDig;
	if(b==1)return zDig;
	if(b==2)return eDig;
}

int getBit(int a,int b){
if((a >> b) & 1 ){
	return 1;		
}
return 0;
}



int main(){
struct in_addr adrr;
adrr.s_addr=0x12345678;
int i=big_endian();

char*a=my_inet_ntoa(adrr);
printf("%s\n",a);

return 0;

}
