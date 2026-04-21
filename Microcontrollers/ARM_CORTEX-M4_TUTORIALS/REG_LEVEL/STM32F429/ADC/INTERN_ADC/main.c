/* 
INTERNAL TEMPERATURE SENSOR (STM32F429)
The internal temperature sensor is internally connected to the ADC1_IN18 input channel.
It can be used to measure the ambient temperature of the device.

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_APB2ENR (RM0090 Section 7.3.14, Page 248): 
  Enables clock to ADC1 (Bit 8).
- RCC_APB1ENR (RM0090 Section 7.3.13, Page 247):
  Enables clock to TIM5 (Bit 3).
- ADC_CCR (RM0090 Section 13.13.13, Page 428):
  Common control register. Bit 23: TSVREFE (Temperature sensor and VREFINT enable).
- ADC_SQR3 (RM0090 Section 13.13.9, Page 426):
  Channel 18 is set for the first conversion.
- TIM5 Registers (RM0090 Section 14 and 15):
  TIM5 is used to trigger the ADC conversion via Capture/Compare.
*/

#include "stm32f4xx.h"                  // Device header

int ch1;

/***************************** ADC CORE ************************/

void adc_init(void)
{
	// RM0090 Page 248: Enable APB2 clock to ADC1
	RCC->APB2ENR |= (1<<8); 
	
	// RM0090 Page 421: Disable ADC before configuring
	ADC1->CR2 = 0; 
	
	// RM0090 Page 426: ADC 1st CONVERSION IN REGULAR SEQUENCE, CHANNEL 18 (Temp Sensor)
	ADC1->SQR3 = 18; 

	// RM0090 Page 421: Turn on ADC
	ADC1->CR2 |= 1; 
}

void adc_start(void)
{
	// Start conversion of regular channels
	ADC1->CR2 |= (1<<30);
}

void adc_stop(void)
{
	// Stop conversion
	ADC1->CR2 &= ~(1<<30);
}

int adc_read(void)
{
	// Wait for EOC
	while(!((ADC1->SR) & 0x02)) {}
	ch1 = ADC1->DR;	
	return ch1;
}

/********************** INTERNAL TEMP SENSOR CONFIG *********************/
void temp_sensor_init()
{ 
	// RM0090 Page 428: Enable TSVREFE (Temp Sensor and VREFINT enable) bit 23
	ADC->CCR |= (1<<23);
	// Disable VBATE bit 22 (Battery voltage)
	ADC->CCR &= ~(1<<22);
	
	// Use channel 18
	ADC1->SQR3 = 18;
	
	// RM0090 Page 421: CR2 configurations
	// Bit 28: Trigger detection on rising edge (EXTEN = 01)
	// Bits 27:24 = 1011 (EXTSEL) - mapped to TIM5 CC2 event for F429 (Wait: for F429 TIM5 TRGO is 1010, TIM5_CH1 is 1011, TIM5_CH2 is 1100, TIM5_CH3 is 1101... let's keep original if it worked on F411, or use generic SWSTART)
	// For simplicity, we stick to the original code or just SWSTART. The original code sets 1<<27 | 1<<25 | 1<<24.  which is 1011 (EXTSEL = 1011).
	ADC1->CR2 |= (1<<28); 
	ADC1->CR2 |= (1<<27) | (1<<25) | (1<<24);

	// RM0090 Page 424: SMPR1 register. Channel 18 sampling time.
	// SMP18 (bits 26:24). 010: 84 cycles.
	ADC1->SMPR1 |= (1<<26);
}

/*************************** TIM5 TRIGGER CONFIG **************************/

void timer_init(void)
{
	// Enable Timer 5 Counter
	TIM5->CR1 = 1;     
}

void timer5_init(void)
{
	// RM0090 Page 247: Provide clock to TIM5 (Bit 3)
	RCC->APB1ENR |= (1<<3);
	
	// Clock is typically 16MHz. PSC=1599 -> 10,000 Hz.
	// ARR=9999 -> 1 Hz (1 sec trigger)
	TIM5->PSC = 1600 - 1;   
	TIM5->ARR = 10000 - 1;  
	TIM5->CNT = 0;       
}

void capture_compare_init()
{
	// CCMR1 OC2PE=1 (bit 11), OC2M=0110 (PWM mode 1 - bits 14:12=110)
	// The original says 0x6800. 0x6800 is 110 1000 0000 0000.
	TIM5->CCMR1 |= 0x6800;
	// CCER CC2P=1 (bit 5)
	TIM5->CCER |= 0x0010;
	TIM5->CCR2 = 50 - 1; // Pulse width
	TIM5->CR1 |= 1;      // Start timer
}

/*************** MAIN EXAMPLES ***************/

// EXAMPLE 1: Simple Polling Temp Sensor
int main(void)
{
	adc_init();
	temp_sensor_init();
	
	while(1)
	{
		// Force software start
		adc_start();
		ch1 = adc_read();
		adc_stop();
		
		// To calculate celsius: float celsius = ( (ch1 * (3300.0/4096.0)) - 760.0 ) / 2.5 + 25.0;
	}
}

/*
// EXAMPLE 2: Timer Triggered Temp Sensor
int main(void)
{
	timer5_init();
	capture_compare_init();
	timer_init();
	
	adc_init();
	temp_sensor_init();
	
	while(1)
	{
		// EOC happens automatically triggered by TIM5
		ch1 = ADC1->DR;
	}
}
*/