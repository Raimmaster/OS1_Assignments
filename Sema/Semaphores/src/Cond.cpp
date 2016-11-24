#include "Cond.h"

Cond::Cond()
{
    int n = pthread_cond_init(&this->cond, NULL);
    if(n != 0)
        perror("Cond init failed!");
}

Cond::~Cond()
{
    //dtor
}

void Cond::condWait(Mutex* mutex){
    int n = pthread_cond_wait(&this->cond, &mutex->mutex);
    if(n != 0)
        perror("Cond wait failed!");
}

void Cond::condSignal(){
    int n = pthread_cond_signal(&this->cond);
    if(n != 0)
        perror("Cond signal failed!");
}
