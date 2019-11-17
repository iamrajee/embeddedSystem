#include<MKL25Z4.h>

// ============================================================================================
void led_red_init() {
    SIM->SCGC5 |= 1 << 10;	        // will activate the port B
    
    // set the pin as gpio
    PORTB->PCR[18] &= 0xFFFFF8FF;   // set 8th, 9th and 10th bit of PCR[18] to 0
    PORTB->PCR[18] |= 1 << 8;       // set 8th bit of PCR[18] to 1
    
    // set the port as output port
    PTB->PDDR |= 1 << 18;           // set the 18th bit of PDDR to 1 for output
}

void led_red_on() {
    // clear the 18th bit of PDOR register
    PTB->PCOR |= 1 << 18;           // set the 18th bit of PCOR to 1	
}

void led_red_off() {
    // toggle the 18th bit of PDOR register
    PTB->PTOR |= 1 << 18;
}
// ============================================================================================


// ============================================================================================
void led_green_init() {
    SIM->SCGC5 |= 1 << 10; 	        // will activate the port B
    
    // set the pin as gpio
    PORTB->PCR[19] &= 0xFFFFF8FF;   // set 8th, 9th and 10th bit of PCR[19] to 0
    PORTB->PCR[19] |= 1 << 8;       // set 8th bit of PCR[19] to 1
    
    // set the port as output port
    PTB->PDDR |= 1 << 19;           // set the 19th bit of PDDR to 1 for output
}

void led_green_on() {
    // clear the 18th bit of PDOR register
    PTB->PCOR |= 1 << 19;           // set the 19th bit of PCOR to 1	
}

void led_green_off() {
    // toggle the 18th bit of PDOR register
    PTB->PTOR |= 1 << 19;
}
// ============================================================================================


// ============================================================================================
void led_blue_init() {
    SIM->SCGC5 |= 1 << 12;	        // will activate the port D
    
    // set the pin as gpio
    PORTD->PCR[1] &= 0xFFFFF8FF;    // set 8th, 9th and 10th bit of PCR[1] to 0
    PORTD->PCR[1] |= 1 << 8;        // set 8th bit of PCR[1] to 1
    
    // set the port as output port
    PTD->PDDR |= 1 << 1;            // set the 1th bit of PDDR to 1 for output
}

void led_blue_on() {
    // clear the 18th bit of PDOR register
    PTD->PCOR |= 1 << 1;            // set the 1th bit of PCOR to 1	
}

void led_blue_off() {
    // toggle the 18th bit of PDOR register
    PTD->PTOR |= 1 << 1;
}
// ============================================================================================


void delay(int cycles) {
    while(cycles--);
}


int main() {
    SystemCoreClockUpdate();	    // updating the clock from PLL
    led_red_init();
    led_green_init();
    led_blue_init();
    while(1) {
        led_red_on(), delay(1000000), led_red_off();
        led_green_on(), delay(1000000), led_green_off();
        led_blue_on(), delay(1000000), led_blue_off();
    }
}
