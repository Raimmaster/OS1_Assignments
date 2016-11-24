#ifndef MUTEX_H
#define MUTEX_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class Mutex
{
    public:
        pthread_mutex_t mutex;
        Mutex();
        void mutexLock();
        void mutexUnlock();
        virtual ~Mutex();
    protected:
    private:
};

#endif // MUTEX_H
