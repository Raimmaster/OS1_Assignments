#ifndef SEMAFORO_H
#define SEMAFORO_H

#include "Mutex.h"
#include "Cond.h"

class Semaforo
{
    public:
        int value, wakeUps;
        Mutex* mutex;
        Cond *cond;
        Semaforo();
        virtual void wait() = 0;
        virtual void signal() = 0;
        virtual ~Semaforo();
    protected:
    private:
};

#endif // SEMAFORO_H
