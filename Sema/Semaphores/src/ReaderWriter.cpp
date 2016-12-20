#include "ReaderWriter.h"
#define CANT_RWS 5

ReaderWriter::ReaderWriter()
{
    this->rwMutex = new C_Semaphore(1);
    this->mutex = new C_Semaphore(1);
    buffer = "Original string!";
    readerCount = 0;
}

ReaderWriter::~ReaderWriter()
{
    delete rwMutex;
    delete mutex;
}

void ReaderWriter::readerFunc(){
    cout<<"Reader: "<<readerCount<<endl;
    while(true){

        this->mutex->wait();
        if(++readerCount == 1){
            this->rwMutex->wait();
        }

        this->mutex->signal();

        cout<<"Reader: "<<readerCount<<" reading: "<<buffer<<endl;

        this->mutex->wait();
        if(--readerCount == 0){
            this->rwMutex->signal();
        }

        this->mutex->signal();

        sleep(1);
    }
}

void ReaderWriter::writerFunc(){
    int writeCount = 0;
    while(true){
        this->rwMutex->wait();
 
        string tempBuff = to_string(writeCount++);
        this->buffer = "Writer with ";
        this->buffer += tempBuff;

        this->rwMutex->signal();

        sleep(2);
    }
}

void ReaderWriter::run(){
    thread* readers[CANT_RWS];
    thread* writers[CANT_RWS];
    for(int i = 0; i < CANT_RWS; ++i)
    {
        readers[i] = new thread(&ReaderWriter::readerFunc, this);
        writers[i] = new thread(&ReaderWriter::writerFunc, this);
    }
    while(true);
    //reading.join();
    //writing.join();
}
