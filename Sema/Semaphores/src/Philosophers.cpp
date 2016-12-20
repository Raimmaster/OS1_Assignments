#include "Philosophers.h"


Philosophers::Philosophers()
{

    for(int i = 0; i < CANT_CHOPS; ++i)
    {
        chopsticks[i] = new C_Semaphore(1);
    }
}

Philosophers::~Philosophers()
{
    for(int i = 0; i < CANT_CHOPS; ++i)
    {
        delete chopsticks[i];
    }
}

void Philosophers::eat(int philoIndex)
{
    bool hungry = false;
    for(int i = 0; ; ++i)
    {
        this->chopsticks[philoIndex]->wait();
        this->chopsticks[(philoIndex + 1) % CANT_CHOPS]->wait();
        
        cout<<"Philo started: "<<philoIndex<<" eating!"<<endl;
        sleep(5);
        cout<<"Philo finished: "<<philoIndex<<" eating!"<<endl;
        
        this->chopsticks[philoIndex]->signal();
        this->chopsticks[(philoIndex + 1) % CANT_CHOPS]->signal();
        
        sleep(1);
    }
}


void Philosophers::run()
{
    thread* readers[CANT_CHOPS];
    thread* writers[CANT_CHOPS];
    for(int i = 0; i < CANT_CHOPS; ++i)
    {
        readers[i] = new thread(&Philosophers::eat, this, i);
    }
    while(true);
}
