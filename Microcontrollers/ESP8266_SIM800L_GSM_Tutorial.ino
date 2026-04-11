/*
 * ============================================================
 *  Tutorial: SIM800L GSM Module — AT Commands with ESP8266
 * ============================================================
 * 
 * Module:    SIM800L (or SIM800C / SIM900A — same AT command set)
 * Interface: UART / SoftwareSerial
 * Voltage:   SIM800L requires 3.4–4.4V power supply.
 *            Do NOT power from NodeMCU 3.3V — it cannot supply enough current.
 *            Use a dedicated LiPo cell or a step-down from 5V with large caps.
 *
 * WIRING:
 *  SIM800L VCC   --> 4.0V regulated supply (NOT NodeMCU 3.3V)
 *  SIM800L GND   --> Shared GND with NodeMCU
 *  SIM800L TX    --> NodeMCU D6 (GPIO12) — RX of SoftwareSerial
 *  SIM800L RX    --> NodeMCU D5 (GPIO14) — TX of SoftwareSerial
 *                    (Use a 1kΩ + 2kΩ voltage divider on this line
 *                     to bring 3.3V logic down to 2.8V for SIM800L RX)
 *
 * CONCEPTS COVERED:
 *  1. GSM module initialisation and signal quality check
 *  2. Sending an SMS via AT commands
 *  3. Making a voice call
 *  4. Reading incoming SMS messages
 *  5. Non-blocking serial bridge pattern
 * ============================================================
 */

#include <SoftwareSerial.h>
#include "../include/secrets.h"   // Contains ALERT_PHONE definition

// D5 = TX to SIM800L, D6 = RX from SIM800L
SoftwareSerial gsmSerial(D6, D5);  // RX, TX

String phoneNumber = ALERT_PHONE;  // e.g. "+447911123456"

// ─── Helper Functions ─────────────────────────────────────────────────────────

// Send AT command and wait for expected response with timeout
bool sendATCommand(const String& cmd, const String& expected, int timeoutMs = 2000) {
  gsmSerial.println(cmd);
  unsigned long start = millis();
  String response = "";
  while (millis() - start < (unsigned long)timeoutMs) {
    while (gsmSerial.available()) {
      response += (char)gsmSerial.read();
    }
    if (response.indexOf(expected) != -1) {
      Serial.print("  [OK] "); Serial.println(cmd);
      return true;
    }
  }
  Serial.print("  [TIMEOUT] "); Serial.print(cmd);
  Serial.print(" — got: "); Serial.println(response);
  return false;
}

void sendSMS(const String& number, const String& message) {
  Serial.println("Sending SMS...");
  sendATCommand("AT+CMGF=1", "OK");                     // Set text mode
  sendATCommand("AT+CMGS=\"" + number + "\"", ">");     // Set recipient
  gsmSerial.print(message);
  gsmSerial.write(26);   // ASCII CTRL+Z = send SMS
  delay(5000);           // Wait for network ACK
  Serial.println("SMS should be sent.");
}

void makeCall(const String& number) {
  Serial.println("Dialling...");
  sendATCommand("ATD" + number + ";", "OK");  // Semicolon = voice call
  delay(20000);   // Let it ring for 20 seconds
  sendATCommand("ATH", "OK");                 // Hang up
  Serial.println("Call ended.");
}

// ─── Setup ───────────────────────────────────────────────────────────────────

void setup() {
  Serial.begin(115200);
  gsmSerial.begin(9600);   // SIM800L default baud rate

  Serial.println("\n--- SIM800L GSM Tutorial ---");
  Serial.println("Waiting for SIM800L to boot (5s)...");
  delay(5000);

  // ── Handshake ──────────────────────────────────────────────────────────────
  sendATCommand("AT", "OK");              // Basic handshake
  sendATCommand("AT+CSQ", "OK");         // Signal quality (0-31, 99=unknown)
  sendATCommand("AT+CCID", "OK");        // SIM card ICCID check
  sendATCommand("AT+CREG?", "+CREG: 0,1", 5000);  // Network registration (1=home, 5=roaming)

  Serial.println("GSM module ready.");
}

// ─── Loop ────────────────────────────────────────────────────────────────────

bool alertSent = false;

void loop() {
  // Example: trigger alert once on startup (simulate sensor crossing threshold)
  if (!alertSent) {
    sendSMS(phoneNumber, "ALERT: Temperature exceeded threshold!");
    // makeCall(phoneNumber);   // Uncomment to also make a call
    alertSent = true;
  }

  // ── Serial Bridge (for debugging AT commands manually via Serial Monitor) ──
  while (Serial.available()) {
    gsmSerial.write(Serial.read());
  }
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}

/*
 * ─── NOTES ────────────────────────────────────────────────────────────────────
 *
 * POWER SUPPLY (Most Common Cause of Failure):
 *   SIM800L draws up to 2A peak during TX bursts. Power it from a Li-ion cell
 *   (3.7V) or a 5V supply through a step-down regulator, with a 100-1000µF
 *   bulk capacitor directly across VCC-GND on the module.
 *
 * AT+CSQ Response:
 *   +CSQ: <rssi>,<ber>
 *   rssi 10-20 = good signal; below 5 = poor; 99 = no signal.
 *
 * Setting Network Operator Manually:
 *   AT+COPS=1,2,"23430"   (numeric mode, UK O2 = 23430)
 *
 * Reading Incoming SMS:
 *   AT+CMGF=1             (text mode)
 *   AT+CMGL="ALL"         (list all messages)
 *   AT+CMGR=1             (read message at index 1)
 *   AT+CMGD=1             (delete message at index 1)
 *
 * Libraries: None required — pure AT commands over SoftwareSerial.
 *
 * Real-World Use in These Projects:
 *   - water_quality-_monitoring: GSM call/SMS when water temp exceeds threshold
 *     (see archive/CODE/SENSORS/GSMTEST/GSMTEST.ino for the original code)
 */
