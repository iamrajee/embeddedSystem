#include<MKL25Z4.h>
#include "cmsis_os.h" // Include header file for RTX CMSIS-RTOS
#include "led.h"

// System runs at 48MHz // LED #0, #1 are port B, LED #2 is port D
extern void LED_Config(void);
extern void LED_Set(void);
extern void LED_Clear(void);
extern __INLINE void LED_On(uint32_t led);
extern __INLINE void LED_Off(uint32_t led);

osThreadId t_blinky; /* Thread IDs */ // Declare a thread ID for blinky
// ======================================================================
void blinky(void const *argument); // Thread /* Function declaration */
void blinky(void const *argument) { // Blinky
    while(1) {
        LED_On(2); // Green LED on
        osDelay(500); // delay 500 msec
        LED_Off(2); // Green LED off
        osDelay(500); // delay 500 msec
    } // end while
} // end of blinky
// ======================================================================
osThreadDef(blinky, osPriorityNormal, 1, 0); // define blinky as thread function



int main(void)
{
    SystemCoreClockUpdate();
    LED_Config();// Configure LED outputs
    t_blinky = osThreadCreate(osThread(blinky), NULL);// Create a task "blinky" and assign thread ID to t_blinky
    while(1){
        LED_On(0); // Red LED on
        osDelay(500); // delay 500 msec
        LED_Off(0); // Red LED off
        osDelay(500); // delay 200 msec
    };
}
