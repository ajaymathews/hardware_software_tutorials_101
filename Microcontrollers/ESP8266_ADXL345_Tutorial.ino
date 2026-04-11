/*
 * ============================================================
 *  Tutorial: ADXL345 3-Axis Accelerometer with ESP8266
 * ============================================================
 * 
 * Sensor:    ADXL345 (SparkFun or AliExpress breakout)
 * Interface: I2C (default address 0x53) or SPI
 * Library:   SparkFun_ADXL345 (recommended) or Adafruit_ADXL345_Unified
 * 
 * WIRING (I2C mode):
 *  ADXL345 VCC  --> NodeMCU 3.3V
 *  ADXL345 GND  --> NodeMCU GND
 *  ADXL345 SDA  --> NodeMCU D2 (GPIO4)
 *  ADXL345 SCL  --> NodeMCU D1 (GPIO5)
 *  ADXL345 SDO  --> GND  (sets I2C address to 0x53)
 *  ADXL345 CS   --> 3.3V (enables I2C mode)
 * 
 * CONCEPTS COVERED:
 *  1. Basic X/Y/Z raw acceleration reading
 *  2. Configuring range (2g / 4g / 8g / 16g)
 *  3. Detecting tap, double-tap, and free-fall events
 *  4. Using interrupt pins (INT1) to trigger fall detection
 * ============================================================
 */

#include <Wire.h>
#include <SparkFun_ADXL345.h>

ADXL345 adxl = ADXL345();

// ─── Calibration ─────────────────────────────────────────────────────────────
// Tune these offsets after running a calibration sketch
const int X_OFFSET =  0;
const int Y_OFFSET = -4;
const int Z_OFFSET = 12;

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- ADXL345 Tutorial ---");

  // Power on the sensor
  adxl.powerOn();

  // Apply calibration offsets (helps improve accuracy)
  adxl.setAxisOffset(X_OFFSET, Y_OFFSET, Z_OFFSET);

  // Set measurement range: 2g | 4g | 8g | 16g
  // Larger range = lower resolution; 2g is most sensitive
  adxl.setRangeSetting(2);

  // ── Activity / Inactivity Detection ────────────────────────────────────────
  adxl.setActivityXYZ(1, 0, 0);        // Detect motion on X-axis only
  adxl.setActivityThreshold(75);       // 62.5mg per LSB

  adxl.setInactivityXYZ(1, 0, 0);
  adxl.setInactivityThreshold(75);
  adxl.setTimeInactivity(10);          // 10 seconds before flagged as inactive

  // ── Free-Fall Detection ─────────────────────────────────────────────────────
  // Free-fall threshold: ~500mg. Duration: minimum 20ms
  adxl.setFreeFallThreshold(7);        // ~437.5mg (7 * 62.5mg)
  adxl.setFreeFallDuration(10);        // 10 * 5ms = 50ms minimum

  // ── Tap Detection ──────────────────────────────────────────────────────────
  adxl.setTapDetectionOnXYZ(0, 0, 1);  // Only detect taps on Z
  adxl.setTapThreshold(50);
  adxl.setTapDuration(15);
  adxl.setDoubleTapLatency(80);
  adxl.setDoubleTapWindow(200);

  // ── Interrupt Mapping ──────────────────────────────────────────────────────
  // Route free-fall interrupt to INT1
  adxl.InactivityINT(0);
  adxl.ActivityINT(0);
  adxl.FreeFallINT(1);   // 1 = route to INT1 pin
  adxl.doubleTapINT(0);
  adxl.singleTapINT(0);

  Serial.println("ADXL345 initialised. Reading acceleration...");
}

void loop() {
  // ── Raw Acceleration Reading ────────────────────────────────────────────────
  int x, y, z;
  adxl.readAccel(&x, &y, &z);

  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.print(y);
  Serial.print("  Z: "); Serial.println(z);

  // ── Interrupt Source Check ─────────────────────────────────────────────────
  // Read interrupt source register to process events
  byte interrupts = adxl.getInterruptSource();

  if (adxl.triggered(interrupts, ADXL345_FREE_FALL)) {
    Serial.println(">>> FREE FALL DETECTED <<<");
  }
  if (adxl.triggered(interrupts, ADXL345_SINGLE_TAP)) {
    Serial.println(">>> SINGLE TAP <<<");
  }
  if (adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)) {
    Serial.println(">>> DOUBLE TAP <<<");
  }
  if (adxl.triggered(interrupts, ADXL345_ACTIVITY)) {
    Serial.println(">>> ACTIVITY DETECTED <<<");
  }
  if (adxl.triggered(interrupts, ADXL345_INACTIVITY)) {
    Serial.println(">>> INACTIVITY DETECTED <<<");
  }

  delay(200);
}

/*
 * ─── NOTES ────────────────────────────────────────────────────────────────────
 *
 * Free-Fall Tuning:
 *   Increase setFreeFallThreshold() if false positives occur.
 *   Increase setFreeFallDuration() to require a longer fall before triggering.
 *
 * SPI Mode:
 *   Replace Wire.begin() with SPI.begin().
 *   Use ADXL345 adxl = ADXL345(SS_PIN); constructor.
 *   Set CS pin low to select device.
 *
 * Libraries:
 *   Arduino Library Manager: search "SparkFun ADXL345"
 *   Or: https://github.com/sparkfun/SparkFun_ADXL345_Arduino_Library
 *
 * Real-World Use in These Projects:
 *   - fall_detection_iot: Free-fall on INT1 → Blynk notify
 *   - Pothole_detection:  Z-axis spike detection for road bump classification
 */
