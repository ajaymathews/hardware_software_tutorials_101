#ifndef __FFT_H
#define __FFT_H

#include <stdint.h>
#include "arm_math.h"

// Define FFT size (must be supported by CMSIS e.g., 512, 1024, 2048)
#define FFT_SAMPLES 1024

void FFT_Init(void);
void FFT_ProcessData(float32_t *inputData, float32_t *outputMag);
uint32_t FFT_FindDominantFrequency(float32_t *magnitudes, float32_t sampleRate);

#endif
