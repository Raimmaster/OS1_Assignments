#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 5

int cnt = 0;
sem_t mutex;

void* ping_pong(void* arg){
  int i = 0;
  for(i = 0; i < NITER; i++)
  {
    sem_wait(&mutex);
    if(cnt++ % 2 == 0)
      printf("Ping!\n");
    else
      printf("Pong!\n");
    sem_post(&mutex);
  }
}

int main(int argc, char * argv[])
{

    sem_init(&mutex, 0, 1);

    pthread_t ping, pong;

    if(pthread_create(&ping, NULL, ping_pong, NULL))
    {
      printf("\n ERROR creating thread ping");
      exit(1);
    }

    if(pthread_create(&pong, NULL, ping_pong, NULL))
    {
      printf("\n ERROR creating thread pong");
      exit(1);
    }

    if(pthread_join(ping, NULL))
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(pong, NULL))
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    printf("Cnt is: %d\n", cnt);
    pthread_exit(NULL);
}