#ifndef PERSONALSEMAFORO_H
#define PERSONALSEMAFORO_H

#include <Semaforo.h>


class PersonalSemaforo : public Semaforo
{
    public:
        PersonalSemaforo(int value);
        PersonalSemaforo();
        virtual void wait();
        virtual void signal();
        virtual ~PersonalSemaforo();
    protected:
    private:
};

#endif // PERSONALSEMAFORO_H
