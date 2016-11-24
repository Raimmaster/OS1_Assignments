#ifndef READERWRITER_H
#define READERWRITER_H

#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "C_Semaphore.h"

using namespace std;

class ReaderWriter
{
    public:
        ReaderWriter();
        virtual ~ReaderWriter();
        void run();
        void readerFunc();
        void writerFunc();
    protected:
        C_Semaphore* rwMutex;
        C_Semaphore* mutex;
        string buffer;
        int readerCount;
    private:
};

#endif // READERWRITER_H
