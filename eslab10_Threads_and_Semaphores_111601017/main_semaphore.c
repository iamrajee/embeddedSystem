#include<MKL25Z4.h>
#include "cmsis_os.h" // Include header file for RTX CMSIS-RTOS
#include "led.h"

// System runs at 48MHz // LED #0, #1 are port B, LED #2 is port D
extern void LED_Config(void);
extern void LED_Set(void);
extern void LED_Clear(void);
extern __INLINE void LED_On(uint32_t led);
extern __INLINE void LED_Off(uint32_t led);

osThreadId t_blinky_red; /* Thread IDs */ // Declare a thread ID for blinky
osThreadId t_blinky_green; /* Thread IDs */ // Declare a thread ID for blinky
osThreadId t_blinky_blue; /* Thread IDs */ // Declare a thread ID for blinky

void blinky_red(void const *argument); // Thread /* Function declaration */
void blinky_green(void const *argument); // Thread /* Function declaration */
void blinky_blue(void const *argument); // Thread /* Function declaration */

osSemaphoreDef(two_LEDs);// Declare a Semaphore for LED control
osSemaphoreId two_LEDs_id; // Declare a Semaphore ID for LED control

// ======================================================================
void blinky_red(void const *argument) { // Blinky
    while(1) {
        osSemaphoreWait(two_LEDs_id, osWaitForever);
        LED_On(0); // Green LED on
        osDelay(400); // delay 400 msec
        LED_Off(0); // Green LED off
        osSemaphoreRelease(two_LEDs_id);
        osDelay(600); // delay 600 msec
    } // end while
} // end of blinky

void blinky_green(void const *argument) { // Blinky
    while(1) {
        osSemaphoreWait(two_LEDs_id, osWaitForever);
        LED_On(1); // Green LED on
        osDelay(400); // delay 400 msec
        LED_Off(1); // Green LED off
        osSemaphoreRelease(two_LEDs_id);
        osDelay(600); // delay 600 msec
    } // end while
} // end of blinky


void blinky_blue(void const *argument) { // Blinky
    while(1) {
        osSemaphoreWait(two_LEDs_id, osWaitForever);
        LED_On(2); // Green LED on
        osDelay(400); // delay 400 msec
        LED_Off(2); // Green LED off
        osSemaphoreRelease(two_LEDs_id);
        osDelay(600); // delay 600 msec
    } // end while
} // end of blinky

// ======================================================================
osThreadDef(blinky_red, osPriorityNormal, 1, 0); // define blinky as thread function
osThreadDef(blinky_green, osPriorityNormal, 1, 0); // define blinky as thread function
osThreadDef(blinky_blue, osPriorityNormal, 1, 0); // define blinky as thread function


int main(void)
{
    SystemCoreClockUpdate();
    LED_Config();// Configure LED outputs
    
    two_LEDs_id = osSemaphoreCreate(osSemaphore(two_LEDs), 2);// Create Semaphore with 2 tokens
    
    //Here order matter, change the order to view changes
    t_blinky_red = osThreadCreate(osThread(blinky_red), NULL);// Create a task "blinky" and assign thread ID to t_blinky
    t_blinky_green = osThreadCreate(osThread(blinky_green), NULL);// Create a task "blinky" and assign thread ID to t_blinky
    t_blinky_blue = osThreadCreate(osThread(blinky_blue), NULL);// Create a task "blinky" and assign thread ID to t_blinky
    
    osThreadTerminate(osThreadGetId());
    while(1){
        osDelay(1000);
    };
}
