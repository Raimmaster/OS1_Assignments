#ifndef COND_H
#define COND_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Mutex.h"

class Cond
{
    public:
        pthread_cond_t cond;
        Cond();
        void condWait(Mutex* mutex);
        void condSignal();
        virtual ~Cond();
    protected:
    private:
};

#endif // COND_H
