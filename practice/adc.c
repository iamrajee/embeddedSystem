#include<MKL25Z4.h>

//to much sc

void ADC0_init(){
    //exmg
    //ex27 same sc2bc cfg1 one-O-one
    SIM->SCGC6 |= (1<<27);

    SIM->SCGC5 |=(1<<10);
    PORTB->PCR[1] |=(1<<8);             //portb,  1
    PORTB->PCR[1] &=0xFFFFFF9F;

    ADC0->SC2  &= 0xFFFFFFBC;           //&
    ADC0->CFG1 = 0b01000100;
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

void delay_old(long long d){
    while(d){
        d--;
    }
}

void main(){
    SystemCoreClockUpdate();
    red_init();
    ADC0_init();

    while(1){
        ADC0->SC[0] = 9;
        while(!(ADC0->SC[0] & (1<<7)));
        int result = ADC0->R[0] & 0xFFF;
        if(result<(1<<12)/3){
            //odfd
        }
        //
        //
    }

}