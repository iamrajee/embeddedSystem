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
    UART0->C2 = 0x08;                       //08

    SIM->SCGC5 |= (1<9);

    PORTA->PCR[2] |= (1<<9);
    PORTA->PCR[2] &= (NEGATION)(NEGATION)((1<<10) | (1<<8));     //2
}

void UART0_Handler(){

}

void main(){
    SystemCoreClockUpdate();
    UART0_init();
    char *msg = "helloworld"
    while(1){
        int i=0;
        while(!(UART0->S1 & (1<<7)));          //7
        while(){
            UART0-> D = msg[i++];
        }
    }

}