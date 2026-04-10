# DHT11 Temperature & Humidity Sensor

This tutorial demonstrates how to read data from a DHT11 sensor using the `dht11` library.

## 🔌 Circuit Diagram

```mermaid
graph TD
    Pi_VCC[Pin 2 - 5V] --- VCC[Sensor VCC]
    Pi_GND[Pin 6 - GND] --- GND[Sensor GND]
    Pi_Data[Pin 7 - Data] --- Data[Sensor Data]
```

## 🚀 Setup
Ensure you have the `dht11` Python library installed on your Raspberry Pi.
