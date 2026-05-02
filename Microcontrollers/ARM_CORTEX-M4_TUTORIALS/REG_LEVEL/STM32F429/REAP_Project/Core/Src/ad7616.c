#include "ad7616.h"

/*
    AD7616 Bare Metal Driver
    - SPI1 Initialization
    - CONVST (PB0) & BUSY (PB1) Initialization
*/

void AD7616_Init(void)
{
    // Enable Clocks for Port A (SPI1) and Port B (Control pins)
    RCC->AHB1ENR |= (1 << 0) | (1 << 1);
    
    // Enable SPI1 Clock (APB2)
    RCC->APB2ENR |= (1 << 12);
    
    // Configure PA5 (SCK), PA6 (MISO), PA7 (MOSI) as Alternate Function (10)
    GPIOA->MODER |= (1 << 11) | (1 << 13) | (1 << 15);
    GPIOA->MODER &= ~((1 << 10) | (1 << 12) | (1 << 14));
    
    // Set AF5 for PA5, PA6, PA7
    GPIOA->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28);
    
    // Configure PA4 as General Purpose Output (CS pin)
    GPIOA->MODER |= (1 << 8);
    GPIOA->MODER &= ~(1 << 9);
    GPIOA->ODR |= (1 << 4); // Set CS high initially
    
    // Configure PB0 as general purpose output (CONVST)
    GPIOB->MODER |= (1 << 0);
    GPIOB->MODER &= ~(1 << 1);
    GPIOB->ODR |= (1 << 0); // Active low pulse, so keep high
    
    // Configure PB1 as input (BUSY)
    GPIOB->MODER &= ~((1 << 2) | (1 << 3));
    
    // SPI1 Configuration: 
    // MSTR=1, BR=011 (fPCLK/16), SSM=1, SSI=1, DFF=1 (16-bit format)
    // AD7616 uses CPOL=1, CPHA=0 (Mode 2) or CPOL=0, CPHA=1 (Mode 1), but usually Mode 2 or 0.
    SPI1->CR1 = (1 << 2) | (3 << 3) | (1 << 9) | (1 << 8) | (1 << 11);
    SPI1->CR1 |= (1 << 6); // Enable SPI SPE=1
    
    /* 
     * Here you would typically send configuration words to AD7616 over SPI:
     * 1. Write to Configuration Register (Enable Sequencer, Burst Mode, Software Mode)
     * 2. Write to Channel Register (Select A0-A2, B0-B2)
     * For bare-metal, this requires asserting CS -> 16-bit transfer -> de-asserting CS.
     */
}

void AD7616_TriggerConversion(void)
{
    // Generate a short LOW pulse on PB0 (CONVST)
    GPIOB->ODR &= ~(1 << 0); 
    // Small delay (minimum 20ns required by AD7616)
    for(volatile int i=0; i<10; i++); 
    GPIOB->ODR |= (1 << 0);
}

void AD7616_ReadChannels(uint16_t *buffer)
{
    // Wait until BUSY (PB1) goes LOW indicating conversion is complete
    while((GPIOB->IDR & (1 << 1)));
    
    // Read 6 channels (3 voltage + 3 current) sequentially
    GPIOA->ODR &= ~(1 << 4); // Pull CS Low
    
    for(int i = 0; i < 6; i++) {
        // Wait until TXE (Transmit buffer empty)
        while(!(SPI1->SR & (1 << 1)));
        
        // Send dummy 16-bit word to clock out data
        SPI1->DR = 0x0000;
        
        // Wait until RXNE (Receive buffer not empty)
        while(!(SPI1->SR & (1 << 0)));
        
        // Store 16-bit result
        buffer[i] = SPI1->DR;
    }
    
    GPIOA->ODR |= (1 << 4); // Pull CS High
}
