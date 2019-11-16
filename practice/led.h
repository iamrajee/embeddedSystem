#include<MKL25Z4.h>

//all
void led_init(){
    SIM->SCGC5 |= (1<10);//select port b

    PORTB->PCR[18] |= (1<<8);//select pin 18 as gpio
    PORTB->PCR[18] &= 0xFFFFF9FF;

    PTB->PDDR |=(1<<18);//set as output
}

void led_on(int led){
    switch (led)
    {
    case 0: PTB->PCOR |= (1<<18);
    //case 1: 
    //case 2:
    default:
        break;
    }
}

void led_off(int led){
    switch (led)
    {
    case 0: PTB->PCOR |= (1<<18);
    //case 1: 
    //case 2:
    default:
        break;
    }
}

void delay_old(long long d){
    while(d){
        d--;
    }
}

void main(){
    SystemCoreClockUpdate();


}