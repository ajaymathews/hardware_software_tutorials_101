# Tutorial: Real-Time IoT Telemetry with Blynk

This tutorial explains how to integrate the **Blynk IoT platform** with your Raspberry Pi for real-time sensor monitoring and remote data visualization. This is the exact technique used in the Stair Climbing Wheelchair and VR Robot projects.

## 🛠 Prerequisites
1. **Blynk App:** Download on iOS or Android.
2. **Blynk Cloud Account:** Create a free account at [blynk.cloud](https://blynk.cloud).
3. **Auth Token:** Create a new "Template" and a "Device" in the Blynk web console to get your 32-character Auth Token.
4. **Library:** Install the Python wrapper:
   ```bash
   pip install blynk-library-python
   ```

---

## 🔌 Example Code: Non-Blocking Telemetry Thread

The best way to use Blynk is by running it in a **background thread**. This prevents the IoT communication from slowing down your main robot control loops.

```python
import time
import threading
import BlynkLib

# CONFIGURATION
BLYNK_AUTH = 'YOUR_AUTH_TOKEN_HERE'

# Initialize Blynk
blynk = BlynkLib.Blynk(BLYNK_AUTH)

def blynk_thread():
    """Background thread to handle Blynk sync."""
    print("Blynk connection thread started.")
    while True:
        blynk.run()
        time.sleep(0.01)

def send_data():
    """Timer-based function to send sensor data."""
    while True:
        # Simulated sensor data (e.g. Temperature / Battery)
        temp = 25.5
        battery = 88
        
        # Send to Virtual Pins
        blynk.virtual_write(1, temp)    # V1 in Blynk App
        blynk.virtual_write(2, battery) # V2 in Blynk App
        
        print(f"Blynk Update: Temp={temp}, Battery={battery}")
        time.sleep(5) # Send every 5 seconds

if __name__ == "__main__":
    # Start the background threads
    threading.Thread(target=blynk_thread, daemon=True).start()
    threading.Thread(target=send_data, daemon=True).start()

    # Main Control Loop (Free to do other things!)
    print("Main loop is running independently...")
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("Stopping...")
```

---

## 📱 Blynk App Configuration
1. Open the Blynk App and go to your **Template**.
2. Add a **Gauge Widget** and link it to **Virtual Pin V1** (Temperature).
3. Add a **Value Display Widget** and link it to **Virtual Pin V2** (Battery).
4. Watch the numbers update in real-time as your Raspberry Pi script runs!

## 📝 Learning Objectives
- **IoT Architecture:** How "Virtual Pins" act as data interfaces between hardware and apps.
- **Multi-threading:** Keeping cloud sync separate from physical hardware control.
- **Latency Management:** Why we use `blynk.run()` in a tight loop but send data slowly.
