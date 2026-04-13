# Google Speech Recognizer Tutorial

Convert your voice into text and make your computer speak back to you using Python.

## 📝 Description
This tutorial demonstrates how to use the `SpeechRecognition` library to capture audio from your microphone and process it using Google's Cloud API. It also uses `pyttsx3` for Text-to-Speech (TTS) to provide a conversational interface.

## 🛠 Installation
You will need to install the following libraries:

```bash
pip install SpeechRecognition
pip install pyttsx3
pip install PyAudio
```

*Note: If you encounter issues installing PyAudio on Windows, you may need to download a pre-compiled wheel or use `pip install pipwin` then `pipwin install pyaudio`.*

## 🚀 Execution
Ensure your microphone is connected and set as the default recording device, then run:
```bash
python SpeechRecognition.py
```

## 📖 Step-by-Step Instructions
1. **Initial Greeting**: The program will say "Hi how can I help you" and start listening.
2. **Speak**: Say anything you want. The program will recognise your speech and repeat it back to you.
3. **Continue or Stop**: 
   - Say "Yes" to repeat the loop.
   - Say "No" or "Stop" to exit the program.
4. **Error Handling**: If the program doesn't understand you, it will ask you to repeat the message.

---
**Troubleshooting**: 
- If you get a "Could not identify the message" error immediately, check your internet connection (Google Speech recognition requires an active connection).
- Ensure your microphone is not muted and the input level is high enough.
