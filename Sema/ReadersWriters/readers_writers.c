#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define QUANT_READERS 5
#define QUANT_WRITERS 3
#define BUFF_SIZE	  8

typedef struct 
{
	char buffer[BUFF_SIZE];
	pthread_mutex_t mutex;
} shared_buffer_t;

int main(int argc, char const *argv[])
{
	
	return 0;
}