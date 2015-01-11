#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv){
	int i,j,b=0,n,r=0,l=0,m;
    char x=47,y=48,z=92,w=95,v=124;
	int k=atoi(argv[1]);
	int h=atoi(argv[2]);
	srand(time(NULL));
	for(j=1;j<=k;j++){
		r+=j*2;
	}
	int a[h];
	for(i=0;i<h;i++){
		a[i]=i;
	}
	for(i=0;i<h;i++){
		a[i]=rand()%r;
		for(n=0;n<h;n++){
			if((a[i]==a[n]) && (i!=n) ){
				a[i]=rand()%r;
				n=0;
			}
		}
	}
		r=0;
		l=0;
		m=0;
	for(j=1;j<=k;j++){
		printf(" ");
		for(n=0;n<k-j;n++)printf("  ");
		for(i=1;i<=j;i++){
			for(r=0;r<h;r++){
				if((a[r]==l) && (m==2)){
					m=3;
				}else if(a[r]==l) {
					m=1;
				}
				if((a[r]==l+1) && (m==1)){
					m=3;
				}else if(a[r]==l+1){
					m=2;
				}
			}
			if(m==1){
				printf("%c%c%c ",y,w,z);
				m=0;
			}else if(m==2){
				printf("%c%c%c ",x,w,y);
				m=0;
			}else if(m==3){
				printf("%c%c%c ",y,w,y);
				m=0;
			}else{
				printf("%c%c%c ",x,w,z);
			}
			l+=2;
		}
		printf("\n");
	}
	for(n=1;n<k;n++)printf("  ");
	printf("|%c%c%c|",v,w,w,w,v);
	return 1;
}
