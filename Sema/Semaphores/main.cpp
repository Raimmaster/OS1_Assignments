#include <iostream>
#include "ReaderWriter.h"
#include "Philosophers.h"

using namespace std;

int main()
{
    //ReaderWriter rwSema;
    //rwSema.run();

    Philosophers philo;
    philo.run();

    return 0;
}
