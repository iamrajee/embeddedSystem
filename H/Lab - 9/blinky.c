#include <MKL25Z4.H>
#include "cmsis_os.h" // Include header file for RTX CMSIS-RTOS
#include "LED_init.h"

// System runs at 48MHz
// LED #0, #1 are port B, LED #2 is port D
extern void LED_Config(void);
extern void LED_Set(void);
extern void LED_Clear(void);
extern __INLINE void LED_On(uint32_t led);
extern __INLINE void LED_Off(uint32_t led);

/* Thread IDs */
osThreadId t_blinky; // Declare a thread ID for blinky

/* Function declaration */
void blinky(void const *argument); // Thread

// --------------------------------------------------------
// Blinky
void blinky(void const *argument) {
    while(1) {
        LED_On(1); // Green LED on
        osDelay(500); // delay 500 msec
        LED_Off(1); // Green LED off
        osDelay(500); // delay 500 msec
    } // end while
} // end of blinky

// define blinky as thread function
osThreadDef(blinky, osPriorityNormal, 1, 0);

// --------------------------------------------------------
int main(void) {
    SystemCoreClockUpdate();
    // Configure LED outputs
    LED_Config();
    // Create a task "blinky" and assign thread ID to t_blinky
    t_blinky = osThreadCreate(osThread(blinky), NULL);
    while(1){
        LED_On(0); // Red LED on
        osDelay(200); // delay 200 msec
        LED_Off(0); // Red LED off
        osDelay(200); // delay 200 msec
    };
}