# ThinkSpeak IoT Ultrasonic Tracker

This tutorial measures distance and automatically uploads the data to your ThinkSpeak cloud dashboard for remote monitoring.

## 🔌 Circuit Diagram

> [!CAUTION]
> **Voltage Divider Required:** The HC-SR04 Echo pin outputs 5V. Use resistors to protect your Pi's 3.3V GPIO input.

```mermaid
graph TD
    Pi_VCC[Pin 2 - 5V] --- VCC[ULTRASONIC VCC]
    Pi_TRIG[Pin 3 - Data] --- TRIG[ULTRASONIC TRIG]
    Pi_ECHO[Pin 5 - Data] --- R1[1k ohm Resistor]
    R1 --- ECHO[ULTRASONIC ECHO]
    R1 --- R2[2k ohm Resistor]
    R2 --- GND[Ground]
```

## 🚀 Setup
- **API Key:** Make sure to replace `YOUR_API_KEY_HERE` in the script with your Write API Key.
- **Numbering:** This script uses `GPIO.BOARD` numbering.
