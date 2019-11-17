#include <MKL25Z4.H>
#include "cmsis_os.h" // Include header file for RTX CMSIS-RTOS
#include "LED_init.h"


// System runs at 48MHz
// LED #0, #2 are port B, LED #1 is port D
extern void LED_Config(void);
extern void LED_Set(void);
extern void LED_Clear(void);
extern __INLINE void LED_On(uint32_t led);
extern __INLINE void LED_Off(uint32_t led);


/* Thread IDs */
osThreadId t_blinky_red; // Declare a thread ID for blinky
osThreadId t_blinky_green; // Declare a thread ID for blinky
osThreadId t_blinky_blue; // Declare a thread ID for blinky


/* Function declaration */
void blinky_red(void const *argument); // Thread
void blinky_green(void const *argument); // Thread
void blinky_blue(void const *argument); // Thread


/* Declare Semaphore */
osSemaphoreDef(two_LEDs); // Declare a Semaphore for LED control
/* Semaphore IDs */
osSemaphoreId two_LEDs_id; // Declare a Semaphore ID for LED control


// --------------------------------------------------------
// Blinky
void blinky_red(void const *argument) {
    while(1) {
        osSemaphoreWait(two_LEDs_id, osWaitForever);
        LED_On(0); // Red LED on
        osDelay(400); // delay 400 msec
        LED_Off(0); // Red LED off
        osSemaphoreRelease(two_LEDs_id);
        osDelay(600); // delay 600 msec
    } // end while
} // end of blinky

void blinky_green(void const *argument) {
    while(1) {
        osSemaphoreWait(two_LEDs_id, osWaitForever);
        LED_On(1); // Green LED on
        osDelay(400); // delay 400 msec
        LED_Off(1); // Green LED off
        osSemaphoreRelease(two_LEDs_id);
        osDelay(600); // delay 600 msec
    } // end while
} // end of blinky

void blinky_blue(void const *argument) {
    while(1) {
        osSemaphoreWait(two_LEDs_id, osWaitForever);
        LED_On(2); // Blue LED on
        osDelay(400); // delay 400 msec
        LED_Off(2); // Blue LED off
        osSemaphoreRelease(two_LEDs_id);
        osDelay(600); // delay 600 msec
    } // end while
} // end of blinky

// define blinky as thread function
osThreadDef(blinky_red, osPriorityNormal, 1, 0);
osThreadDef(blinky_green, osPriorityNormal, 1, 0);
osThreadDef(blinky_blue, osPriorityNormal, 1, 0);


// --------------------------------------------------------
int main(void) {
    SystemCoreClockUpdate();
    // Configure LED outputs
    LED_Config();
    // Create Semaphore with 2 tokens
    two_LEDs_id = osSemaphoreCreate(osSemaphore(two_LEDs), 2);
    // Create threds "blinky_xxx" and assign thread ID to t_blinky_xxx
    t_blinky_red = osThreadCreate(osThread(blinky_red), NULL);
    t_blinky_green = osThreadCreate(osThread(blinky_green), NULL);
    t_blinky_blue = osThreadCreate(osThread(blinky_blue), NULL);
    // Terminate main
    osThreadTerminate(osThreadGetId());
    while(1){
        osDelay(1000); // delay 1000 msec
    };
}