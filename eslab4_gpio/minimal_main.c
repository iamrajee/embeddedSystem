#include<MKL25Z4.h> //INCLUDING LIBRARY

//====================red B18=============================//
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
    // ========== BLINK RED FOR 100 TIMES ===========//
    led_red_on();
    n = 100 //1e2;
    while(n--){
        led_red_toggle();
        delay(1e6);
    }
    led_red_off();
    
}