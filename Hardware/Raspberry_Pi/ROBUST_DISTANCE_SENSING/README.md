# Tutorial: Robust, Non-Blocking Distance Sensing (HC-SR04)

This tutorial demonstrates how to implement non-blocking distance sensing using the HC-SR04 Ultrasonic sensor and Python's `threading` library. This allows your Raspberry Pi robot to measure distance in the background while performing other tasks (like driving or communicating) without "stuttering".

## 🔌 Hardware Setup

> [!CAUTION]
> **Voltage Divider Protection:** The HC-SR04 Echo pin outputs 5V. You MUST use a voltage divider (1kΩ and 2kΩ resistors) to step this down to 3.3V before connecting to the Raspberry Pi GPIO pins.

### Recommended Wiring
- **VCC:** Pin 2 - 5V
- **GND:** Pin 6 - Ground
- **TRIG:** BCM 23 - (Control Output)
- **ECHO:** BCM 24 - (Signal Input via Resistors)

---

## 💻 Standalone Non-Blocking Class

This class encapsulates the distance logic into a background thread, providing an always-updated `sensor.distance` value.

```python
import time
import threading
import RPi.GPIO as GPIO

class RobustDistanceSensor:
    def __init__(self, trig, echo):
        self.trig = trig
        self.echo = echo
        self.distance = 100.0
        self.running = True
        
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.trig, GPIO.OUT)
        GPIO.setup(self.echo, GPIO.IN)
        
        # Start the background polling thread
        threading.Thread(target=self._poll_sensor, daemon=True).start()

    def _poll_sensor(self):
        while self.running:
            # Trigger pulse
            GPIO.output(self.trig, True)
            time.sleep(0.00001)
            GPIO.output(self.trig, False)

            timeout = time.time() + 0.1 # 100ms timeout
            start_time = time.time()
            stop_time = time.time()

            # Pulse detection
            while GPIO.input(self.echo) == 0 and time.time() < timeout:
                start_time = time.time()
            while GPIO.input(self.echo) == 1 and time.time() < timeout:
                stop_time = time.time()

            # Speed of sound calc (343 m/s)
            elapsed = stop_time - start_time
            new_dist = (elapsed * 34300) / 2
            
            # Simple outlier filter (discard values > 400cm)
            if new_dist < 400:
                self.distance = new_dist
                
            time.sleep(0.05) # 20Hz polling rate

    def stop(self):
        self.running = False

# --- Usage Example ---
if __name__ == "__main__":
    try:
        # Initialize sensor on BCM 23 (Trig) and BCM 24 (Echo)
        sensor = RobustDistanceSensor(trig=23, echo=24)
        
        print("Polling distance in background. Control is returned to your loop!")
        while True:
            print(f"Latest Distance: {sensor.distance:.1f} cm")
            time.sleep(0.5)
            
    except KeyboardInterrupt:
        GPIO.cleanup()
```

---

## 📝 Learning Objectives
- **Threading:** How to offload I/O-intensive tasks to a background process.
- **Timing Accuracy:** Why `time.time()` is used for precise pulse duration.
- **Outlier Rejection:** Implementing simple checks to prevent "ghost" readings.
