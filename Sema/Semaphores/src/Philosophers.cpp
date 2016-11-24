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
        hungry = i % CANT_CHOPS == 0;
        cout<<"Hungry: "<<hungry<<endl;
        //if(hungry){
        this->chopsticks[philoIndex]->wait();
        cout<<"Philo "<<philoIndex<<" picked up"<<philoIndex<<endl;
        this->chopsticks[(philoIndex + 1) % CANT_CHOPS]->wait();
        cout<<"Philo "<<philoIndex<<" picked up"<<((philoIndex + 1) % CANT_CHOPS)<<endl;
        cout<<"Philo: "<<philoIndex<<" eating!"<<endl;
        //usleep(1000);
        this->chopsticks[philoIndex]->signal();
        this->chopsticks[(philoIndex + 1) % CANT_CHOPS]->signal();
        //}
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
