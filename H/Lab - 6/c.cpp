#include<MKL25Z4.h>

static unsigned volatile int delayCounter = 0;

void UART0_init() {
    // enabling UART0 by setting the corresponding bit in SCGC4 register
    SIM->SCGC4 |= 1 << 10;
    
    // enable the clock at UART0 from FLL or PLL/2 by putting 01 at bit
    // positions 27 and 26 in SOPT2 registers
    SIM->SOPT2 |= 1 << 26;
    SIM->SOPT2 &= ~(1 << 27);
    
    /*
    SBR = (clock frequency = 22000000) / (OSR * (baud rate = 57600))
    clock frequency and baud rate are fixed so we need only OSR or SBR
    SBR is of 13 bits and we set its value using the following registers -
    SBR[7:0] = BDL[7:0] and SBR[12:8] = BDH[4:0]
    */
    
    // disable all the operation modes in UART0
    UART0->C2 = 0x00;
    
    // SBR setting for baud rate of 57600 (and OSR = 16)
    UART0->BDH = 0x00;
    UART0->BDL = 0x18;
    UART0->C4 = 0x0F; // for an OSR of 16
    UART0->C1 = 0x00; // no parity
    
    // activate the receiver of UART0 (with interrupt enabled)
    UART0->C2 = 0x36;
    
    // activating port A
    SIM->SCGC5 |= 1 << 9;
    // configuring PTA1 as UART_Tx by putting 010 at bit positions 10 to 8 in PCR for PORT A1
    /*
    Note that we can also do this using alternative 4 for PORTE21
    But here we are using alternative 1 for PORTA1 because it is connected to USB port
    whereas PORTE20 is not
    */
    
    PORTA->PCR[1] &= ~(7 << 8);
    PORTA->PCR[1] |= 1 << 9;
    
    
    NVIC->ISER[0] = 0x00001000;
}

void led_red_init() {
    SIM->SCGC5 |= 1 << 10; // will activate the port B
    
    // set the pin as gpio
    PORTB->PCR[18] &= 0xFFFFF8FF; // set 8th, 9th and 10th bit of PCR[18] to 0
    PORTB->PCR[18] |= 1 << 8; // set 8th bit of PCR[18] to 1
    
    // set the port as output port
    PTB->PDDR |= 1 << 18; // set the 18th bit of PDDR to 1 for output
}

void led_red_on() {
    // clear the 18th bit of PDOR register
    PTB->PCOR |= 1 << 18; // set the 18th bit of PCOR to 1
}

void led_red_off() {
    // toggle the 18th bit of PDOR register
    PTB->PTOR |= 1 << 18;
}

void led_green_init() {
    SIM->SCGC5 |= 1 << 10; // will activate the port B
    
    // set the pin as gpio
    PORTB->PCR[19] &= 0xFFFFF8FF; // set 8th, 9th and 10th bit of PCR[19] to 0
    PORTB->PCR[19] |= 1 << 8; // set 8th bit of PCR[19] to 1
    
    // set the port as output port
    PTB->PDDR |= 1 << 19; // set the 19th bit of PDDR to 1 for output
}

void led_green_on() {
    // clear the 18th bit of PDOR register
    PTB->PCOR |= 1 << 19; // set the 19th bit of PCOR to 1
}

void led_green_off() {
    // toggle the 18th bit of PDOR register
    PTB->PTOR |= 1 << 19;
}

void led_blue_init() {
    SIM->SCGC5 |= 1 << 12; // will activate the port D
    
    // set the pin as gpio
    PORTD->PCR[1] &= 0xFFFFF8FF; // set 8th, 9th and 10th bit of PCR[1] to 0
    PORTD->PCR[1] |= 1 << 8; // set 8th bit of PCR[1] to 1
    
    // set the port as output port
    PTD->PDDR |= 1 << 1; // set the 1th bit of PDDR to 1 for output
}

void led_blue_on() {
    // clear the 18th bit of PDOR register
    PTD->PCOR |= 1 << 1; // set the 1th bit of PCOR to 1
}

void led_blue_off() {
    // toggle the 18th bit of PDOR register
    PTD->PTOR |= 1 << 1;
}

void delay(int ms) {
    while(ms--);
}

void UART0_IRQHandler() {
    char ch = UART0->D;
    if(ch == 'A') led_red_on(); delay(1000000); led_red_off();
    else if(ch == 'B') led_green_on(); delay(1000000); led_green_off();
    else if(ch == 'C') led_blue_on(); delay(1000000); led_blue_off();
}

int main() {
    SystemCoreClockUpdate(); // updating the clock from PLL
    UART0_init();
    
    led_red_init(); led_red_off();
    led_green_init(); led_green_off();
    led_blue_init(); led_blue_off();
    
    while(1);
}
