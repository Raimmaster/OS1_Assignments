#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define QUANT_PROD 1
#define QUANT_CONSUM 5
#define QUANT_ITEMS 4

void* producer_func(void* args);
void* consumer_func(void* args);

int main(int argc, char const *argv[])
{
	pthread_t t_producer, t_consumer;
	int thread_index;

	sem_init(&shared_vars.fullSlots, 0, 0);
	sem_init(&shared_vars.emptySlots, 0, 0);
	pthread_mutex_init(&shared.mutex, NULL);

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

}

void* consumer_func(void* args){

}