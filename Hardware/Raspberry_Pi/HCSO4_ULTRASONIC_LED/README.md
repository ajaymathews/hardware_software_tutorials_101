# HC-SR04 Ultrasonic Sensor with LED Feedback

This tutorial measures distance and provides visual feedback using a Matplotlib-based GUI that changes color based on proximity.

## 🔌 Circuit Diagram

> [!CAUTION]
> **Voltage Divider Required:** The HC-SR04 Echo pin outputs 5V, but the Raspberry Pi inputs only handle 3.3V. You must use resistors to step down the voltage.

```mermaid
graph TD
    Pi_VCC[Pin 2 - 5V] --- VCC[ULTRASONIC VCC]
    Pi_TRIG[BCM 23 - Pin 16] --- TRIG[ULTRASONIC TRIG]
    Pi_ECHO[BCM 24 - Pin 18] --- R1[1k ohm Resistor]
    R1 --- ECHO[ULTRASONIC ECHO]
    R1 --- R2[2k ohm Resistor]
    R2 --- GND[Ground]
```

## 🚀 Setup
- **Library:** `RPi.GPIO`, `matplotlib`
- **Numbering:** This script uses `GPIO.BCM` numbering.
