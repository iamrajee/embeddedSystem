/*
* 	Author : Rajendra singh
*	Roll no: 111601017
*/


#include<MKL25Z4.h> //INCLUDING LIBRARY

//=============================ADC0_init=============================//
void init_TPM(){
    //disable clock gating (enabling clock) of 
    SIM->SCGC6 |= (1<<24); 
    
    //setting 24th,25th = 01 for enabling
    SIM->SOPT2 |= (1<<24); //
    SIM->SOPT2 &= ~(1<<25);
    
    //disable tpm0 counter
    TPM0->SC &= ~(3<<3);
    
    //timer clock freq
    TPM0->MOD = 20999;
    
    //configure channel for edge align
    //use tpm0_s
    int temp = TPM0->CONTROLS[1].CnSC;
    temp |= (1<<5);
    temp &= ~(1<<4);
    temp |= (1<<3);
    temp &= ~(1<<2);
    TPM0->CONTROLS[1].CnSC = temp;
    
    //TPM0->CONTROLS[1].CnSC = (0x08 | 0x20);
    
    //set duty cycle 75%
    //TPM0->CONTROLS[1].CnV = 52500; //20999/4
    //TPM0->CONTROLS[1].CnV = (3/4)*20999;
    //TPM0->CONTROLS[1].CnV = (1/2)*20999;
    //TPM0->CONTROLS[1].CnV = (0)*20999;
    TPM0->CONTROLS[1].CnV = (1)*20999;
    
    //disable LPTPM counter
    TPM0->SC = 0b01000;
    
    //configure pddr for blue led
    SIM->SCGC5 |=(1<<12); //TO ACTIVATE PORT B
	//PORTD->PCR[1]|=(1<<8); //SETTING 8TH BIT TO 1
	//PORTD->PCR[1]&=0xFFFFF9FF; //SETTING 9TH, 10TH BIT TO 0, OTHER UNCHANGED
    
    //[10:8] =100
    PORTD->PCR[1]|=(1<<10);
    PORTD->PCR[1]&=~(3<<8);
}

void decreaseBrightness(){
   if(TPM0->CONTROLS[1].CnV == 1){
        TPM0->CONTROLS[1].CnV = 20999;
   }
   TPM0->CONTROLS[1].CnV-=5;;
}

//=============================blue D1=============================//
//=======init========//
void led_blue_init(){
	SIM->SCGC5 |=(1<<12); //TO ACTIVATE PORT B
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

//=============================DELAY old=============================//
void delay_old(long long int d){
	while(d--);
}


//=============================MAIN=============================//
int main(void){
    
    SystemCoreClockUpdate(); //updating clock from PLL
    
    init_TPM();
    //led_blue_init();
    
    //led_blue_off();
    while(1){
        decreaseBrightness();
        delay_old(1);
    }
}