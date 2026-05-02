#include "sdram.h"

/*
    FMC SDRAM Bare Metal Driver
    - Configure FMC controller for W9825G6KH-6 or similar
    - SDRAM Initialization Sequence (Precharge, Auto-Refresh, Mode Reg)
*/

static void delay(volatile uint32_t count)
{
    while(count--);
}

void SDRAM_Init(void)
{
    // 1. Enable Clocks for FMC and GPIO Ports used (Port B, C, D, E, F, G depending on routing)
    RCC->AHB3ENR |= (1 << 0); // FMC Clock Config
    RCC->AHB1ENR |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5) | (1 << 6); 
    
    /* 
     * 2. Initialize GPIO pins for FMC Alternate Function (AF12 = 1100).
     * You would configure D0-D15, A0-A11, NBL0/1, SDCKE, SDCLK, SDNCAS, SDRAS, SDNRAS, SDNEW.
     * (e.g., GPIOB->MODER |= ..., GPIOB->AFR |= ... )
     * Since there are 40+ pins, this forms a large block of register writes.
     * For brevity, this skeleton assumes pins are configured here.
     */
     
    // 3. Configure FMC SDRAM Control Registers
    // Set RPIPE, RBURST, SDCLK configuration for SDRAM Bank 2
    FMC_Bank5_6->SDCR[1] = 0x00002800; // Example config
    
    // 4. Configure FMC SDRAM Timing Registers
    FMC_Bank5_6->SDTR[1] = 0x00106000; 
    
    // 5. SDRAM Initialization Sequence
    // Step A: Clock Enable Command
    FMC_Bank5_6->SDCMR = 0x00000009 | (1 << 4); // Target Bank 2
    delay(10000); 
    
    // Step B: PALL (Precharge All) Command
    FMC_Bank5_6->SDCMR = 0x0000000A | (1 << 4);
    delay(10);
    
    // Step C: Auto Refresh Command (Issue 8 times)
    FMC_Bank5_6->SDCMR = 0x000000EB | (1 << 4);
    delay(10);
    
    // Step D: Load Mode Register (Burst length, latency)
    FMC_Bank5_6->SDCMR = 0x0004600C | (1 << 4);
    delay(10);
    
    // Step E: Set Auto-Refresh Rate
    FMC_Bank5_6->SDRTR = 0x0560; // Count relative to SDCLK
}

void SDRAM_Write16(uint32_t offset, uint16_t data)
{
    // Write 16-bit to SDRAM mapped region
    *(__IO uint16_t *)(EXT_SDRAM_ADDR + offset) = data;
}

uint16_t SDRAM_Read16(uint32_t offset)
{
    // Read 16-bit from SDRAM mapped region
    return *(__IO uint16_t *)(EXT_SDRAM_ADDR + offset);
}
