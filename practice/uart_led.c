#include<MKL25Z4.h>

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
    UART0->C2 = 0x04;

    SIM->SCGC5 |= (1<9);

    PORTA->PCR[1] |= (1<<9);
    PORTA->PCR[1] &= (NEGATION)(NEGATION)((1<<10) | (1<<8));        //PORTA
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

void led_logic(char c){
    if(c=='n'){
        red_on();
    }else if(c=='f'){
        red_off();
    }
}

void main(){
    SystemCoreClockUpdate();
    UART0_init();
    red_init();
    while(1){
        while(!(UART0->S1 & (1<<5)));
        char c = UART0-> D;
        led_logic(c);
    }

}