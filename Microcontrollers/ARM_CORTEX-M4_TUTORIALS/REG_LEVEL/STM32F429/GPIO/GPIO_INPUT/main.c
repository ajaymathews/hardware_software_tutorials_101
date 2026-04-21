/*
STEPS (STM32F429 Keil Update):
1) SELECT THE FOLDER FOR PROJECT, NAME ANYTHING YOU WANT
2) CHOOSE THE BOARD/DEVICE: STM32F429ZITx
3) FROM CMSIS, TICK CORE; FROM DEVICE TICK STARTUP
4) CLICK OPTION FOR TARGET, UNDER DEBUG TICK RESET & RUN
5) PROJECT -> TARGET -> RENAME SOURCE_GROUP TO APPLICATION
   CREATE A NEW FILE -> main.c (WRITE YOUR CODE IN IT)
   ADD THIS MAIN TO THE APPLICATION

CODING FOR STM32F429I-DISC1:
- USER LED (RED) is on PG14
- USER BUTTON is on PA0

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244): 
  Enables clock for GPIOA (Bit 0) and GPIOG (Bit 6).
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285): 
  Sets GPIO modes: 00 for Input (Button PA0), 01 for Output (LED PG14).
- GPIOx_IDR (RM0090 Section 8.4.5, Page 287):
  Input data register. Reads state of GPIOs (Used to read PA0).
- GPIOx_ODR (RM0090 Section 8.4.6, Page 287): 
  Output data register. Toggles LED.
*/

#include "stm32f4xx.h"             // DEVICE HEADER

#define RED_PIN (1<<14)            // PIN 14 (PG14)
#define RED_MODER (1<<28)          // MODER for PG14 (01 at bit 28-29)

#define SWITCH_MODER (3<<0)        // Mask for clearing PA0 MODER (Bits 0-1)
#define BUTTON_STATUS 0x01         // Bit 0 corresponds to PA0

#define GPIOG_CLOCK (1<<6)         // Bit 6 for Port G
#define GPIOA_CLOCK (1<<0)         // Bit 0 for Port A

void gpio_init()
{
	// RM0090 Page 244: Enable clock for Port A (Button) and Port G (LED)
	RCC->AHB1ENR |= GPIOG_CLOCK | GPIOA_CLOCK;
	
	// RM0090 Page 285: Set PG14 to Output (01)
	GPIOG->MODER |= RED_MODER;
  
	// RM0090 Page 285: Set PA0 to Input (00). We clear the bits.
	// Giving MODER 0 resets to Input
	GPIOA->MODER &= ~SWITCH_MODER;
}

int main()
{
	gpio_init();

	while(1)
	{
		// RM0090 Page 287: IDR register reads input data. We check bit 0 (PA0)
		if((GPIOA->IDR) & BUTTON_STATUS)
		{
			// Wait until the button is released (hand takes off switch)
			while((GPIOA->IDR) & BUTTON_STATUS); 
			
			// RM0090 Page 287: ODR register sets/toggles outputs. We toggle PG14
			GPIOG->ODR ^= RED_PIN; 
		}
	}
}