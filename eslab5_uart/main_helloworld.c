//==============Transmitting Data 'Y' using UART0=====================//
#include <MKL25Z4.H>

void UART0_init(void){ //funtion defination
    SIM->SCGC4 |= (1<<10); // set 10th index(index start from 0) bit = 1, enable clock for UART0 by 1<<10 or 0x400
    SIM->SOPT2 |= (1<<26); // set 26th index bit = 1, Selecting MCGFLLCLK clock or MCGPLLCLK/2 as clock source 1<<26 or 0x04000000
    SIM->SOPT2 &= 0xF7FFFFFF; // set 27th index bit = 0, other undisturbed, F(0111)FFFFFF
    UART0->C2 = 0x00; // Transmitter, Receiver disabled
    UART0->BDH = 0x00; // Baudrate updated
    UART0->BDL = 0x18; //00001101, to write 24, SBR = (clock freq/(OSR*))
    UART0->C4 = 0x0F; //00001111, for OCR of 16, Setting OverSampling Ratio 01111
    UART0->C1 = 0x00; //00000000, no parity
    UART0->C2 = 0x08; //set 3rd index bit = 1, 00001000, Transmitter enabled &Receiver disabled
    SIM->SCGC5 |= (1<<9); //set 9th index bit = 0, Clock for PORT A Enabled
    PORTA->PCR[2] = (1<<9); //set 9th index bit = 0, MUXing PORT A to use as UART
    PORTA->PCR[2] = 0xFFFFFAFF; //reset
}

int main (void){
    UART0_init(); //Initiating UART0 as transmitter
    char *msg = "HELLO WORLD "; //msg
    int i=0;
    while (1){ //Infinite Loop
        while(msg[i]){
            while(!(UART0->S1 & 0x80));//In a loop till transmitting data buffer is not empty
            UART0->D = msg[i]; //Transmitting msg[i] via UART0
            i++;
        }
    }
}

