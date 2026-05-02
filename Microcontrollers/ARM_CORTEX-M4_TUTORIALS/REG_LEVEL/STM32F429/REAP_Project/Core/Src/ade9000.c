#include "ade9000.h"

/*
    ADE9000 Bare Metal Driver
    - SPI2 Initialization
    - Read/Write Register Routines (16-bit address, 32-bit data)
*/

static void SPI2_Write16(uint16_t data)
{
    while(!(SPI2->SR & (1 << 1)));
    SPI2->DR = data;
    while(!(SPI2->SR & (1 << 0)));
    float dummy = SPI2->DR; // clearing RX buffer
}

static uint16_t SPI2_Read16()
{
    while(!(SPI2->SR & (1 << 1)));
    SPI2->DR = 0x0000;
    while(!(SPI2->SR & (1 << 0)));
    return SPI2->DR;
}

void ADE9000_Init(void)
{
    // Enable Clocks for Port B and Port C
    RCC->AHB1ENR |= (1 << 1) | (1 << 2);
    
    // Enable SPI2 Clock (APB1)
    RCC->APB1ENR |= (1 << 14);
    
    // Configure PB13(SCK), PB14(MISO), PB15(MOSI) as Alternate Function (10)
    GPIOB->MODER |= (1 << 27) | (1 << 29) | (1 << 31);
    GPIOB->MODER &= ~((1 << 26) | (1 << 28) | (1 << 30));
    
    // Set AF5 for PB13, PB14, PB15 (SPI2)
    // AFR[1] = AFRH (Pins 8 to 15).
    // PB13 (bits 20-23), PB14 (bits 24-27), PB15 (bits 28-31)
    GPIOB->AFR[1] |= (5 << 20) | (5 << 24) | (5 << 28);
    
    // Configure PB12 as Output (CS Pin)
    GPIOB->MODER |= (1 << 24);
    GPIOB->MODER &= ~(1 << 25);
    GPIOB->ODR |= (1 << 12); // CS High
    
    // Configure PC4 as Input (IRQ0)
    GPIOC->MODER &= ~((1 << 8) | (1 << 9));
    
    // SPI2 Configuration
    // MSTR=1, BR=011, SSM=1, SSI=1, DFF=1 (16-bit data frame)
    SPI2->CR1 = (1 << 2) | (3 << 3) | (1 << 9) | (1 << 8) | (1 << 11);
    SPI2->CR1 |= (1 << 6); // Enable SPI2
    
    /*
     * Initialization Sequence as per ADE9000 datasheet:
     * 1. Write ACCMODE (3-wire/4-wire configs, SELFREQ)
     * 2. Initialize DSP engine 
     * 3. Enable Event interrupts in status mask registers
     */
}

void ADE9000_WriteReg(uint16_t addr, uint32_t data)
{
    // 16-bit address formatted -> Shift address by 4 bits, Bit 3 = 0 (WRITE)
    uint16_t cmd = (addr << 4) & 0xFFF0; 
    
    uint16_t dataHigh = (data >> 16) & 0xFFFF;
    uint16_t dataLow  = data & 0xFFFF;
    
    GPIOB->ODR &= ~(1 << 12); // CS Low
    
    SPI2_Write16(cmd);
    SPI2_Write16(dataHigh);
    SPI2_Write16(dataLow);
    
    GPIOB->ODR |= (1 << 12); // CS High
}

uint32_t ADE9000_ReadReg(uint16_t addr)
{
    // Bit 3 = 1 (READ)
    uint16_t cmd = ((addr << 4) & 0xFFF0) | 0x0008; 
    
    GPIOB->ODR &= ~(1 << 12); // CS Low
    
    SPI2_Write16(cmd);
    uint32_t dataHigh = SPI2_Read16();
    uint32_t dataLow = SPI2_Read16();
    
    GPIOB->ODR |= (1 << 12); // CS High
    
    return (dataHigh << 16) | dataLow;
}
