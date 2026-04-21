/* 
TIMER PWM MODE (STM32F429)
Using TIM5 Channel 1 connected to PA0 to fade an LED via PWM.

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244): 
  Enables clock to GPIOA (Bit 0).
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285): 
  PA0 mode set to 10 for Alternate Function.
- GPIOx_AFRL (RM0090 Section 8.4.9, Page 289): 
  Alternate function low register. AF2 for TIM5_CH1 on PA0.
- RCC_APB1ENR (RM0090 Section 7.3.13, Page 247): 
  Enables clock to TIM5 (Bit 3).
- TIM5_PSC / TIM5_ARR (RM0090 Section 14.4.11/14.4.12): 
  Prescaler and Auto-reload registers to set PWM frequency.
- TIM5_CCMR1 (RM0090 Section 14.4.7, Page 575): 
  Capture/Compare mode register. OC1M[2:0] set to 110 for PWM Mode 1.
- TIM5_CCER (RM0090 Section 14.4.9, Page 579): 
  Capture/Compare enable register. CC1E=1 sets Channel 1 output.
- TIM5_CCR1 (RM0090 Section 14.4.13, Page 581): 
  Capture/Compare register 1. Sets the duty cycle comparing to ARR.
- TIM5_CR1 (RM0090 Section 14.4.1): 
  Control register 1. CEN=1 enables counter.
*/

#include "stm32f4xx.h"                  // Device header

int DUTY_CYCLE=0;
int val;

void timer_pin_init()
{
	// RM0090 Page 244: Enable clock for Port A
	RCC->AHB1ENR |= (1<<0); 
	
	// RM0090 Page 285: Set PA0 to Alternate Function (10 in binary)
	GPIOA->MODER |= (1<<1); 
	
	// RM0090 Page 289: Set AF2 (0010) for PA0 in AFRL (AFR[0])
	GPIOA->AFR[0] |= (1<<1); 
}

void timer5_init(void)
{
	// RM0090 Page 247: Provide APB1 clock to TIM5
	RCC->APB1ENR |= (1<<3);
	
	// Default system clock HSI = 16 MHz
	// 16,000,000 / 10 = 1,600,000 Hz Timer Clock
	TIM5->PSC = 10 - 1;   
	
	// Set Auto-Reload value. Frequency = 1,600,000 / 26667 = ~60 Hz
	TIM5->ARR = 26667 - 1;
	
	// Initialize counter
	TIM5->CNT = 0;       
	
	// RM0090 Section 14.4.1: Enable TIM5 Counter
	TIM5->CR1 = 1;        
}

void timer5_pwm_init(void)
{
	// RM0090 Page 575: CCMR1 OC1M = 110 (PWM Mode 1 on Channel 1) -> bits 6 and 5
	TIM5->CCMR1 |= (1<<6) | (1<<5);  
	
	// RM0090 Page 579: Enable Capture/Compare Channel 1
	TIM5->CCER |= 1;         
	 
	// Initial Duty Cycle
	TIM5->CCR1 = (26667 / 3) - 1; 
}

// Calibrated roughly for 16MHz
void delayMs(int delay)
{
	int i;
	for(; delay > 0; delay--)
	{
		for(i = 0; i < 3200; i++);
	}
}

int main()
{
	timer_pin_init();
	timer5_init();
	timer5_pwm_init();
	
	while(1)
	{
		// Fade OUT
		for(val = 4000; val >= 700; val -= 10)
		{
			TIM5->CCR1 = val;
			delayMs(10);
		}
		// Fade IN
		for(val = 700; val <= 4000; val += 10)
		{
			TIM5->CCR1 = val;
			delayMs(10);
		}
	}
}