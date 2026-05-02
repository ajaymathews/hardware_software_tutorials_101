#ifndef __SDRAM_H
#define __SDRAM_H

#include <stdint.h>
#include "stm32f4xx.h"

// SDRAM Bank 2 base address on STM32F429
#define EXT_SDRAM_ADDR  ((uint32_t)0xD0000000)

void SDRAM_Init(void);
void SDRAM_Write16(uint32_t offset, uint16_t data);
uint16_t SDRAM_Read16(uint32_t offset);

#endif
