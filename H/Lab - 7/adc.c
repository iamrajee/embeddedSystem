#include<MKL25Z4.h>

static volatile short data = 0;

void ADC0_init() {
    // disable clock gating to ADC0 to activate it
    SIM->SCGC6 |= (1 << 27);
    
    // activate port B
    SIM->SCGC5 |= 1 << 10;
    
    // set the pin as ADC0_SE9 (PCR[10-8] = 001)
    PORTB->PCR[1] &= 0xFFFFF8FF;    // set 8th, 9th and 10th bit of PCR[1] to 0
    PORTB->PCR[1] |= 1 << 8;        // set 8th bit of PCR[1] to 1
    
    // configuring ADC0 for software trigger and default voltage reference pin pair, that is, external pins VREFH and VREFL
    ADC0->SC2 &= 0xFFFFFFBC;        // reset the 6th bit and 0th, 1th bit in ADC0_SC2 register
    
    // setting configuration register for ADC0 (see manual for details about ADC0_CFG1)
    ADC0->CFG1 = 0b01000100;
}

void read() {
    // setting input channel as AD9 for ADC0
    ADC0->SC1[0] = 9;
    
    // check conversion complete (COCO) flag of ADC0_SC1A to see if data is read
    while(!(ADC0->SC1[0] & (1 << 7)));      // 0 for A
    
    // read the data from ADC0_RA register (only first 12 bits)
    data = ADC0->R[0] & 0xFFF;              // 0 of A
}

void led_red_init() {
    SIM->SCGC5 |= 1 << 10;          // will activate the port B
   
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

void led_green_init() {
    SIM->SCGC5 |= 1 << 10;          // will activate the port B
   
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

void led_blue_init() {
    SIM->SCGC5 |= 1 << 12;          // will activate the port D
   
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

void delay(int t) {
    while(t--);
}

int main() {
    SystemCoreClockUpdate();    // updating the clock from PLL
    ADC0_init();
    led_red_init(); led_red_off();
    led_blue_init(); led_blue_off();
    led_green_init(); led_green_off();
    while(1) {
        read();
        if(data > (1 << 13) / 3) led_red_on(), delay(100000), led_red_off();
        else if(data > (1 << 12) / 3) led_blue_on(), delay(100000), led_blue_off();
        else led_green_on(), delay(100000), led_green_off();
    }
}
