#include <stdio.h>


void print_matrix(int n, int m, int *M);

void mmul(int n, int m, int k, int *M1, int *M2, int *M);

int main()
{
  int A []= {/* 3x4-Matrix  */
    1,2,-1,1,
    0,1,2,-2,
    2,-1,0,-3
  };

  int B [] = { /* 4x2-Matrix */
    1,-2,
    0,-1,
    1,1,
    1,0
  };

  int C[6]; /* 3x2-Matrix */

  print_matrix(3,4,A);
  print_matrix(4,2,B);

  mmul(3,4,2,A,B,C);

  print_matrix(3,2,C);

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

void mmul(int n, int m, int k, int *M1, int *M2, int *M)
{
  int x;
  int y;
  int z;
  int temp;
  for (y=0;y<n;y++) {
    for (x=0;x<k;x++) {
      temp = 0;
      for (z=0;z<m;z++) {
	temp += M1[y*m+z]*M2[z*k+x];
      }
      M[y*k+x] = temp;
    }
  }
}
