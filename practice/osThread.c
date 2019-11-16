#include<MKL25Z4.h>

//red
void red_init(){
    SIM->SCGC5 |= (1<10);//select port b

    PORTB->PCR[18] |= (1<<8);//select pin 18 as gpio
    PORTB->PCR[18] &= 0xFFFFF9FF;

    PTB->PDDR |=(1<<18);//set as output
}

void red_on(){
    PTB->PCOR |=(1<<18); //clear - on
}

void delay_old(long long d){
    while(d){
        d--;
    }
}

void main(){
    SystemCoreClockUpdate();


}