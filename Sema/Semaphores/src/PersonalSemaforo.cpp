#include "PersonalSemaforo.h"

PersonalSemaforo::PersonalSemaforo() : Semaforo::Semaforo()
{

}


PersonalSemaforo::PersonalSemaforo(int value)
{
    this->value = value;
    this->wakeUps = 0;
    this->mutex = new Mutex();
    this->cond = new Cond();
}

PersonalSemaforo::~PersonalSemaforo()
{
    delete this->mutex;
    delete this->cond;
}


void PersonalSemaforo::wait()
{
    this->mutex->mutexLock();
    this->value--;

    if(this->value < 0){
        do {
            this->cond->condWait(this->mutex);
        }while(this->wakeUps < 1);
        this->wakeUps--;
    }

    this->mutex->mutexUnlock();
}

void PersonalSemaforo::signal()
{
    this->mutex->mutexLock();
    this->value++;

    if(this->value <= 0){
        this->wakeUps++;
        this->cond->condSignal();
    }

    this->mutex->mutexUnlock();
}
