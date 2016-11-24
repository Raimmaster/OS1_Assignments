#include "C_Semaphore.h"

C_Semaphore::C_Semaphore(int value)
{
    sem_init(&this->mutex, 0, value);
}

C_Semaphore::~C_Semaphore()
{
    sem_close(&this->mutex);
}

void C_Semaphore::wait(){
    sem_wait(&this->mutex);
}

void C_Semaphore::signal(){
    sem_post(&this->mutex);
}
