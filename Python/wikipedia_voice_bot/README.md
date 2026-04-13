# Wikipedia Voice Bot Tutorial

Build a voice-activated AI that searches Wikipedia and reads the summary aloud to you.

## 📝 Description
This bot uses your computer's microphone to listen for commands. If you say "hello", it responds back. If you say anything else, it uses that word as a keyword to search Wikipedia, pulls the summary of the most relevant page, and speaks it back to you using Text-to-Speech.

## 🛠 Installation
You will need to install the following libraries:

```bash
pip install wikipedia pyttsx3 SpeechRecognition PyAudio requests pypiwin32
```

*Note: `pypiwin32` is specifically for Windows to handle COM object interactions required by some speech engines.*

## 🚀 Execution
Ensure your microphone is connected and run:
```bash
python PYAUDIO_WITH_GOOGLE_VOICE_RECOGNITION.py
```

## 📖 Step-by-Step Instructions
1. **Trigger**: Wait for the console to print "Say something!".
2. **Command**: 
   - Say **"Hello"** to hear the bot say "HI".
   - Say a **topic** (e.g., "Python programming" or "Mount Everest") to hear a summary from Wikipedia.
3. **Voice**: The bot will read out the first paragraph of the Wikipedia page.
4. **Listening**: The bot runs in a loop and will immediately ask for another command after finishing the speech.

---
**💡 Discussion**: This project combines API interaction (`wikipedia`), GUI-less interactivity (`speech_recognition`), and hardware control (`pyttsx3` for sound). It is the same logic used to build smart home assistants like Alexa or Google Home.
