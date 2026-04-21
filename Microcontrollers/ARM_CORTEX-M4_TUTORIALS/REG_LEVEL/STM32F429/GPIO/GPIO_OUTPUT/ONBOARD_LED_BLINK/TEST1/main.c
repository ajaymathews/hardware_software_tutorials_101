/*
STEPS (STM32F429 Keil Update):
1) SELECT THE FOLDER FOR PROJECT, NAME ANYTHING YOU WANT
2) CHOOSE THE BOARD/DEVICE: STM32F429ZITx
3) FROM CMSIS, TICK CORE; FROM DEVICE TICK STARTUP
4) CLICK OPTION FOR TARGET, UNDER DEBUG TICK RESET & RUN
5) PROJECT -> TARGET -> RENAME SOURCE_GROUP TO APPLICATION
   CREATE A NEW FILE -> main.c (WRITE YOUR CODE IN IT)
   ADD THIS MAIN TO THE APPLICATION

ARM REGISTERS CAN BE VIEWED IN THE DEBUG MODE IN THE KEIL IDE, THEN THE REGISTERS ADDRESS/SP ADDRESS 
IS COPIED AND FROM VIEW, CLICK ON MEMORY WINDOW AND COPY THIS ADDRESS TO SHOW A DETAILED VIEW OF MEMORY.
USED FOR DEBUGGING.

CODING FOR STM32F429I-DISC1 (F429 Discovery Board):
- THE USER LEDS ARE LOCATED ON PORT G (PG13 = GREEN, PG14 = RED).
- SYSTEM CLOCK: The default HSI (Internal Oscillator) runs at 16 MHz.

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244): 
  Register to enable clock for AHB1 peripherals. Bit 6 enables GPIOG clock.
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285): 
  32-bit register to select I/O mode. We need 01 (General purpose output mode) for pins 13 and 14.
- GPIOx_ODR (RM0090 Section 8.4.6, Page 287): 
  Output data register to set pins High/Low.

SYSTICK TIMER FOR DELAY:
- Standard ARM Cortex-M4 system timer. We use it to count 1ms ticks for a reliable delay without blocking totally in an empty loop.
*/

#include "stm32f4xx.h"             // DEVICE HEADER FOR STM32F4 (works for F429)

// Pin definitions for STM32F429I-DISC1
#define GREEN_PIN (1<<13)         // PIN 13 (PG13)
#define GREEN_MODER (1<<26)       // MODER 01 at bits 27:26 (1<<26)

#define RED_PIN (1<<14)           // PIN 14 (PG14)
#define RED_MODER (1<<28)         // MODER 01 at bits 29:28 (1<<28)

#define GPIOG_CLOCK (1<<6)        // bit 6 of AHB1ENR enables GPIOG

// Volatile variables used in ISR
volatile uint32_t tick;           // Incremented at each SysTick interrupt
volatile uint32_t _tick;          // Temporary storage for reading tick safely

// SysTick Interrupt Handler (Standard Cortex-M4 function)
void SysTick_Handler(void){
	++tick;                        // Increment every 1 millisecond
}

// Safely get current tick count
uint32_t getTick(void){
	__disable_irq();               // Disable interrupts briefly to avoid race conditions
	_tick = tick;
	__enable_irq();
	
	return _tick;
}

// Non-blocking delay in seconds
void Dely(uint32_t sec){
	sec *= 1000;                     // MULTIPLY BY 1000 TO GET MILLISECONDS (SysTick is 1ms)
	uint32_t temp = getTick();       // Starting tick count
	while((getTick() - temp) < sec); // Wait until elapsed time > desired ms
}

// Basic Delay Function using CPU cycles (calibrated for 16MHz roughly)
void delayMs(int delay)
{
	int i;
	for(; delay > 0; delay--) {
		for(i = 0; i < 3195; i++);     // Execution loops 
	}
}

void GPIO_Init(){
	
	/******** INITIALIZING GPIO **********/
	
	// RM0090 Page 244: Bit 6 of RCC_AHB1ENR is GPIOGEN
	RCC->AHB1ENR |= GPIOG_CLOCK;         // ENABLE CLOCK FOR PORT G
 
	// RM0090 Page 285: MODER bits for PG13 and PG14 set to 01 (Output)
	GPIOG->MODER |= GREEN_MODER | RED_MODER; 
	
	/******** INITIALIZING SYSTICK TIMER **********/
	
	SystemCoreClockUpdate();              // Retrieve current SystemCoreClock (16MHz default)
	SysTick_Config(SystemCoreClock/1000); // Trigger interrupt every 1ms
	                                      
	__enable_irq();                       // Ensure interrupts are active for SysTick
}

void RED_BLINK()
{
	while(1) {	
		// RM0090 Page 287: Toggle Red LED state using XOR on ODR
		GPIOG->ODR ^= RED_PIN; 
		Dely(1);   // Delay 1 second
	}
}

void GREEN_BLINK()
{
	while(1) {	
		// RM0090 Page 287: Toggle Green LED state using XOR on ODR
		GPIOG->ODR ^= GREEN_PIN; 
		Dely(1);   // Delay 1 second
	}
}

int main(){
	// Initialize GPIO G and SysTick
	GPIO_Init();
	
	// Start blinking the Red LED (you can swap this to GREEN_BLINK() to test)
	RED_BLINK();
}
