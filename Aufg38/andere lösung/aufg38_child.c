#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/resource.h>

int main (int argc,char *argv[]){
    clock_t start, stop;
    stop=0;
    int i;
    int n=atoi(argv[1]);
    int p_numb=atoi(argv[2]);
    while(1){
    i=0;
    start=stop;
    for(;i<=n;){
    //printf("Child process %i - count %i \n",p_numb,i);
    i++;
    }
    stop=clock();

    printf("Child process %i - time: %.8f seconds - prio %i\n",p_numb,(double)(stop-start)/CLOCKS_PER_SEC,getpriority(PRIO_PROCESS,0));
    }
    return 0;
}
