/* 
ADC : STM32F429 has up to 3 ADCs (ADC1, ADC2, ADC3)
This code uses ADC1 for continuous conversion on Channel 1 (Pin PA1).

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_APB2ENR (RM0090 Section 7.3.14, Page 248):
  APB2 bus provides clock to ADC1. Bit 8 enables ADC1 clock.
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244):
  AHB1 bus provides clock to GPIOs. Bit 0 enables GPIOA clock.
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285):
  Setting GPIO mode. Mode 11 (Analog mode) for PA1.
- ADC_CR2 (RM0090 Section 13.13.3, Page 421):
  Bit 0: ADON, Turn on ADC.
  Bit 30: SWSTART, Starts conversion of regular channels.
- ADC_SQR3 (RM0090 Section 13.13.9, Page 426):
  Regular sequence register 3. We set channel 1 as the first conversion (bits 4:0).
- ADC_SR (RM0090 Section 13.13.1, Page 419):
  Status register. Bit 1: EOC, End of Conversion indicator.
- ADC_DR (RM0090 Section 13.13.11, Page 427):
  Data register. Holds regular data after conversion.
*/

#include "stm32f4xx.h"                  // Device header

int ch1;

/***************************** ADC ************************/

void adc_init(void)
{
	// RM0090 Page 248: Enable APB2 clock to ADC1 (Bit 8)
	RCC->APB2ENR |= (1<<8); 
	
	// RM0090 Page 421: Disable ADC before configuring
	ADC1->CR2 = 0; 
	
	// RM0090 Page 426: Configure 1st conversion in regular sequence as Channel 1
	ADC1->SQR3 |= 1; 

	// RM0090 Page 421: Turn on ADC
	ADC1->CR2 |= 1; 
}

void adc_pin_init(void)
{
	// RM0090 Page 244: Enable clock for Port A
	RCC->AHB1ENR |= (1<<0); 
	
	// RM0090 Page 285: Set PA1 to Analog mode (11 = 3 in binary)
	// Bits 3 and 2 correspond to pin 1 MODER
	GPIOA->MODER |= (3<<2); 
}

void adc_start(void)
{
	// RM0090 Page 421: Set SWSTART (Bit 30) to start regular sequence conversion
	ADC1->CR2 |= (1<<30);
	// Note: CR2 ADON was already set in init, setting bit 0 again just keeps it on.
	ADC1->CR2 |= 1;
}

void adc_stop(void)
{
	// Power off ADC
	ADC1->CR2 = 0;
}

int adc_read(void)
{
	// RM0090 Page 419: Wait until EOC (End of Conversion) bit 1 is set
	while(!((ADC1->SR) & 0x02)) {}
	
	// RM0090 Page 427: Read converted data
	ch1 = ADC1->DR;	
	
	return ch1;
}

/*************** ADC_MAIN***************/

int main(void)
{
	adc_pin_init();
	
	while(1)
	{
		// Note: The original code resets and reinitializes ADC in loop. 
		// For continuous conversion in F429, this is identical to F411 logic:
		adc_init();
		adc_start();
		ch1 = adc_read();
		adc_stop();
	}
}
