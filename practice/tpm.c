#include<MKL25Z4.h>

//removed led code

void TPM0_init(){
    //sopt 24
    SIM->SCGC6 |=  (1<<24); //24 - 01
    SIM->SOPT2 |=  (1<<24);
    SIM->SOPT2 &=  (neg)(1<<25);

    //tpm0 sc &=(neg)(3<<3);
    //      mod
    //      controls[1].CnSC
    //                 .CnV
    //     sc = 0b01000;
    TPM0->SC &= (neg)(3<<3);
    TPM0->MOD = 20999;
    int temp = TPM0->CONTROLS[1].CnSC;
    temp |= (1<<5);
    temp &= (neg)(1<<4);
    temp |= (1<<3);
    temp &= (neg)(1<<2);
    TPM0->CONTROLS[1].CnSC = temp;
    TPM0->CONTROLS[1].Cnv = (3/4)*(20999);
    TPM0->SC = 0b01000;

    //blue - opps.
    SIM->SCGC5 |= (1<<12);
    PORTD->PCR[1] |= (1<<10);
    PORTD->PCR[1] |= (neg)((1<<9) | (1<<8));
}

void decreaseBrightness(){
    int interval = 5;
    if(TPM0->CONTROLS[1].Cnv <= interval){
        TPM0->CO    NTROLS[1].Cnv = (3/4)*20999;
    }
    TPM0->CONTROLS[1].Cnv-=interval;
}

void delay_old(long long d){
    while(d){
        d--;
    }
}

void main(){
    SystemCoreClockUpdate();
    TPM0_init();

    while(1){
        decreaseBrightness();
        delay_old(1);
    }

}