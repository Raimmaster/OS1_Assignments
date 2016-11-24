#ifndef C_SEMAPHORE_H
#define C_SEMAPHORE_H
#include <semaphore.h>

class C_Semaphore
{
    public:
        C_Semaphore(int value);
        virtual void wait();
        virtual void signal();
        virtual ~C_Semaphore();
        sem_t mutex;
    protected:
    private:
};

#endif // C_SEMAPHORE_H
