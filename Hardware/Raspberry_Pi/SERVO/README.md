# Servo Motor Control

This tutorial demonstrates how to control a standard servo motor using PWM signals.

## 🔌 Circuit Diagram

```mermaid
graph LR
    Pi_5V[Pin 2 - 5V] --- VCC[Servo VCC - Red]
    Pi_GND[Pin 6 - GND] --- GND[Servo GND - Black]
    Pi_PWM[Pin 22 - Signal] --- Sig[Servo Signal - Orange]
```

## 🚀 Note
This script uses `GPIO.BOARD` numbering for the PWM signal.
