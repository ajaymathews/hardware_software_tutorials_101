#include "main.h"

/*
    REAP CARE SYSTEM - MAIN LOOP
*/

// Variables for ADE9000
uint32_t rms_current;
uint32_t rms_voltage;
uint32_t thd_value;

// Variables for AD7616
uint16_t adc_buffer[6];
float32_t fft_input_buffer[FFT_SAMPLES];
float32_t fft_output_mag[FFT_SAMPLES / 2];

// Simple delay function
void System_DelayMs(int delay)
{
    for(int i=0; i<delay; i++) {
        for(volatile int j=0; j<3200; j++); 
    }
}

int main(void)
{
    // 1. Initialize System Peripherals (Bare Metal)
    SystemCoreClockUpdate();
    
    SDRAM_Init();
    AD7616_Init();
    ADE9000_Init();
    RS485_Init();
    FFT_Init();
    
    uint32_t sdram_offset = 0;
    uint32_t sample_count = 0;
    
    while(1)
    {
        // ------------------------------------------------------------- //
        // STEP 1: READ ADE9000 (RMS, THD, Anomalies)
        // ------------------------------------------------------------- //
        // 0x021C = AIRMS (Current A RMS)
        // 0x021D = AVRMS (Voltage A RMS)
        rms_current = ADE9000_ReadReg(0x021C); 
        rms_voltage = ADE9000_ReadReg(0x021D); 
        
        // Example Threshold Check for Overcurrent
        if(rms_current > 0x0F000000) 
        {
            // Trigger Anomaly
            uint8_t alert_payload[] = "ALERT: OVERCURRENT DETECTED\r\n";
            RS485_Transmit(alert_payload, sizeof(alert_payload));
            
            // ------------------------------------------------------------- //
            // STEP 2: HIGH SPEED SAMPLING WITH AD7616 (1000 SPS)
            // ------------------------------------------------------------- //
            sample_count = 0;
            sdram_offset = 0;
            
            while(sample_count < FFT_SAMPLES)
            {
                AD7616_TriggerConversion();
                AD7616_ReadChannels(adc_buffer);
                
                // Store Current A (assume it's channel 0) to SDRAM
                SDRAM_Write16(sdram_offset, adc_buffer[0]);
                
                // Also store to our FFT Buffer (requires conversion to float)
                // Assuming AD7616 gives 16-bit signed or unsigned. If signed 2's comp, convert.
                fft_input_buffer[sample_count] = (float32_t)((int16_t)adc_buffer[0]);
                
                sdram_offset += 2; // Offset moves by 2 bytes (16-bit word)
                sample_count++;
                
                System_DelayMs(1); // Rough ~1000 SPS delay
            }
            
            // ------------------------------------------------------------- //
            // STEP 3: PERFORM FFT TO EXTRACT HARMONICS
            // ------------------------------------------------------------- //
            FFT_ProcessData(fft_input_buffer, fft_output_mag);
            
            // Find dominant frequency component from the anomaly
            uint32_t domFreq = FFT_FindDominantFrequency(fft_output_mag, 1000.0f);
            
            // ------------------------------------------------------------- //
            // STEP 4: TRANSMIT FFT DATA OVER RS485
            // ------------------------------------------------------------- //
            uint8_t freq_payload[32];
            // Poor man's sprintf for baremetal (if stdlib formatting isn't included)
            freq_payload[0] = 'D'; 
            freq_payload[1] = 'O'; 
            freq_payload[2] = 'M';
            freq_payload[3] = ' ';
            freq_payload[4] = 'F';
            freq_payload[5] = 'R';
            freq_payload[6] = 'E';
            freq_payload[7] = 'Q';
            freq_payload[8] = ':';
            freq_payload[9] = ' ';
            // Assuming domFreq is ~ 50 to 300 hz max
            freq_payload[10] = (domFreq / 100) + '0';
            freq_payload[11] = ((domFreq / 10) % 10) + '0';
            freq_payload[12] = (domFreq % 10) + '0';
            freq_payload[13] = 'H';
            freq_payload[14] = 'Z';
            freq_payload[15] = '\r';
            freq_payload[16] = '\n';

            RS485_Transmit(freq_payload, 17);
        }
        
        System_DelayMs(100);
    }
}
