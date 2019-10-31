#include<MKL25Z4.h>

/* ============== function to configure the all leds ================ */
void LED_Config(){ 
    //ACTIVATE PORT
    SIM->SCGC5 |=(1<<10);//B
    SIM->SCGC5 |=(1<<12);//D
    
    //SET 8,9,10 = 001 TO GPIO
    PORTB->PCR[18]|=(1<<8); //SETTING 8TH BIT TO 1
    PORTB->PCR[18]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    PORTB->PCR[19]|=(1<<8); //SETTING 8TH BIT TO 1
    PORTB->PCR[19]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    PORTD->PCR[1]|=(1<<8); //SETTING 8TH BIT TO 1
    PORTD->PCR[1]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    
    PTB->PDDR |= (1<<18); //18TH BIT = 1, TO ACTIVATE 18 PIN
    PTB->PDDR |= (1<<19); //18TH BIT = 1
    PTD->PDDR |= (1<<1); //18TH BIT = 1
}

/* ============== function to on the all leds ================ */
void LED_On(uint32_t led){
    switch(led){
        case 0 : PTB->PCOR |= (1<<18 );//CLEAR 18PIN VALUE
        case 1 : PTB->PCOR |= (1<<19 ); //CLEAR 19PIN VALUE
        case 2 : PTD->PCOR |= (1<<1 ); //CLEAR 1PIN VALUE
    }
}

/* ============== function to off the all leds ================ */
void LED_Off(uint32_t led){
    switch(led){
        case 0 : PTB->PDOR |= (1<<18 ); //set 18PIN VALUE
        case 1 : PTB->PDOR |= (1<<19 ); //set 19PIN VALUE
        case 2 : PTD->PDOR |= (1<<1 ); //set 1PIN VALUE
    }
}

/* ============== function to set the all leds ================ */
void LED_Set(void){
    PTB->PSOR |= (1<<18 );//set 18PIN VALUE
    PTB->PSOR |= (1<<19 ); //set 19PIN VALUE
    PTD->PSOR |= (1<<1 ); //set  1PIN VALUE
}

/* ============== function to clear the all leds ================ */
void LED_Clear(void){
    PTB->PDOR |= (1<<18 );//CLEAR 18PIN VALUE
    PTB->PDOR |= (1<<19 ); //CLEAR 19PIN VALUE
    PTD->PDOR |= (1<<1 ); //CLEAR 1PIN VALUE
}
