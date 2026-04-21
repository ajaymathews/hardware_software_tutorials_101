/*
SPI1 CONFIGURATION (STM32F429)
Using SPI1 in Master Mode.
Pins: 
- PA5: SCK (Serial Clock)
- PA6: MISO (Master In Slave Out)
- PA7: MOSI (Master Out Slave In)

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244): 
  Enables clock to GPIOA (Bit 0).
- RCC_APB2ENR (RM0090 Section 7.3.14, Page 248): 
  Enables clock to SPI1 (Bit 12).
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285): 
  Sets PA5, PA6, PA7 to Alternate Function (10).
- GPIOx_AFRL (RM0090 Section 8.4.9, Page 289): 
  Sets AF5 (0101) for PA5, PA6, PA7 (SPI1).
- SPI_CR1 (RM0090 Section 28.5.1, Page 894): 
  Control register 1. We configure it for Master (MSTR=1), Baud rate (BR[2:0]), Software slave management (SSM=1, SSI=1), and enable SPI (SPE=1).
- SPI_SR (RM0090 Section 28.5.3, Page 897): 
  Status register. Check TXE (Transmit buffer empty) and RXNE (Receive buffer not empty).
- SPI_DR (RM0090 Section 28.5.4, Page 898): 
  Data register (16-bit) but we send 8 bits at a time.
*/

#include "stm32f4xx.h"                  // Device header

void spi_pin_init()
{
	// RM0090 Page 244: Enable clock for Port A
	RCC->AHB1ENR |= (1<<0);
	
	// RM0090 Page 285: Configure PA5, PA6, PA7 to Alternate Function mode (10 binary)
	// PA5 (bits 10-11), PA6 (bits 12-13), PA7 (bits 14-15)
	GPIOA->MODER |= (1<<11) | (1<<13) | (1<<15); 
	GPIOA->MODER &= ~((1<<10) | (1<<12) | (1<<14)); // Clear the low bits just in case
	
	// RM0090 Page 289: Set Alternate Function 5 (AF5 = 0101) for PA5, PA6, PA7
	// AFR[0] is AFRL.
	// PA5 -> bits 20-23
	// PA6 -> bits 24-27
	// PA7 -> bits 28-31
	GPIOA->AFR[0] |= (5<<20) | (5<<24) | (5<<28); 
}

void spi_init()
{
	// RM0090 Page 248: Enable clock for SPI1 on APB2
	RCC->APB2ENR |= (1<<12);
	
	// RM0090 Page 894: SPI_CR1 Configurations
	// Bit 2: MSTR = 1 (Master configuration)
	// Bits 5:3: BR = 011 (f_PCLK/16 for baud rate) -> roughly 1MHz with 16MHz base
	// Bit 9: SSM = 1 (Software slave management enabled)
	// Bit 8: SSI = 1 (Internal slave select)
	SPI1->CR1 = (1<<2) | (3<<3) | (1<<9) | (1<<8);
	
	// Bit 6: SPE = 1 (Enable SPI)
	SPI1->CR1 |= (1<<6);
}

// Write/Read a single byte over SPI (Full-Duplex)
uint8_t spi_transfer(uint8_t data)
{
	// Wait until TXE (Transmit buffer empty) is 1
	while(!(SPI1->SR & (1<<1))) {}
	
	// Send data
	SPI1->DR = data;
	
	// Wait until RXNE (Receive buffer not empty) is 1
	while(!(SPI1->SR & (1<<0))) {}
	
	// Read received data
	return SPI1->DR;
}

int main()
{
	spi_pin_init();
	spi_init();
	
	while(1)
	{
		// Example usage: Transmit 'A', receive to 'response'
		// uint8_t response = spi_transfer('A');
	}
}