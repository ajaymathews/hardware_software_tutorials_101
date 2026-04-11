/*
 * ============================================================
 *  Tutorial: DS18B20 OneWire Temperature Sensor with ESP8266
 * ============================================================
 * 
 * Sensor:    DS18B20 (waterproof or TO-92 package)
 * Interface: 1-Wire (single data line, no I2C/SPI)
 * Libraries: OneWire + DallasTemperature
 *
 * WIRING (Parasite Power Mode - 2 wires):
 *  DS18B20 GND  --> NodeMCU GND
 *  DS18B20 DQ   --> NodeMCU D4 (GPIO2)   ← with 4.7kΩ to 3.3V
 *  DS18B20 VDD  --> GND (parasite power)
 *
 * WIRING (Normal Power Mode - 3 wires, RECOMMENDED):
 *  DS18B20 GND  --> NodeMCU GND
 *  DS18B20 DQ   --> NodeMCU D4 (GPIO2)   ← with 4.7kΩ to 3.3V
 *  DS18B20 VDD  --> NodeMCU 3.3V
 *
 * CONCEPTS COVERED:
 *  1. Single sensor read
 *  2. Reading multiple DS18B20 sensors on ONE wire
 *  3. Identifying sensors by unique 64-bit address
 *  4. Non-blocking temperature reads with millis()
 * ============================================================
 */

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4   // GPIO2 — the data line

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Store addresses for multiple sensors (each DS18B20 has a unique 64-bit ROM)
DeviceAddress sensor1Addr, sensor2Addr;

// Non-blocking timer
unsigned long lastReadTime   = 0;
const long    READ_INTERVAL  = 2000;  // Read every 2 seconds

void printAddress(DeviceAddress addr) {
  for (uint8_t i = 0; i < 8; i++) {
    if (addr[i] < 16) Serial.print("0");
    Serial.print(addr[i], HEX);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n--- DS18B20 Tutorial ---");

  sensors.begin();

  // Count how many devices are on the bus
  int deviceCount = sensors.getDeviceCount();
  Serial.print("Found "); Serial.print(deviceCount); Serial.println(" sensor(s).");

  // Print addresses of each sensor found
  for (int i = 0; i < deviceCount; i++) {
    DeviceAddress addr;
    if (sensors.getAddress(addr, i)) {
      Serial.print("  Sensor "); Serial.print(i);
      Serial.print(" address: "); printAddress(addr); Serial.println();
    }
  }

  // Cache the first two sensor addresses for direct fast reads
  sensors.getAddress(sensor1Addr, 0);
  sensors.getAddress(sensor2Addr, 1);

  // Set resolution: 9-bit (fastest, 0.5°C) to 12-bit (slowest, 0.0625°C)
  sensors.setResolution(sensor1Addr, 12);
  sensors.setResolution(sensor2Addr, 12);
}

void loop() {
  // Non-blocking read — only request temp every READ_INTERVAL ms
  if (millis() - lastReadTime >= READ_INTERVAL) {
    lastReadTime = millis();

    // requestTemperatures() triggers all sensors simultaneously
    sensors.requestTemperatures();

    // ── Method 1: Read by index (simple, all sensors) ──────────────────────
    int total = sensors.getDeviceCount();
    for (int i = 0; i < total; i++) {
      float tempC = sensors.getTempCByIndex(i);
      float tempF = sensors.getTempFByIndex(i);

      Serial.print("Sensor "); Serial.print(i + 1);
      Serial.print(": "); Serial.print(tempC); Serial.print(" °C  /  ");
      Serial.print(tempF); Serial.println(" °F");

      if (tempC == DEVICE_DISCONNECTED_C) {
        Serial.println("  ERROR: Sensor disconnected or wiring fault!");
      }
    }

    // ── Method 2: Read by saved address (faster for specific sensors) ───────
    float t1 = sensors.getTempC(sensor1Addr);
    Serial.print("Sensor 1 by address: "); Serial.print(t1); Serial.println(" °C");

    Serial.println("---");
  }
}

/*
 * ─── NOTES ────────────────────────────────────────────────────────────────────
 *
 * Pull-up Resistor:
 *   MANDATORY. A 4.7kΩ resistor between DQ and VDD is required.
 *   Without it the sensor will read -127°C or DEVICE_DISCONNECTED.
 *
 * Resolution vs. Conversion Time:
 *   9-bit  → 93.75ms conversion,  0.5°C   resolution
 *   10-bit → 187.5ms,             0.25°C
 *   11-bit → 375ms,               0.125°C
 *   12-bit → 750ms,               0.0625°C  ← default
 *   Use sensors.setWaitForConversion(false) + manual delay for async reads.
 *
 * Multiple Sensors (up to 127):
 *   All share one GPIO pin. The 1-Wire protocol uses ROM addressing to
 *   differentiate sensors. Use sensors.getAddress() to discover addresses,
 *   then hardcode them for production firmware.
 *
 * Libraries:
 *   Arduino Library Manager: "OneWire" by Jim Studt
 *   Arduino Library Manager: "DallasTemperature" by Miles Burton
 *
 * Real-World Use in These Projects:
 *   - fall_detection_iot:         Body temperature monitoring with alert
 *   - water_quality-_monitoring:  Dual sensor for inlet/outlet water temperature
 */
