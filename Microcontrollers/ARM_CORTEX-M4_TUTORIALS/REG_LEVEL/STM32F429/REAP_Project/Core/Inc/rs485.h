#ifndef __RS485_H
#define __RS485_H

#include <stdint.h>
#include "stm32f4xx.h"

// USART1 Pins: PA9 (TX), PA10 (RX)
// Direction control: PA8 (MAX485 DE/RE)

void RS485_Init(void);
void RS485_Transmit(uint8_t *data, uint16_t length);

#endif
