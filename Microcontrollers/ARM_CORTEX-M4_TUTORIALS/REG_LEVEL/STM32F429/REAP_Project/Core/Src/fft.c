#include "fft.h"

/*
    FFT Processing Wrapper using CMSIS-DSP
    - Initializes the Fast Fourier Transform instance
    - Calculates Magnitudes
    - Returns Dominant Frequency
*/

static arm_rfft_fast_instance_f32 fft_handler;

void FFT_Init(void)
{
    // Initialize the Real FFT instance
    arm_rfft_fast_init_f32(&fft_handler, FFT_SAMPLES);
}

void FFT_ProcessData(float32_t *inputData, float32_t *outputMag)
{
    // inputData Must be array of size FFT_SAMPLES
    // outputMag Must be array of size FFT_SAMPLES / 2
    
    // Intermediate buffer for Complex FFT output
    float32_t complexOutput[FFT_SAMPLES];
    
    // 1. Process Real FFT (Time domain -> Frequency Domain)
    arm_rfft_fast_f32(&fft_handler, inputData, complexOutput, 0);
    
    // 2. Calculate Magnitudes (complex output -> absolute magnitude)
    arm_cmplx_mag_f32(complexOutput, outputMag, FFT_SAMPLES / 2);
    
    // 3. Ignore DC component (0Hz bin)
    outputMag[0] = 0; 
}

uint32_t FFT_FindDominantFrequency(float32_t *magnitudes, float32_t sampleRate)
{
    float32_t maxVal = 0.0f;
    uint32_t maxIndex = 0;
    
    // Find the maximum value in the array
    arm_max_f32(magnitudes, FFT_SAMPLES / 2, &maxVal, &maxIndex);
    
    // Convert bin index to Hz
    uint32_t domFrequency = (maxIndex * sampleRate) / FFT_SAMPLES;
    
    return domFrequency;
}
