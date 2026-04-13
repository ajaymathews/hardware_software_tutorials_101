# ThingSpeak API Functions

Learn how to interact with the ThingSpeak IoT platform using Python's `urllib` and `json` modules.

## 📝 Description
This tutorial provides a collection of functions to read from and write to ThingSpeak channels. It includes a command-line interface (CLI) to test these functions in real-time.

## 🛠 Prerequisites
You need a [ThingSpeak account](https://thingspeak.com/) and a Channel with:
- `WRITE_API_KEY`
- `READ_API_KEY`
- `CHANNEL_ID`

Update these constants in `thinkspeak_functions.py` before running.

## 🛠 Installation
This tutorial uses standard Python libraries. No external `pip` installations are required.

## 🚀 Execution
Run the script using Python:
```bash
python thinkspeak_functions.py
```

## 📖 Step-by-Step Instructions
1. **Write Data**: Choose option 1 to upload a numeric value to a specific field in your channel.
2. **Read All Data**: Choose option 2 to fetch all historical entries for a field.
3. **Read Last Value**: Choose option 3 to fetch the most recent entry.
4. **Read Channel Name**: Choose option 4 to retrieve the metadata for your channel.

---
**💡 Discussion**: ThingSpeak is an excellent platform for visualizing sensor data from devices like NodeMCU or Raspberry Pi. Using Python, you can build powerful dashboards or data analysis tools that interact with your hardware remotely.