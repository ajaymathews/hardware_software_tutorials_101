/*
GENERAL PURPOSE TIMER (STM32F429)
Using TIM5 (32-bit Timer) to create a precise blocking delay of 1 second, toggling the Red LED (PG14).

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_APB1ENR (RM0090 Section 7.3.13, Page 247): 
  TIM2, TIM3, TIM4, and TIM5 are connected to the APB1 bus. Bit 3 enables TIM5 clock.
- TIM5_PSC (RM0090 Section 14.4.11, Page 580): 
  Prescaler register. Divides the timer clock (16MHz) by (1600) to get a 10kHz counter.
- TIM5_ARR (RM0090 Section 14.4.12, Page 580): 
  Auto-reload register. Sets the maximum count before triggering an update event.
- TIM5_CR1 (RM0090 Section 14.4.1, Page 567): 
  Control register 1. CEN (Bit 0) enables the counter.
- TIM5_SR (RM0090 Section 14.4.5, Page 573): 
  Status register. UIF (Bit 0) is the Update Interrupt Flag, set when the timer overflows.
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244): 
  Enables clock to GPIOG (Bit 6).
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285): 
  Configures PG14 as output (01).
*/

#include "stm32f4xx.h"                  // Device header

void timer_init(void)
{
	// RM0090 Page 567: Enable TIM5 Counter (CEN bit)
	TIM5->CR1 = 1;     
}

void timer5_init(void)
{
	// RM0090 Page 247: Provide clock to TIM5 (Bit 3)
	RCC->APB1ENR |= (1<<3);
	
	// Prescaler: 16MHz / 1600 -> 10,000 Hz
	TIM5->PSC = 1600 - 1;   
	
	// Auto-Reload value: Count to 10,000 -> 1 Hz (1 sec)
	TIM5->ARR = 10000 - 1;  
	
	// Reset counter
	TIM5->CNT = 0;       
}

void delayS(int n)
{
	while(n > 0)
	{
		// RM0090 Page 573: Wait until UIF (Update Interrupt Flag) is 1
		while(!(TIM5->SR & 0x0001)) {} 
		
		// Clear UIF flag manually
		TIM5->SR &= ~(0x0001); 
		
		n--;
	}
}

void gpio_init()
{
	// RM0090 Page 244: Enable clock for Port G
	RCC->AHB1ENR |= (1<<6);         
 
	// RM0090 Page 285: Set PG14 to output mode (01 at bit 28-29)
	GPIOG->MODER |= (1<<28);             
}	
 
int main()
{
	timer5_init();
	timer_init();
	gpio_init();
	
	while(1)
	{
		// RM0090 Page 287: Toggle PG14 Output Data Register
		GPIOG->ODR ^= (1<<14);
		
		// Block for 1 second
		delayS(1);
	}
}
