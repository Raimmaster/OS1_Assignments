#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 5

int cnt = 0;
sem_t mutex;

void* ping_pong(void* arg){
  int i = 0;
  int value = *(int*)arg;
  for(i = 0; i < NITER; i++)
  {
    usleep(1);
    sem_wait(&mutex);
    int val;
    sem_getvalue(&mutex, &val);
    //printf("Val sem_wait: %d\n", val);
    if(cnt++ % 2 == 0)
      printf("Ping! from %d\n", value);
    else
      printf("Pong! from %d\n", value);
    sem_post(&mutex);
    sem_getvalue(&mutex, &val);
    //printf("Val sem_post: %d\n", val);
  }
}

int main(int argc, char * argv[])
{

    sem_init(&mutex, 0, 1);

    pthread_t ping, pong;
    int value = 5;
    int val2 = 10;
    if(pthread_create(&ping, NULL, ping_pong, (void*)&value))
    {
      printf("\n ERROR creating thread ping");
      exit(1);
    }

    if(pthread_create(&pong, NULL, ping_pong, (void*)&val2))
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

    sem_destroy(&mutex);

    return 0;
}