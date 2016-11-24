#include "PersonalSemaforo.h"

PersonalSemaforo::PersonalSemaforo(int value)
{
    this->value = value;
    this->wakeUps = 0;
    this->mutex = new Mutex();
    this->con = new Cond();
}

PersonalSemaforo::~PersonalSemaforo()
{
    delete this->mutex;
    delete this->cond;
}


void PersonalSemaforo::wait()
{
    mutex_lock(this->mutex);
    this->value--;

    if(this->value < 0){
        do {
            condWait(this->cond, this->mutex);
        }while(this->wakeUps < 1);
        this->wakeUps--;
    }

    mutexUnlock(this->mutex);
}

void PersonalSemaforo::signal()
{
    mutexLock(this->mutex);
    this->value++;

    if(this->value <= 0){
        this->wakeUps++;
        condSignal(this->cond);
    }

    mutexUnlock(this->mutex);
}
