#include<MKL25Z4.h> //INCLUDING LIBRARY

//====================red B18=============================//
//=======init========//
void led_red_init(){
    SIM->SCGC5 |=(1<<10); //TO ACTIVATE PORT B OR ACTIVE PORT B CLOCK
    //SET 10,9,8 = 0,0,1 TO GPIO
    PORTB->PCR[18]|=(1<<8); //SETTING 8TH BIT TO 1
    PORTB->PCR[18]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    PTB->PDDR |= (1<<18); //18TH BIT = 1, TO ACTIVATE 18 PIN
}
//=======ON========//
void led_red_on(){ //!!! on on low
    PTB->PCOR |= (1<<18 ); //CLEAR 18PIN VALUE
}
//=======OFF========//
void led_red_off(){
    PTB->PDOR |= (1<<18); //CLEAR 18PIN VALUE
}
//=======TOGGLE========//
void led_red_toggle(){
    PTB->PTOR |= (1<<18); //CLEAR 18PIN VALUE
}

//=============================green B19=============================//
//=======init========//
void led_green_init(){
    SIM->SCGC5 |=(1<<10); //TO ACTIVATE PORT B
    PORTB->PCR[19]|=(1<<8); //SETTING 8TH BIT TO 1
    PORTB->PCR[19]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    PTB->PDDR |= (1<<19); //18TH BIT = 1
}
//=======ON========//
void led_green_on(){
    PTB->PCOR |= (1<<19 ); //CLEAR 18PIN VALUE
}
//=======OFF========//
void led_green_off(){
    PTB->PDOR |= (1<<19); //CLEAR 18PIN VALUE
}
//=======TOGGLE========//
void led_green_toggle(){
    PTB->PTOR |= (1<<19); //CLEAR 18PIN VALUE
}
//=============================blue D1=============================//
//=======init========//
void led_blue_init(){
    SIM->SCGC5 |=(1<<12); //TO ACTIVATE PORT D
    PORTD->PCR[1]|=(1<<8); //SETTING 8TH BIT TO 1
    PORTD->PCR[1]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    PTD->PDDR |= (1<<1); //18TH BIT = 1
}
//=======ON========//
void led_blue_on(){
    PTD->PCOR |= (1<<1 ); //CLEAR 18PIN VALUE
}
//=======OFF========//
void led_blue_off(){
    PTD->PDOR |= (1<<1); //CLEAR 18PIN VALUE
}
//=======TOGGLE========//
void led_blue_toggle(){
    PTD->PTOR |= (1<<1); //CLEAR 18PIN VALUE
}

//=============================DELAY=============================//
void delay(long long int d){
    while(d--);
}
//=============================MAIN=============================//
int main(void){
    SystemCoreClockUpdate(); //updating clock from PLL
    long long int n; //NOUMBER OF BLINK
    
    //INIT ALL LED
    led_red_init();
    led_green_init();
    led_blue_init();
    
    // ========== BLINK RED FOR 100 TIMES ===========//
    led_red_on();
    n = 1e2;
    while(n--){
        led_red_toggle();
        delay(1e6);
    }
    led_red_off();
    
    // ========== BLINK RED FOR 100 TIMES ===========//
    led_green_on();
    n = 1e2;
    while(n--){
        led_green_toggle();
        delay(1e6);
    }
    led_green_off();
    
    // ========== BLINK RED FOR 100 TIMES ===========//
    led_blue_on();
    n = 1e2;
    while(n--){
        led_blue_toggle();
        delay(1e6);
    }
    led_blue_off();
    
    // ========== BLINK ALL ONE AFTER OTHER FOR 100 TIMES ===========//
    n = 1e2;
    while(n--){
        led_red_on();
        delay(1e6);
        led_red_off();
        delay(1e6);

        led_green_on();
        delay(1e6);
        led_green_off();
        delay(1e6);

        led_blue_on();
        delay(1e6);
        led_blue_off();
        delay(1e6);
    }
}