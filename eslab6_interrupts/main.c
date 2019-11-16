/*
* 	Author : Rajendra singh
*	Roll no: 111601017
*/

#include<MKL25Z4.h> //INCLUDING LIBRARY

//global
static unsigned volatile int delayCtr=0;
int ticket[4];

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

//=============================DELAY better=============================//
void delay_better(unsigned int d){
	delayCtr=0;
	while(delayCtr<d);
}

//=============================SysTick_Handler=============================//
void SysTick_Handler(void){
	int i;
	delayCtr++;
	for(i=0; i<4; i++){
		ticket[i]++;
	}
}

//=============================SysTick_init=============================//
void SysTick_init(){
	SysTick->LOAD = 20971 - 1;//load the RVR reg of systick
	SysTick->VAL = 0x00;//reset timer
	SysTick->CTRL = 0x07;//enable the timer and interrupt by putting
	//one at 0th and 1th position(request)
	//and 0 at 3rd position (res??)
}

void UART0_init(void)
{
	SIM->SCGC4 |= (1<<10); // set 10th index(index start from 0) bit = 1, enable clock for UART0 by 1<<10 or 0x400
	SIM->SOPT2 |= (1<<26); // set 26th index bit = 1, Selecting MCGFLLCLK clock or MCGPLLCLK/2 as clock source 1<<26 or 0x04000000
	SIM->SOPT2 &= 0xF7FFFFFF; // set 27th index bit = 0, other undisturbed, F(0111)FFFFFF
	UART0->C2 = 0x00; // Transmitter, Receiver disabled
	UART0->BDH = 0x00; // Baudrate updated
	UART0->BDL = 0x18; //00001101, to write 24, SBR = (clock freq/(OSR*))
	UART0->C4 = 0x0F; //00001111, for OCR of 16, Setting OverSampling Ratio 01111
	UART0->C1 = 0x00; //00000000, no parity
	//UART0->C2 = 0x04; //set 3rd index bit = 1, 00001000, Transmitter disabled & Receiver enabled - old
	UART0->C2 = 0x36; //set 5rd index bit = 1, 00001000, Transmitter disabled & Receiver enabled with interrupt - new
	SIM->SCGC5 |= (1<<9); //set 9th index bit = 0, Clock for PORT A Enabled
	PORTA->PCR[1] = (1<<9); //set 9th index bit = 0, MUXing PORT A to use as UART
	PORTA->PCR[1] = 0xFFFFFAFF; //reset
	NVIC->ISER[0] = 0x00001000; //- new
}
void LED_init(void)//Initiating GREEN LED
{
	SIM->SCGC5 |= (1<<10); // enable clock to Port B
	PORTB->PCR[19] |= (1<<8); // MUXing PORT B to use as (PCR19 - 001)
	PORTB->PCR[19] &= 0xFFFFF9FF;
	PTB->PDDR |= (1<<19); //Setting Pin 19 as input and taking XOR
	PTB->PDOR |= (1<<19); //initially off, Corresponding bit 19 in PDORB is set to logic 1.
}
void LED_set(char value)
{
	if (value =='g') //Green LED ON
	{
		PTB->PCOR |= (1<<19); //Corresponding bit 19 in PDORB is cleared to logic 0
	}else if(value =='o') //Green LED OFF
	{
		PTB->PDOR |= (1<<19); //Corresponding bit 19 in PDORB is set to logic 1.
	}
}


void UART0_IQRHandler(){
	char c=UART0->D;
	if (c =='g') //Green LED ON
	{
		led_green_on();
		delay_better(1000);
		// delay_old(100000);
		led_green_off();
	}else if(c=='b') //blue LED OFF
	{
		led_blue_on();
		delay_better(1000);
		// delay_old(100000);
		led_blue_off();
	}
}

//=============================MAIN=============================//
int main(void){
	
	SystemCoreClockUpdate(); //updating clock from PLL
	long long int n; //NUMBER OF BLINK
	
	//INIT ALL LED
	led_green_init();
	led_blue_init();
	led_green_off();
	led_blue_off();

	//INIT SysTick
	SysTick_init();
	
	
	//===================================== first and second experiment =========================
	/* ----------------------------------- Blinking led using interrupt ------------------------*/
	led_green_on();
	led_blue_on();
	while(1){

		// 2
		if(ticket[0]>500){//used for second experiment of blinking multiple led
			ticket[0]=0;
			led_green_toggle();
		}
		if(ticket[1]>1000){
			ticket[1]=0;
			led_blue_toggle();
		}

		//1
		//led_green_toggle(); //used for very first simple experiment of blinking single led

		//delay_old(1e6); //normal delay function
		delay_better(1000); //improved delay function
	}
	led_green_off();
	//==========================================================================================
	
	//===================================== third experiment =====================================
	/* ----------------------------------- interrupt with uart --------------------------------*/
	/* 
	UART0_init(); // Initiating UART0 as receiver
	while (1);
	*/

}
