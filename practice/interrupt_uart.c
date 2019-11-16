#include<MKL25Z4.h>

//global
static unsigned volatile int delayCtr = 0;

void UART0_init(){
    //SPOT C2 BDH BDL(18) C4(F) 1 2(4) 5 PCR
    SIM->SCGC4 |= (1<10);
    SIM->SOPT2 |= (1<<26);//27TH,26TH
    SIM->SOPT2 &= (NEGATION)(1<<27);

    UART0->C2 = 0x00;
    UART0->BDH = 0x00;
    UART0->BDL = 0x18;
    UART0->C4 = 0x0F;
    UART0->C1 = 0x00;
    UART0->C2 = 0x36;                       //36

    SIM->SCGC5 |= (1<9);

    PORTA->PCR[1] |= (1<<9);
    PORTA->PCR[1] &= (NEGATION)((1<<10) | (1<<8));     //1

    NVIC->ISER[0] = 0b00001000;            //nvic !!! =
}

void UART0_IQRHandler(){
    char c = UART0->D;
    if(c=='r'){
        red_on();
        //odfd
    }else if(c=='g'){

    }
}

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

    // while(1){
    //     red_on();
    //     delay_better(1e6);
    //     red_off();
    //     delay_better(1e6);
    // }

    UART0_init();
    while(1);


}