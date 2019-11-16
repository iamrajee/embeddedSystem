#include <MKL25Z4.H>

void UART0_init(void){
    SIM->SCGC4 |= (1<<10); // set 10th index(index start from 0) bit = 1, enable clock for UART0 by 1<<10 or 0x400
    SIM->SOPT2 |= (1<<26); // set 26th index bit = 1, Selecting MCGFLLCLK clock or MCGPLLCLK/2 as clock source 1<<26 or 0x04000000
    SIM->SOPT2 &= 0xF7FFFFFF; // set 27th index bit = 0, other undisturbed, F(0111)FFFFFF
    UART0->C2 = 0x00; // Transmitter, Receiver disabled
    UART0->BDH = 0x00; // Baudrate updated
    UART0->BDL = 0x18; //00001101, to write 24, SBR = (clock freq/(OSR*))
    UART0->C4 = 0x0F; //00001111, for OCR of 16, Setting OverSampling Ratio 01111
    UART0->C1 = 0x00; //00000000, no parity
    UART0->C2 = 0x04; //set 3rd index bit = 1, 00001000, Transmitter disabled & Receiver enabled
    SIM->SCGC5 |= (1<<9); //set 9th index bit = 0, Clock for PORT A Enabled
    PORTA->PCR[1] = (1<<9); //set 9th index bit = 0, MUXing PORT A to use as UART
    PORTA->PCR[1] = 0xFFFFFAFF; //reset
}

void LED_init(void){//Initiating GREEN LED
    SIM->SCGC5 |= (1<<10); // enable clock to Port B
    PORTB->PCR[19] |= (1<<8); // MUXing PORT B to use as (PCR19 - 001)
    PORTB->PCR[19] &= 0xFFFFF9FF;
    PTB->PDDR |= (1<<19); //Setting Pin 19 as input and taking XOR
    PTB->PDOR |= (1<<19); //initially off, Corresponding bit 19 in PDORB is set to logic 1.
}

void LED_set(char value) {
    if (value =='g'){ //Green LED ON
        PTB->PCOR |= (1<<19); //Corresponding bit 19 in PDORB is cleared to logic 0
    }else if(value =='o'){ //Green LED OFF
        PTB->PDOR |= (1<<19); //Corresponding bit 19 in PDORB is set to logic 1.
    }
}

int main (void){
    SystemCoreClockUpdate();
    char c;
    UART0_init(); // Initiating UART0 as receiver
    LED_init(); // Initiating PTB18, PTB19 for turning on LED
    while (1) {
        while(!(UART0->S1 & (1<<5))); //Infinite loop till receiving data buffer is not empty
        c = UART0->D; //Receiving Values from Tera Terminal
        LED_set(c); //Running LED based on the the data received
    }
}