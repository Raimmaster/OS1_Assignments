#ifndef SEMAFORO_H
#define SEMAFORO_H


class Semaforo
{
    public:
        int value, wakeUps;
        Mutex* mutex;
        Cond *cond;
        Semaforo(int value);
        virtual void wait() = 0;
        virtual void signal() = 0;
        virtual ~Semaforo();
    protected:
    private:
};

#endif // SEMAFORO_H
