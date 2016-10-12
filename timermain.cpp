#include <cstdlib>
#include <cstdio>
#include "miosix.h"
//#include "miosix/arch/cortexM3_efm32gg/efm32gg332f1024_wandstem/interfaces-impl/gpio_timer.h"
//#include <e20/e20.h>
//#include "miosix/arch/cortexM3_efm32gg/efm32gg332f1024_wandstem/interfaces-impl/high_resolution_timer_base.cpp"
#include "debugpin.h"
#include "/home/fabiuz/NetBeansProjects/miosix-kernel-unofficial/miosix/arch/cortexM3_efm32gg/efm32gg332f1024_wandstem/interfaces-impl/high_resolution_timer_base.cpp"

using namespace std;
using namespace miosix;

//FixedEventQueue<100,12> queue;
int global=0;

void ContextSwitchTest1(){
    initDebugPins();
    for (;;){
	HighPin<debug2> hp;
    }
}
static void ContextSwitchTest2(void* v){
    initDebugPins();
    for (long long i=1;;i+=5){
	HighPin<debug2> hp;
	Thread::sleepUntil(i);
    }
}


int main(int argc, char** argv) {
    printf("Hello world\n");
    
    /*expansion::gpio0::mode(Mode::OUTPUT); //i have to enable and configure each single GPIO on the board
    expansion::gpio10::mode(Mode::INPUT);
    testPin::low();
    
    {
        FastInterruptDisableLock dLock;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1; //power up the timer, each peripheral is turned off by default
    }

    TIMER1->CNT = 0;
    TIMER1->CTRL |= TIMER_CTRL_PRESC_DIV1;  //Timer runs @48MHz
    TIMER1->TOP = 0xFFFF; //auto reload if counter register go in overflow
    
    
    
    //channel 0 is transceiver timestamp input, so is set as input capture on rising edges
    TIMER1->CC[2].CTRL |= TIMER_CC_CTRL_MODE_INPUTCAPTURE |
                          TIMER_CC_CTRL_ICEDGE_RISING |
                          TIMER_CC_CTRL_INSEL_PIN;    
    
    TIMER1->ROUTE=TIMER_ROUTE_CC2PEN
                | TIMER_ROUTE_LOCATION_LOC1; //connect the TIMER1 with the correct pin on the board

    TIMER1->CMD |= TIMER_CMD_START;
   
    for(int i=0;TIMER1->CC[2].CCV==0;i++){
        if(i==3000)
            testPin::high();
        printf("%lu %lu %lu i=%d\n",TIMER1->CNT,TIMER1->CC[2].CCV,TIMER1->STATUS,i);
    }
    printf("TImer scattato CCV: %lu\n",TIMER1->CC[2].CCV);
    
    printf("Provo ad abilitare un interrupt:\n");
    testPin::low();
    TIMER1->CC[2].CCV=0;
    TIMER1->CC[2].CCVB=0;
    printf("IEN=%lu=0? IF=%lu\n",TIMER1->IEN,TIMER1->IF);
    TIMER1->IEN= TIMER_IEN_CC2;
    TIMER1->IFC=TIMER_IFC_OF|TIMER_IFC_CC2 ;
    printf("IEN=%lu=0? IF=%lu\n",TIMER1->IEN,TIMER1->IF);
    
    NVIC_SetPriority(TIMER1_IRQn,5); //Low priority    
    NVIC_ClearPendingIRQ(TIMER1_IRQn);
    NVIC_EnableIRQ(TIMER1_IRQn);
    
    printf("Inizio contatore:\n");
    for(int i=0;TIMER1->CC[2].CCV==0;i++){
        if(i==8) printf("IF=%lu\n",TIMER1->IF);
        if(i==10)
            testPin::high();
        printf("%lu %lu %lu i=%d\n",TIMER1->CNT,TIMER1->CC[2].CCV,TIMER1->STATUS,i);
    }
    printf("IEN=%lu=0? IF=%lu  global=%d\n",TIMER1->IEN,TIMER1->IF,global);
    queue.runOne();
    
    
    
    printf("Continuo provando il chaining dei timer...\n");
    
    
    TIMER1->CMD |= TIMER_CMD_STOP;
    {
        FastInterruptDisableLock dLock;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER2; //power up the timer, each peripheral is turned off by default
    }
    TIMER2->CTRL |= TIMER_CTRL_CLKSEL_TIMEROUF
                 |  TIMER_CTRL_SYNC;
    TIMER2->TOP = 0xFFFF; 
    TIMER2->CNT = 0;
    TIMER1->CNT = 0;
    TIMER1->CMD |= TIMER_CMD_START;
    testPin::low();
    for(int i=0;i<20;i++){
        printf("TIMER2.TIMER1: %lu %lu\n",TIMER2->CNT,TIMER1->CNT);
    }
    
    */
    
    /* 
    printf("Chaining e lettura 32 bit di eventi GPIO");
    {
        FastInterruptDisableLock dLock;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1; //power up the timer, each peripheral is turned off by default
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER2;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER3;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_PRS;
    }
    
    TIMER2->CNT = 0;
    TIMER1->CNT = 0;
    TIMER3->CNT = 0;
    TIMER1->CMD = TIMER_CMD_STOP;
    TIMER2->CMD = TIMER_CMD_STOP;
    TIMER3->CMD = TIMER_CMD_STOP;
    
    TIMER1->CTRL |= TIMER_CTRL_SYNC;
    TIMER2->CTRL |= TIMER_CTRL_SYNC;
    TIMER3->CTRL |= TIMER_CTRL_CLKSEL_TIMEROUF
                 |  TIMER_CTRL_SYNC;
    
    TIMER1->CMD = TIMER_CMD_START;
    for(int i=0;i<100000;i++){
        if(i%1000==0){
            TIMER1->CMD = TIMER_CMD_STOP;
            printf("%lu %lu %lu\n",TIMER1->CNT,TIMER2->CNT,TIMER3->CNT);
            TIMER1->CMD = TIMER_CMD_START;
        }
        
    }//è davvero sincrono!!
    TIMER1->CMD = TIMER_CMD_STOP;
    
    
    
    expansion::gpio0::mode(Mode::OUTPUT); //i have to enable and configure each single GPIO on the board
    expansion::gpio10::mode(Mode::INPUT);
    testPin::low();
    
    TIMER1->ROUTE=TIMER_ROUTE_CC2PEN
                | TIMER_ROUTE_LOCATION_LOC1;
    //Configuro la modalità input
    TIMER1->CC[2].CTRL=TIMER_CC_CTRL_MODE_INPUTCAPTURE |
                          TIMER_CC_CTRL_ICEDGE_RISING |
                          TIMER_CC_CTRL_INSEL_PIN; 
    //TIMER1->IEN = TIMER_IEN_CC2;
    //Configuro PRS Timer 3 deve essere un consumer, timer1/2 producer, TIMER3 keeps the most significative part
    //TIMER1->CC2 as producer, i have to specify the event i'm interest in    
    PRS->CH[0].CTRL=PRS_CH_CTRL_SOURCESEL_TIMER1
                    |PRS_CH_CTRL_SIGSEL_TIMER1CC2;
    
    //TIMER3->CC0 as consumer
    TIMER3->CC[0].CTRL|=TIMER_CC_CTRL_PRSSEL_PRSCH0
                    |   TIMER_CC_CTRL_INSEL_PRS
                    |   TIMER_CC_CTRL_ICEDGE_BOTH
                    |   TIMER_CC_CTRL_MODE_INPUTCAPTURE;
    
    
    TIMER1->CMD |= TIMER_CMD_START;
    for(int i=0;i<25;i++){
        if(i==10) testPin::high();
        if(i==14) testPin::low();
        if(i==20) testPin::high();
        printf("TIMER1, TIMER3: %lu %lu %lu\n",TIMER1->CC[2].CCV,TIMER3->CC[0].CCV,TIMER3->CNT);
    }
    */
    
    
    //Test con Output/Compare. Se imposto un tempo a 32 bit questo deve alzare un pin al momento giusto
    //printf("Provo il chaining con output compare\n");
    /*
    {
        FastInterruptDisableLock dLock;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER1; //power up the timer, each peripheral is turned off by default
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER2;
        CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_TIMER3;
    }
    
    TIMER2->CNT = 0;
    TIMER1->CNT = 0;
    TIMER3->CNT = 0;
    TIMER1->CMD = TIMER_CMD_STOP;
    TIMER2->CMD = TIMER_CMD_STOP;
    TIMER3->CMD = TIMER_CMD_STOP;
    
    TIMER1->CTRL |= TIMER_CTRL_SYNC;
    TIMER2->CTRL |= TIMER_CTRL_SYNC;
    TIMER3->CTRL |= TIMER_CTRL_CLKSEL_TIMEROUF
                 |  TIMER_CTRL_SYNC;
    
    TIMER1->CC[2].CCV=10;
    TIMER2->CC[2].CCV=834;
    TIMER1->CC[2].CTRL=TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;
    TIMER2->CC[2].CTRL=TIMER_CC_CTRL_MODE_OUTPUTCOMPARE;
    //TIMER3->IEN=TIMER_IEN_OF;
    
    //NVIC_SetPriority(TIMER1_IRQn,5); //Low priority    
    //NVIC_ClearPendingIRQ(TIMER1_IRQn);
    //NVIC_EnableIRQ(TIMER1_IRQn);
    NVIC_SetPriority(TIMER3_IRQn,5); //Low priority    
    NVIC_ClearPendingIRQ(TIMER3_IRQn);
    NVIC_EnableIRQ(TIMER3_IRQn);
    
    TIMER1->CMD = TIMER_CMD_START;
    
    printf("TIMER1->IF=%lu\n",TIMER1->IF);
    for(;TIMER3->CNT<1000;) 
        if((TIMER3->CNT)%100==0){
            printf("TIMER3: %lu,TIMER1->IF=%lu\n",TIMER3->CNT,TIMER3->IF);
	    if(TIMER3->CNT==900){
		TIMER3->IEN=TIMER_IEN_CC2;
	    }
	}
    printf("\nFine loop\n");
    //queue.runOne();
    printf("TIMER1->IF=%lu\n",TIMER1->IF);
    //queue.runOne();
    */
    //delayMs(10000);
    //printf("%u\n",ms32time);
    //delayMs(80000);
    
    /*for(;;){
        //printf("\n",);
        printf("%lu %llu %d %llu\n",TIMER3->CNT,c.getCurrentTick()>>32,global,ms32time);
    }*/
    
    
    
    
    // Test per GPIOTimer trigger OUTPUT mode
    //ContextSwitchTest2(0);
    Thread *t=Thread::create(ContextSwitchTest2,512);
    
    expansion::gpio0::mode(Mode::INPUT);
    expansion::gpio10::mode(Mode::OUTPUT);
    expansion::gpio10::low();
    
    GPIOtimer& g=GPIOtimer::instance();
    HighResolutionTimerBase& h=HighResolutionTimerBase::instance();
    bool flag=true,exit=false;
    
    //	Test cases  in tick:
    //	#	    Dec				Hex			    Late
    //	0	    1				0x0000001		    true
    //	1	    40000			0x00009C40		    true
    //	2 relative  step of 100			step of 0x64		    false/true about 130 lates
    //	3	    200000000			0x0BEBC200		    false
    //	4	    2000000000			0x77359400		    false
    //	5	    4294950912			0xFFFFC000		    false
    //	6	    4294967296			0x100000000		    true
    //	7	    4294975487			0x100006FFF		    true
    long long values[8];
    values[0]=0x00000001;
    values[1]=0x00009C40;
    values[2]=0x00000064;
    values[3]=0x0BEBC200;
    values[4]=0x77359400;
    values[5]=0xFFFFC000; //Mettere 0xFFFFC000 per farlo funzionare, perchè????????????
    values[6]=0x100000000;
    values[7]=0x10A001FFF;
    bool result;
    for(int i=0,j=0;i<8;i++){
	
	if(i==0||i==1||i==3||i==4||i==5||i==6||i==7){
	    printf("---------Test #%d(%d), set time:%llu, now:%llu\n",i,j,values[i],h.getCurrentTick());
	    result=g.absoluteWaitTrigger(values[i]);
	}else{
	    if(j==0){
		printf("---------Test #%d(%d), set time:%llu, now:%llu\n",i,j,values[i],h.getCurrentTick());
	    }
	    if(j<1000){
		result=g.waitTrigger(values[i]+j);
		j++;
		if(j<1000){
		    i--;
		}else{
		    printf("Number of late time %llu\n",GPIOtimer::aux1);
		}
	    }
	}
	{
	    
	    while(1){
	    if(expansion::gpio0::value()){break;}
	    }
	}
	
	
	if(i==0||(i==1&&j==0)||i==3||i==4||i==5||i==6||i==7){
	    printf("--------Fine ciclo. result: %d\n",result);
	}else{
	    if(result==0){
		GPIOtimer::aux1++;
	    }
	}
	expansion::gpio10::low();
    }
    
    
    /*
    GPIOtimer& g=GPIOtimer::instance();
    delayMs(2000);
    printf("Inizio...\n");
    WaitResult w=g.absoluteWaitTimeoutOrEvent(536870919); //Only event
    printf("End... %d\n",w);
    */
    //ContextSwitchTest2();
    
    
    printf("\n\n\n\n,.-\n");
    return 0;
}
