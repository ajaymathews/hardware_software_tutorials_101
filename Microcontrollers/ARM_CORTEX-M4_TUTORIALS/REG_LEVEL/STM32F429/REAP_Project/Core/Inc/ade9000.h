#ifndef __ADE9000_H
#define __ADE9000_H

#include <stdint.h>
#include "stm32f4xx.h"

// SPI2 Pins: PB13 (SCK), PB14 (MISO), PB15 (MOSI), PB12 (CS)
// IRQ Pin: PC4

void ADE9000_Init(void);
void ADE9000_WriteReg(uint16_t addr, uint32_t data);
uint32_t ADE9000_ReadReg(uint16_t addr);

#endif
