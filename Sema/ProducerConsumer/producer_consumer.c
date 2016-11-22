#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFF_SIZE 5
#define QUANT_PROD 1
#define QUANT_CONSUM 5
#define QUANT_ITEMS 4

typedef struct {
	int buffer[BUFF_SIZE];
	int index_first_empty_slot;
	int index_first_full_slot;
	sem_t fullSlots;
	sem_t emptySlots;
	pthread_mutex_t mutex;
} shared_buffer_t;

void* producer_func(void* args);
void* consumer_func(void* args);

shared_buffer_t shared_struct;

int main(int argc, char const *argv[])
{
	pthread_t t_producer, t_consumer;
	int thread_index;

	sem_init(&shared_struct.fullSlots, 0, 0);
	sem_init(&shared_struct.emptySlots, 0, 0);
	pthread_mutex_init(&shared_struct.mutex, NULL);

	for(thread_index = 0; 
		thread_index < QUANT_PROD; 
		thread_index++){
		pthread_create(&t_producer, NULL, producer_func, (void*)&thread_index);
	}

	for(thread_index = 0; 
		thread_index < QUANT_CONSUM; 
		thread_index++){
		pthread_create(&t_consumer, NULL, consumer_func, (void*)&thread_index);
	}

	pthread_join(t_producer, NULL);
	pthread_join(t_consumer, NULL);

	return 0;
}

void* producer_func(void* args){
	int p_index = *(int*)args;
	int i;
	for (i = 0; i < QUANT_ITEMS * QUANT_CONSUM; ++i)
	{
		int item = i;
		sem_wait(&shared_struct.emptySlots);
		pthread_mutex_lock(&shared_struct.mutex);
		//PRODUCTION CODE
		shared_struct.buffer[shared_struct.index_first_empty_slot] = item;
		shared_struct.index_first_empty_slot = (shared_struct.index_first_empty_slot + 1) % BUFF_SIZE;
		fflush(stdout);
		pthread_mutex_unlock(&shared_struct.mutex);
		sem_post(&shared_struct.fullSlots);
	}
}

void* consumer_func(void* args){

}