#include<MKL25Z4.h>

//global
static unsigned volatile int delayCtr = 0;

void SysTick_init(){
    SysTick->LOAD = 20971-1;
    SysTick->VAL = 0x00;
    SysTick->CTRL = 0x07;
}

void SysTick_Handler(){
    delayCtr++;
}

//red
void red_init(){
    SIM->SCGC5 |= (1<10);

    PORTB->PCR[18] |= (1<<8);
    PORTB->PCR[18] &= 0xFFFFFF9F;

    PTB->PDDR |=(1<<18);
}

void red_on(){
    PTB->PCOR |=(1<<18);
}

void red_on(){
    PTB->PDOR |=(1<<18);
}

void delay_old(long long d){
    while(d){
        d--;
    }
}

void delay_better(long long d){
    delayCtr=0;
    while(delayCtr < d);
}

void main(){
    SystemCoreClockUpdate();
    red_init();
    SysTick_init();

    while(1){
        red_on();
        delay_better(1e6);
        red_off();
        delay_better(1e6);
    }


}