/*
SYSTICK TIMER EXAMPLES (STM32F429)

The SysTick timer is a core Cortex-M4 feature (not specific to STM32). 
It runs on the processor clock (HCLK). In our default case, this is the 16MHz internal HSI.

Two methods are shown below for generating a delay:
1) Polling the SysTick flag.
2) Using the SysTick Exception/Interrupt.
*/

#include "stm32f4xx.h"                  // Device header

/********************** 1ST METHOD: POLLING **************************/

void systickdelayMs(int n)
{
	// For 16MHz clock, 16000 cycles = 1 millisecond
	SysTick->LOAD = 16000; 
	// Clear current value reg
	SysTick->VAL = 0; 
	// Enable SysTick, use processor clock
	SysTick->CTRL = 0x5;
	
	for(int i=0; i<n; i++)
	{
		// Wait until the COUNTFLAG (bit 16) is set
		// 0x10000 is equivalent to (1<<16)
		while((SysTick->CTRL & 0x10000) == 0) {}  
	}
	// Disable SysTick
	SysTick->CTRL = 0;
}

/******************** 2ND METHOD: USING INTERRUPT ********************/

volatile uint32_t tick;              
volatile uint32_t _tick;           

// THIS FUNCTION EXISTS ON ALL CORTEX-M SERIES AND IS TRIGGERED BY THE SYSTICK EXCEPTION
void SysTick_Handler(void)
{
	++tick;   // Incremented at each tick (1ms)
}                                  

uint32_t getTick(void)
{
	__disable_irq();  // Disable interrupts safely
	_tick = tick;     // Read global tick
	__enable_irq();   // Re-enable interrupts
	
	return _tick;
}

void DelayS(uint32_t sec)
{
  sec *= 1000;                       // MULTIPLY BY 1000 TO GET MILLISECONDS
	uint32_t temp = getTick();         
  while((getTick() - temp) < sec);   // Wait until difference is greater than delay
}

/*********************** MAIN *********************/
int main()
{
	// Basic setup if using interrupts
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock / 1000); // 1ms interrupt
	__enable_irq();

	while(1)
	{
		DelayS(1);
		// Or using polling:
		// systickdelayMs(1000);
	}
}
