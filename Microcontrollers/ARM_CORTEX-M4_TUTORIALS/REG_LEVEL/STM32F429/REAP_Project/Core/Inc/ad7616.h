#ifndef __AD7616_H
#define __AD7616_H

#include <stdint.h>
#include "stm32f4xx.h"

// AD7616 SPI1 Pins:
// PA5 - SCK, PA6 - MISO, PA7 - MOSI, PA4 - CS
// Additional Pins:
// PB0 - CONVST (Start Conversion trigger)
// PB1 - BUSY (Interrupt/Polling input)

void AD7616_Init(void);
void AD7616_TriggerConversion(void);
void AD7616_ReadChannels(uint16_t *buffer);

#endif
