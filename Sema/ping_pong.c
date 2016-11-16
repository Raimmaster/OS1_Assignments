#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 5

int cnt = 0;
sem_t ping_mutex, pong_mutex;

void* ping(void* arg){
  int i = 0;
  int value = *(int*)arg;
  for(i = 0; i < NITER; i++)
  {
    sem_wait(&pong_mutex);
    printf("Ping!\n");
    sem_post(&ping_mutex);
  }
}

void* pong(void* arg){
  int i = 0;
  int value = *(int*)arg;
  for(i = 0; i < NITER; i++)
  {
    sem_wait(&ping_mutex);
    printf("Pong!\n");
    sem_post(&pong_mutex);
  }
}


int main(int argc, char * argv[])
{

    sem_init(&ping_mutex, 0, 1);
    sem_init(&pong_mutex, 0, 1);

    pthread_t ping_thread, pong_thread;
    int value = 5;
    int val2 = 10;
    if(pthread_create(&ping, NULL, ping_thread, (void*)&value))
    {
      printf("\n ERROR creating thread ping");
      exit(1);
    }

    if(pthread_create(&pong, NULL, pong_thread, (void*)&val2))
    {
      printf("\n ERROR creating thread pong");
      exit(1);
    }

    if(pthread_join(ping_thread, NULL))
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(pong_thread, NULL))
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    printf("Cnt is: %d\n", cnt);
    pthread_exit(NULL);

    sem_destroy(&ping_mutex);
    sem_destroy(&pong_mutex);

    return 0;
}