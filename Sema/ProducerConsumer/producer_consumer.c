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
	sem_t full_slots;
	sem_t empty_slots;
	pthread_mutex_t mutex;
} shared_buffer_t;

void* producer_func(void* args);
void* consumer_func(void* args);
void create_producers(pthread_t*);
void create_consumers(pthread_t*);

shared_buffer_t shared_struct;

int main(int argc, char const *argv[])
{
	pthread_t* t_producer = (pthread_t*)malloc(sizeof(pthread_t)); 
	pthread_t* t_consumer = (pthread_t*)malloc(sizeof(pthread_t) * QUANT_CONSUM);

	sem_init(&shared_struct.full_slots, 0, 0);
	sem_init(&shared_struct.empty_slots, 0, BUFF_SIZE);
	pthread_mutex_init(&shared_struct.mutex, NULL);	

	create_producers(t_producer);
	create_consumers(t_consumer);

	pthread_join(*t_producer, NULL);
	pthread_join(*t_consumer, NULL);

	free(t_producer);
	free(t_consumer);

	return 0;
}

void create_producers(pthread_t* t_producer){
	int thread_index;
	for(thread_index = 0; 
		thread_index < QUANT_PROD; 
		++thread_index){
		pthread_create(t_producer, NULL, producer_func, (void*)&thread_index);
		printf("Creating producers!\n");	
	}	
}

void create_consumers(pthread_t* t_consumer){
	int thread_index;

	for(thread_index = 0; 
		thread_index < QUANT_CONSUM; 
		++thread_index){
		pthread_create(&t_consumer[thread_index], NULL, consumer_func, (void*)&thread_index);
		printf("Creating consumers!\n");
	}
}

void* producer_func(void* args){
	int p_index = *(int*)args;
	int i, item;
	for (i = 0; i < QUANT_ITEMS * QUANT_CONSUM; ++i)
	{
		item = i;
		sem_wait(&shared_struct.empty_slots);
		pthread_mutex_lock(&shared_struct.mutex);
		shared_struct.buffer[shared_struct.index_first_empty_slot] = item;
		shared_struct.index_first_empty_slot = 
			(shared_struct.index_first_empty_slot + 1) % BUFF_SIZE;
		printf("***\tProducer: %d making %d\n", p_index, item);
		fflush(stdout);
		pthread_mutex_unlock(&shared_struct.mutex);
		sem_post(&shared_struct.full_slots);
		if(!(i % 2))
			sleep(1);
	}
}

void* consumer_func(void* args){
	int c_index = *(int*)args;
	int item, i;
	for (i = QUANT_ITEMS; i > 0; --i)
	{
		sem_wait(&shared_struct.full_slots);
		pthread_mutex_lock(&shared_struct.mutex);
		item = shared_struct.buffer[shared_struct.index_first_full_slot];
		shared_struct.index_first_full_slot = 
			(shared_struct.index_first_full_slot + 1) % BUFF_SIZE;
		printf("Consumer: %d eating %d\n", c_index, item);
		fflush(stdout);
		pthread_mutex_unlock(&shared_struct.mutex);
		sem_post(&shared_struct.empty_slots);
		if(!(i % 2))
			sleep(1);
	}
}