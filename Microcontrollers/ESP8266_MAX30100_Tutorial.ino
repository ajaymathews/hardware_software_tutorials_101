/*
 * ============================================================
 *  Tutorial: MAX30100 Pulse Oximeter & Heart Rate with ESP8266
 * ============================================================
 * 
 * Sensor:    MAX30100 (or MAX30102 - pin compatible)
 * Interface: I2C (fixed address 0x57)
 * Library:   MAX30100lib by OXHack (recommended)
 * 
 * WIRING:
 *  MAX30100 VIN  --> NodeMCU 3.3V
 *  MAX30100 GND  --> NodeMCU GND
 *  MAX30100 SDA  --> NodeMCU D2 (GPIO4)
 *  MAX30100 SCL  --> NodeMCU D1 (GPIO5)
 *  MAX30100 INT  --> NodeMCU D5 (optional - for interrupt-driven reading)
 * 
 * IMPORTANT: The MAX30100 runs at 1.8V I/O logic internally but its breakout
 * boards include level shifters. If wiring raw chip, use logic level converter.
 *
 * CONCEPTS COVERED:
 *  1. Polling-based heart rate (BPM) and SpO2 reading
 *  2. Callback on beat detection 
 *  3. Non-blocking millis() pattern for cloud reporting
 * ============================================================
 */

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 2000   // Print readings every 2 seconds

PulseOximeter pox;
uint32_t lastReport = 0;

// This callback fires every time a heartbeat is detected
void onBeatDetected() {
  Serial.println("♥ Beat!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- MAX30100 Tutorial ---");

  // Initialize the MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED to initialise MAX30100.");
    Serial.println("Check wiring: SDA->D2, SCL->D1, VCC->3.3V");
    while (1);   // Halt execution — sensor is mandatory
  }
  Serial.println("MAX30100 online.");

  // Set the current for the IR LED (higher = stronger signal, more current)
  // Options: MA_0, MA_4_4, MA_7_6, MA_11, MA_14_2, MA_17_4, MA_20_8, MA_24, ...
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Register the beat detection callback
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  // CRITICAL: pox.update() must be called as fast as possible.
  // Never put long delays or blocking code in loop() when using MAX30100.
  pox.update();

  // Report readings every REPORTING_PERIOD_MS milliseconds (non-blocking)
  if (millis() - lastReport > REPORTING_PERIOD_MS) {
    float bpm  = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    Serial.print("Heart Rate: "); Serial.print(bpm);  Serial.print(" BPM  |  ");
    Serial.print("SpO2: ");       Serial.print(spo2); Serial.println(" %");

    // Check for valid readings (sensor returns 0 when finger not detected)
    if (bpm == 0) {
      Serial.println("  >> No finger detected. Place finger firmly on sensor.");
    }
    if (spo2 < 90 && spo2 > 0) {
      Serial.println("  >> WARNING: Low oxygen saturation!");
    }

    lastReport = millis();
  }
}

/*
 * ─── NOTES ────────────────────────────────────────────────────────────────────
 *
 * Common Issues:
 *  - Readings stuck at 0: Finger not placed correctly on sensor window.
 *  - SpO2 always 100%: Usually means insufficient LED current — try a higher
 *    MA setting like MAX30100_LED_CURR_11MA.
 *  - Sensor not found (I2C): Confirm pull-up resistors (4.7kΩ) are on SDA/SCL.
 *
 * Sampling Rate / Performance:
 *   The library uses an ISR internally. Avoid long blocking code in loop().
 *   Use millis() timers for all cloud upload tasks (ThingSpeak, Blynk.virtualWrite).
 *
 * MAX30102 Differences:
 *   MAX30102 adds a green LED channel. Use the "MAX30105" Sparkfun library instead.
 *   The I2C address and wiring remain the same.
 *
 * Libraries:
 *   Arduino Library Manager: search "MAX30100lib"
 *   Or: https://github.com/oxullo/Arduino-MAX30100
 *
 * Real-World Use in These Projects:
 *   - Health_Monitoring_iot: BPM + SpO2 → ThingSpeak every 15s
 *   - fall_detection_iot:    BPM monitoring + abnormal heart-rate alert via Blynk
 */
