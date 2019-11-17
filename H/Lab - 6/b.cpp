#include<MKL25Z4.h>

static unsigned volatile int delayCounter = 0;
static unsigned volatile int ticker[4] = {0};
    
void green_led_init() {
    SIM->SCGC5 |= 1 << 10;          // will activate the port B
    
    // set the pin as gpio
    PORTB->PCR[19] &= 0xFFFFF8FF;   // set 8th, 9th and 10th bit of PCR[19] to 0
    PORTB->PCR[19] |= 1 << 8;       // set 8th bit of PCR[19] to 1
    
    // set the port as output port
    PTB->PDDR |= 1 << 19;           // set the 19th bit of PDDR to 1 for output
}

void blue_led_init() {
    SIM->SCGC5 |= 1 << 12;          // will activate the port D
    
    // set the pin as gpio
    PORTD->PCR[1] &= 0xFFFFF8FF;    // set 8th, 9th and 10th bit of PCR[1] to 0
    PORTD->PCR[1] |= 1 << 8;        // set 8th bit of PCR[1] to 1
    
    // set the port as output port
    PTD->PDDR |= 1 << 1;            // set the 1th bit of PDDR to 1 for output
}


void green_led_toggle() {
    // toggle the 19th bit of PDOR register
    PTB->PTOR |= 1 << 19;
}

void blue_led_toggle() {
    // toggle the 18th bit of PDOR register
    PTD->PTOR |= 1 << 1;
}

void SysTick_init() {
    SysTick->LOAD = 20971 - 1;      // load the RVR (reload value register) of SysTick
    SysTick->VAL = 0x00;            // clear the current value of the SysTick counter
    SysTick->CTRL = 0x7;            // enable the counter and SysTick Exception request (1 at bit positions 0 and 1), also use processor clock (1 at bit position 3)
}

void SysTick_Handler(void) {
    for(int i = 0; i < 4; i++) {
        ticker[i]++;
    }
}

int main() {
    SystemCoreClockUpdate();
    green_led_init();
    blue_led_init();
    SysTick_init();
    
    while(1) {
        if(ticker[0] > 500) ticker[0] = 0; green_led_toggle();
        if(ticker[1] > 1000) ticker[1] = 0; blue_led_toggle();
    }
}
