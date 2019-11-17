#include<MKL25Z4.h>

void LED_Config() {
    SIM->SCGC5 |= 1 << 10; // will activate the port B
    SIM->SCGC5 |= 1 << 12; // will activate the port D

    // set the pins B18, B19, D1 as gpio
    PORTB->PCR[18] &= 0xFFFFF8FF;   // set 8th, 9th and 10th bit of PCR[18] to 0
    PORTB->PCR[18] |= 1 << 8;       // set 8th bit of PCR[18] to 1
    PORTB->PCR[19] &= 0xFFFFF8FF;   // set 8th, 9th and 10th bit of PCR[19] to 0
    PORTB->PCR[19] |= 1 << 8;       // set 8th bit of PCR[19] to 1
    PORTD->PCR[1] &= 0xFFFFF8FF;    // set 8th, 9th and 10th bit of PCR[1] to 0
    PORTD->PCR[1] |= 1 << 8;        // set 8th bit of PCR[1] to 1
    
    // set the ports as output port
    PTB->PDDR |= 1 << 18;           // set the 18th bit of PDDR to 1 for output
    PTB->PDDR |= 1 << 19;           // set the 18th bit of PDDR to 1 for output
    PTD->PDDR |= 1 << 1;            // set the 1th bit of PDDR to 1 for output
}

void LED_Set() {
    PTB->PSOR |= 1 << 18;       // red LED
    PTB->PSOR |= 1 << 19;       // green LED
    PTD->PSOR |= 1 << 1;        // blue LED
}

void LED_Clear() {
    PTB->PCOR |= 1 << 18;       // red LED
    PTB->PCOR |= 1 << 19;       // green LED
    PTD->PCOR |= 1 << 1;        // blue LED
}

void LED_On(uint32_t led) {
    // function to turn the specified LED on
    switch(led) {
        case 0: PTB->PCOR |= 1 << 18; break; // red LED
        case 1: PTB->PCOR |= 1 << 19; break; // green LED
        case 2: PTD->PCOR |= 1 << 1;  break; // blue LED
    }
}

void LED_Off(uint32_t led) {
    // function to turn the specified LED off
    switch(led) {
        case 0: PTB->PTOR |= 1 << 18; break; // red LED
        case 1: PTB->PTOR |= 1 << 19; break; // green LED
        case 2: PTD->PTOR |= 1 << 1;  break; // blue LED
    }
}