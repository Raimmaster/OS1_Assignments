#include "Mutex.h"

Mutex::Mutex()
{

    int n = pthread_mutex_init(this->&mutex, NULL);
    if(n != 0)
        perror("Mutex init failed!");
}

Mutex::~Mutex()
{
    //dtor
}

void Mutex::mutexLock(){
    int n = pthread_mutex_lock(this->&mutex);
    if(n != 0)
        perror("Mutex lock failed!");
}

void Mutex::mutexUnlock(){
    int n = pthread_mutex_unlock(this->&mutex);
    if (n != 0)
        perror("Mutex unlock failed!");
}
