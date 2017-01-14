
#include <cstdio>
#include "miosix.h"

using namespace std;
using namespace miosix;

bool status=false;
Thread *a=NULL;
Thread *b=NULL;
Thread *th3 = NULL;
Thread *th4 = NULL;
Thread *th5 = NULL;

void f(void *argv)
{
    for(;;)
    {
        status=true;
        long long t = getTime();
        Thread::nanoSleep(400000);
        t = getTime() - t;
        status=false;
        //delayMs(250);
    }
}

void f2(void *arg){
    for (;;)
        delayMs(500);
}

int main()
{
    a=Thread::getCurrentThread();
    th3=Thread::create(f2,STACK_MIN);
    b=Thread::create(f,STACK_MIN,ControlSchedulerPriority(MAIN_PRIORITY,REALTIME_PRIORITY_IMMEDIATE));
    th4=Thread::create(f2,STACK_MIN);
    th5=Thread::create(f2,STACK_MIN);
    
    for(;;) delayMs(500);
}
