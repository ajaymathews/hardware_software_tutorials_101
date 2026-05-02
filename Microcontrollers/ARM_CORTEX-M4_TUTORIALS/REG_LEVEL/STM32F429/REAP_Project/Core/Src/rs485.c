#include "rs485.h"

/*
    RS485 Bare Metal Driver
    - USART1 Initialization
    - Send Data array
*/

#define BAUD 0x0683 // 9600 @ 16MHz APB2 Clock

void RS485_Init(void)
{
    // Enable Clocks for Port A and USART1
    RCC->AHB1ENR |= (1 << 0);
    RCC->APB2ENR |= (1 << 4);
    
    // Configure PA9(TX) and PA10(RX) for Alternate Function (10)
    GPIOA->MODER |= (1 << 19) | (1 << 21);
    GPIOA->MODER &= ~((1 << 18) | (1 << 20));
    
    // Set AF7 for PA9, PA10
    GPIOA->AFR[1] |= (7 << 4) | (7 << 8); // AFR[1] is AFRH
    
    // Configure PA8 as General Purpose Output (RS485 DE/RE control)
    GPIOA->MODER |= (1 << 16);
    GPIOA->MODER &= ~(1 << 17);
    GPIOA->ODR &= ~(1 << 8); // Set Low initially (Receiver Enabled)
    
    // Configure USART1: Baudrate and Control Registers
    USART1->BRR = BAUD;
    USART1->CR1 |= (1 << 3) | (1 << 2); // Enable TX and RX
    USART1->CR1 |= (1 << 13); // Enable USART1
}

static void USART1_WriteBlock(uint8_t ch)
{
    while(!(USART1->SR & (1 << 7))); // Wait until TXE is 1
    USART1->DR = ch;
}

void RS485_Transmit(uint8_t *data, uint16_t length)
{
    // 1. Assert DE/RE pin High (Drive RS485 bus)
    GPIOA->ODR |= (1 << 8);
    
    // 2. Transmit array
    for(uint16_t i = 0; i < length; i++)
    {
        USART1_WriteBlock(data[i]);
    }
    
    // 3. Wait until Transmission Complete (TC bit)
    while(!(USART1->SR & (1 << 6)));
    
    // 4. De-assert DE/RE pin Low (Listen mode)
    GPIOA->ODR &= ~(1 << 8);
}
