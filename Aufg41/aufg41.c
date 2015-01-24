#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *printer();
int cnt = 0;

int main(void) {
  pthread_t thread1, thread2;
  printer();
  pthread_create( &thread1, NULL, printer, NULL);
  //sleep(1);
  pthread_create( &thread2, NULL, printer, NULL);
  pthread_join( thread1, NULL);
  pthread_join( thread2, NULL);
}

void *printer() {
  sleep(1);
  printf("cnt = %d, thread_pid = %5d, my_pid = %5d\n", cnt, getppid(), getpid());
  cnt++;
}
