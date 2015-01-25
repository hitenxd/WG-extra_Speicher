#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

struct mmulParam{
int n;
int m;
int k;
int *M1;
int *M2;
int *M;
int *cal;
};

void print_matrix(int n, int m, int *M);

void* mmul(void* mmularg);

void write_mat_to_file(int* mat,int zeilen,int spalten){
FILE *f = fopen("matr.txt", "w");
int i,j;
for (i=0;i<zeilen;i++){
    for(j=0;j<spalten;j++){
        fprintf(f, "%i ", mat[i*spalten+j]);
    }
    fprintf(f,"\n");
}

fclose(f);

}


int main(int argc,char* argv[]){

    if(argc!=5){
        printf("benötige param.: Anz. threads, n, m, k\n");
        return -1;
    }

    struct timeval start, stop;

    int i,j,anzthr,n,m,k;

    anzthr=atoi(argv[1]);
    n=atoi(argv[2]);
    m=atoi(argv[3]);
    k=atoi(argv[4]);
    pthread_t workThreadID[anzthr];
    int MAX_NMBR=20;
    int *A=malloc(n*m*sizeof(int));
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){

            A[i*m+j]=rand()%MAX_NMBR;
            if(rand()%2){
                A[i*m+j]*=-1;
            }
        }
    }

    int *B=malloc(m*k*sizeof(int));
    for(i=0;i<m;i++){

        for(j=0;j<k;j++){
            B[i*k+j]=rand()%MAX_NMBR;
            if(rand()%2){
                B[i*k+j]*=-1;
            }
        }

    }

    int *calc=malloc(n*k*sizeof(int));

    for(i=0;i<n*k;i++){
        calc[i]=0;
    }

    int *C=malloc(n*k*sizeof(int));

    struct mmulParam par;
    par.n=n;
    par.m=m;
    par.k=k;
    par.M1=A;
    par.M2=B;
    par.M=C;
    par.cal=calc;
    print_matrix(n,m,A);
    print_matrix(m,k,B);

    gettimeofday(&start,NULL);
    for(i=0;i<anzthr;i++){
        pthread_create(&workThreadID[i], NULL, mmul, &par);
    }
    for(i=0;i<anzthr;i++){
        pthread_join(workThreadID[i],NULL);
    }
    gettimeofday(&stop,NULL);
    print_matrix(n,k,C);
    write_mat_to_file(C,n,k);
    printf("hat %d sec und %d mikro sec gedauert \n",(int)(stop.tv_sec-start.tv_sec),(int)(stop.tv_usec-start.tv_usec));

    free(A);
    free(B);
    free(C);
    free(calc);
    return 0;
}

void print_matrix(int n, int m, int *M)
{
  int x;
  int y;
  printf("\n");
  for (y=0;y<n;y++) {
    for (x=0;x<m;x++) {
      printf ("%5d", M[y*m+x]);
    }
    printf("\n");
  }
  printf("\n");
}

void* mmul(void* mmularg)
{
    struct mmulParam* mmp = (struct mmulParam*) mmularg;
  int x;
  int y;
  int z;
  int temp;
  for (y=0;y<mmp->n;y++) {
    for (x=0;x<mmp->k;x++) {
      if(!mmp->cal[y*mmp->k+x]){
        mmp->cal[y*mmp->k+x]=1;
        //printf("%i,%i NOT YET calculated+++++++\n",y,x);
        temp = 0;
      for (z=0;z<mmp->m;z++) {
        temp += mmp->M1[y*mmp->m+z]*mmp->M2[z*mmp->k+x];
      }
      mmp->M[y*mmp->k+x] = temp;
      }
      else{
       // printf("%i,%i ALREADY calculated________\n",y,x);
      }

    }
  }

  return (void*) 0;
}

