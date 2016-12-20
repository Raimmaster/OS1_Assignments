#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "C_Semaphore.h"
#define CANT_CHOPS 50

using namespace std;

class Philosophers
{
    public:
        C_Semaphore* chopsticks[CANT_CHOPS];
        Philosophers();
        void run();
        void eat(int philoIndex);
        virtual ~Philosophers();
    protected:
    private:
};

#endif // PHILOSOPHERS_H
