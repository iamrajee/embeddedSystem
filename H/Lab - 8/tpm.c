#include<MKL25Z4.h>

void init_TPM() {
    // we would be using TPM0, channel 0 (Timer/PWM module)
    
    // disabling clock gating (enabling clock) for TPM0 
    SIM->SCGC6 |= (1 << 24);
    
    // selecting clock source for TPM counter clock as MCGFLLCLK clock or MCGPLLCLK/2
    // set SIM_SOPT2[25:24] to 01
    SIM->SOPT2 |= (1 << 24);
    SIM->SOPT2 &= ~(1 << 25);
    
    // first disable the TPM0 counter
    // TPM0_SC[4:3] = 00
    TPM0->SC &= ~(3 << 3);
    
    //
    // (MOD + 1) * frequency_of_overflows = timer_clock_frequency
    // frequency_of_overflows = 100Hz
    // timer_clock_frequency = 21MHz
    TPM0->MOD = 20999;
    
    // configuring the channel for Edge-aligned (TPM0_C1SC[5:4] = 10) PWM High-true pulses (TPM0_C1SC[3:2] = 10) (clear Output on match, set Output on reload)
    // use TPM0->CONTROLS[1].CnSC or TPM0_SC to configure TMP0_C1SC register
    // note that all the values must be set at one go
    int tmp = TPM0->CONTROLS[1].CnSC;
    tmp |= (1 << 5);
    tmp &= ~(1 << 4);
    tmp |= (1 << 3);
    tmp &= ~(1 << 2);
    TPM0->CONTROLS[1].CnSC = tmp;
    
    // configuring for 75% duty cycle (1 means off and 0 means on)
    TPM0->CONTROLS[1].CnV = TPM0->MOD / 4;  // (TPM0->MOD / 4)
    
    // see manual for further details
    TPM0->SC = 0b01000;
    
    // activating PORTD
    SIM->SCGC5 |= 1 << 12;
     
    // configuring PORTD1 for TPM0_CH1 (PORTD_PCR1[10:8] = 100)
    PORTD->PCR[1] |= (1 << 10);
    PORTD->PCR[1] &= ~(3 << 8);
}

void decrease_brigtness() {
    int interval = 10;
    if(TPM0->CONTROLS[1].CnV >= TPM0->MOD - interval) TPM0->CONTROLS[1].CnV = TPM0_MOD / 4;
    else TPM0->CONTROLS[1].CnV += interval;
}

void delay(int t) { while(t--); }

int main() {
    SystemCoreClockUpdate();    // updating the clock from PLL
    init_TPM();
    while(1) {
        decrease_brigtness(); delay(10);
    }
}
