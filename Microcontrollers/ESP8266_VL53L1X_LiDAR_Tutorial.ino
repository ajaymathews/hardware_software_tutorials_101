/*
 * ============================================================
 *  Tutorial: VL53L1X LiDAR Time-of-Flight sensor with ESP8266
 * ============================================================
 * 
 * Sensor:    VL53L1X (SparkFun Qwiic or STMicro breakout)
 * Interface: I2C (default address 0x29)
 * Library:   SparkFun VL53L1X (recommended)
 * Range:     Up to 4 metres (dark environment), 2m typical
 * 
 * WIRING:
 *  VL53L1X VCC / VIN  --> NodeMCU 3.3V
 *  VL53L1X GND        --> NodeMCU GND
 *  VL53L1X SDA        --> NodeMCU D2 (GPIO4)
 *  VL53L1X SCL        --> NodeMCU D1 (GPIO5)
 *  VL53L1X XSHUT      --> (optional) NodeMCU D3 — for hardware reset/multi-sensor
 *
 * CONCEPTS COVERED:
 *  1. Basic single-measurement mode
 *  2. Continuous ranging mode (faster updates)
 *  3. Setting distance mode (Short / Long)
 *  4. Handling multiple VL53L1X sensors with XSHUT remapping
 * ============================================================
 */

#include <Wire.h>
#include <SparkFun_VL53L1X.h>

SFEVL53L1X distanceSensor;

// ─── Constants ───────────────────────────────────────────────────────────────
const int POTHOLE_THRESHOLD_MM = 300;  // Objects > 300mm away = pothole detected
const int MEASUREMENT_INTERVAL = 500;  // ms between readings in the loop

unsigned long lastMeasurement = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- VL53L1X LiDAR Tutorial ---");

  Wire.begin(D2, D1);   // SDA = D2 (GPIO4), SCL = D1 (GPIO5)

  if (distanceSensor.begin() != 0) {   // Returns 0 on success
    Serial.println("Sensor failed to begin. Check wiring!");
    while (1);
  }
  Serial.println("VL53L1X sensor online.");

  // ── Ranging Mode ────────────────────────────────────────────────────────────
  // Short mode: max ~1.3m, better ambient light immunity
  // Long mode:  max ~4m,   more sensitive to ambient light
  distanceSensor.setDistanceModeShort();   // Default: long
  // distanceSensor.setDistanceModeLong();

  // ── Timing Budget ───────────────────────────────────────────────────────────
  // Longer budget = better accuracy but slower
  // Options: 15, 20, 33, 50, 100 (ms) — default is 100ms
  distanceSensor.setTimingBudgetInMs(50);

  // ── Intermeasurement Period ─────────────────────────────────────────────────
  // Must be >= timing budget
  distanceSensor.setIntermeasurementPeriod(60);

  // Start continuous ranging (sensor keeps updating on its own)
  distanceSensor.startRanging();
  Serial.println("Continuous ranging started...");
}

void loop() {
  // Non-blocking — only read when new data is ready
  if (millis() - lastMeasurement >= MEASUREMENT_INTERVAL) {
    lastMeasurement = millis();

    // Check if a new measurement is available
    if (distanceSensor.checkForDataReady()) {
      int distance = distanceSensor.getDistance();   // Result in millimetres
      uint8_t rangeStatus = distanceSensor.getRangeStatus();

      distanceSensor.clearInterrupt();  // Required before next measurement

      // Range status 0 = valid reading
      if (rangeStatus != 0) {
        Serial.print("Range error: "); Serial.println(rangeStatus);
      } else {
        Serial.print("Distance: "); Serial.print(distance); Serial.println(" mm");

        // Example application: Pothole detection threshold
        if (distance > POTHOLE_THRESHOLD_MM) {
          Serial.println(">>> POTHOLE DETECTED <<<");
        }
      }
    }
  }
}

/*
 * ─── NOTES ────────────────────────────────────────────────────────────────────
 *
 * Range Status Codes:
 *   0  = Valid
 *   2  = Signal rate too low (target too far or absorptive)
 *   4  = Phase out of bounds (object too close, < ~4cm)
 *   7  = Wraparound detected (sensor confused by reflections)
 *
 * Multiple VL53L1X Sensors (XSHUT Remapping):
 *   1. Wire all XSHUT pins to separate GPIO pins (e.g., D3, D4, D5).
 *   2. Pull all XSHUT LOW to disable all sensors.
 *   3. Enable sensor 1 (XSHUT HIGH), call begin(), then changeAddress(0x30).
 *   4. Enable sensor 2, call begin(), then changeAddress(0x31).
 *   5. Now both are accessible at different I2C addresses.
 *
 * Single-Shot vs Continuous Mode:
 *   startRanging() / stopRanging() → continuous (used above)
 *   startOneshotRanging()          → one measurement then stop
 *
 * Libraries:
 *   Arduino Library Manager: search "SparkFun VL53L1X"
 *   Or: https://github.com/sparkfun/SparkFun_VL53L1X_Arduino_Library
 *
 * Real-World Use in These Projects:
 *   - Pothole_detection: Distance to road surface vs POTHOLE_THRESHOLD_MM trigger
 */
