/*
USART6 CONFIGURATION (STM32F429)
Using UART6 on pins PC6 (TX) and PC7 (RX).

REFERENCES TO RM0090 (STM32F429 User Manual):
- RCC_AHB1ENR (RM0090 Section 7.3.10, Page 244): 
  Enables clock to GPIOC (Bit 2).
- RCC_APB2ENR (RM0090 Section 7.3.14, Page 248): 
  Enables clock to USART6 (Bit 5). (USART1 and USART6 are on APB2).
- GPIOx_MODER (RM0090 Section 8.4.1, Page 285): 
  Sets PC6 and PC7 to 10 (Alternate Function Mode).
- GPIOx_AFRL (RM0090 Section 8.4.9, Page 289): 
  Sets AF8 (1000) for PC6 and PC7 (bits 27:24 and 31:28).
- USART_CR1 (RM0090 Section 30.6.4, Page 1007): 
  Control register 1. UE=1 (bit 13) enables USART. TE=1 (bit 3) enables transmitter. RE=1 (bit 2) enables receiver.
- USART_BRR (RM0090 Section 30.6.3, Page 1006): 
  Baud rate register. Configured for 9600 baud using 16MHz clock (value 0x0683).
- USART_SR (RM0090 Section 30.6.1, Page 1001): 
  Status register. TXE (bit 7) = Transmit data register empty. RXNE (bit 5) = Read data register not empty.
- USART_DR (RM0090 Section 30.6.2, Page 1004): 
  Data register points to TDR when writing and RDR when reading.
*/

#include "stm32f4xx.h" // Device header

// Baud Rate Calculation for 9600 @ 16MHz APB2 Clock
#define BAUD 0x0683

void delayMS(int delay)
{
	int i;
	for(; delay > 0; delay--)
	{
		for(i = 0; i < 3195; i++);
	}
}

/***************************** USART CORE ************************/

void usart_init(void)
{ 
	// RM0090 Page 244: Enable GPIOC clock
	RCC->AHB1ENR |= (1<<2);   
	
	// RM0090 Page 248: Enable USART6 clock from APB2
	RCC->APB2ENR |= (1<<5);   
	
	// RM0090 Page 1006: Set Baudrate 9600 @ 16MHz
	USART6->BRR = BAUD;       
	
	// RM0090 Page 1007: Enable USART
	USART6->CR1 |= (1<<13);  
}

/********************* TRANSMISSION (TX) ***********************/
// PIN PC6

void usart_tx_init(void)
{
	// RM0090 Page 285: Set PC6 to Alternate Function Mode (10 -> bit 13)
	GPIOC->MODER |= (1<<13);  
	
	// RM0090 Page 289: Set AF8 (1000) for PC6 on AFRL (AFR[0] bits 27:24)
	GPIOC->AFR[0] |= (1<<27);   

	// RM0090 Page 1007: Enable Transmitter
	USART6->CR1 |= (1<<3);    
}

void usart_writechar(uint8_t ch)
{
	// RM0090 Page 1001: Wait until TXE (bit 7) is 1 (Transmit data register empty)
	while(!(USART6->SR & 0x0080)) {}
	
	// RM0090 Page 1004: Write data to DR to transmit
	USART6->DR = ch;          
}

void usart_writestring(char *ptr)
{
	while(*ptr != '\0')
	{
		usart_writechar(*ptr);
		ptr++;
	}
}

/*************************** RECEPTION (RX) *************************/
// PIN PC7

void usart_rx_init(void)
{
	// RM0090 Page 285: Set PC7 to Alternate Function Mode (10 -> bit 15)
	GPIOC->MODER |= (1<<15);
	
	// RM0090 Page 289: Set AF8 (1000) for PC7 on AFRL (AFR[0] bits 31:28)
	GPIOC->AFR[0] |= (1<<31); 
	
	// RM0090 Page 1007: Enable Receiver
	USART6->CR1 |= (1<<2);
}

int readchar(void)
{
	// RM0090 Page 1001: Wait until RXNE (bit 5) is 1 (Read data register not empty)
	while(!(USART6->SR & 0x0020)) {}
	
	// RM0090 Page 1004: Read data from DR
	int letter = USART6->DR;
	return letter;	
}

/****************************** MAIN **********************************/

int main(void)
{
	int letter;
	
	usart_init();
	usart_tx_init();
	usart_rx_init();
	
	while(1)
	{
		// Basic Echo program
		letter = readchar();
		delayMS(1);
		usart_writechar(letter);
	}
}