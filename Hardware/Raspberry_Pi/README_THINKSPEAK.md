# ThinkSpeak IoT Setup Guide

To use the `thingspeak_ultrasonic.py` script provided in this repository, you must create a free ThinkSpeak account and generate your own API key.

## 🚀 Steps to Generate Your API Key

1.  **Sign Up:** Go to [ThinkSpeak.com](https://thingspeak.com/) and create a free account.
2.  **Create a New Channel:**
    *   Click on **Channels** -> **My Channels**.
    *   Click **New Channel**.
    *   Give it a name (e.g., "Raspberry Pi Ultrasonic").
    *   Enable **Field 1** (e.g., "Distance").
    *   Scroll down and click **Save Channel**.
3.  **Get Your Write API Key:**
    *   Click on the **API Keys** tab.
    *   Copy the **Write API Key**.
4.  **Update the Code:**
    *   Open `Hardware/Raspberry_Pi/ULTRASONIC_THINKSPEAK/thingspeak_ultrasonic.py`.
    *   Find the line: `myAPI = "YOUR_API_KEY_HERE"`.
    *   Replace `YOUR_API_KEY_HERE` with your actual key.

## 📊 Viewing Your Data
Once the script is running, click on the **Private View** tab in your ThinkSpeak dashboard to see your distance measurements updated in real-time on a graph!

---
*Note: This tutorial is for educational purposes only. Keep your API keys private!*
