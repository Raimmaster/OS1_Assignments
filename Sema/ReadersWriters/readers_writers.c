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
	sem_t can_read;
	pthread_mutex_t mutex;
} shared_buffer_t;

void* reader_func(void*);

shared_buffer_t shared_buff;

int main(int argc, char const *argv[])
{
	strcpy(shared_buff.buffer, "hola");

	pthread_t* t_reader = (pthread_t*)malloc(sizeof(pthread_t));
	pthread_t* t_writer = (pthread_t*)malloc(sizeof(pthread_t));

	create_readers(t_reader);
	create_writers(t_writer);

	pthread_join(*t_reader, NULL);
	pthread_join(*t_writer, NULL);

	free(t_reader);
	free(t_writer);

	return 0;
}

void create_readers(pthread_t* t_reader){
	int thread_index;
	for(thread_index = 0;
		thread_index < QUANT_READERS;
		++thread_index){
		pthread_create(t_reader, NULL, reader_func, (void*)&thread_index);
		printf("Creating reader!\n");
	}
}

void* reader_func(void* args){
	int r_index = *(int*)args;
	int i;
	for(i = 0; i < BUFF_SIZE; i++){
		sem_wait(&shared_buff.can_read);
	}
}