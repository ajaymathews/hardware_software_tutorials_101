# Tkinter ThingSpeak GUI

A desktop application built with Python and Tkinter to push data to the ThingSpeak IoT platform.

## 📝 Description
This tutorial combines GUI development (Tkinter) with IoT (ThingSpeak). It provides a simple input field where you can type a number and a "SEND" button to upload that number to your ThingSpeak channel in one click.

## 🛠 Prerequisites
You need a [ThingSpeak account](https://thingspeak.com/) and a Channel with:
- `WRITE_API_KEY`
- `CHANNEL_ID`

Update these constants in `Tkinter_Thingspeak.py` before running.

## 🛠 Installation
This tutorial uses standard Python libraries (`tkinter`, `urllib`). No external `pip` installations are required for the core functionality.

## 🚀 Execution
Run the script using Python:
```bash
python Tkinter_Thingspeak.py
```

## 📖 Step-by-Step Instructions
1. **Launch**: A small window will appear with an "INPUT DATA" label and an entry box.
2. **Input**: Type a numeric value into the box.
3. **Send**: Click the **SEND** button.
4. **Verify**: Check the Python console for a "status code: 200" message, then check your ThingSpeak channel dashboard online to see the new data point plotted on your graph.

---
**💡 Tips**: 
- Status code **200** means success.
- If you get an error, check that your `WRITE_API_KEY` is correct and your internet connection is active.
