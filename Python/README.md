# Master Python Tutorials

A comprehensive collection of Python tutorials ranging from basic syntax and data structures to advanced topics like Computer Vision, IoT (ThingSpeak), Socket Programming, and Voice Assistants.

## 🚀 Overview

This repository is designed to take you from Python basics to building real-world hardware and IoT integrations.

### 📘 Basic Python Scripts
These scripts cover the fundamental building blocks of Python:
- `basic_operations.py`: Arithmetic and basic variable usage.
- `class.py`: Introduction to Object-Oriented Programming (OOP) and Classes.
- `dictionaries.py`: Working with Key-Value pairs.
- `errors.py`: Exception handling (`try...except`).
- `files.py`: Reading and writing to text files.
- `functions.py`: Defining and calling reusable code blocks.
- `lists.py`: Working with indexed sequences.
- `os_functions.py`: Interacting with the operating system (paths, directories).
- `sets.py`: Working with unique, unordered collections.

### 🛠 Advanced Tutorials (Subfolders)
Each folder below contains a dedicated `README.md` with specific installation and execution steps:

1. **[Computer Vision Basics](./computer_vision_basics/)**: Vision testing app using Tkinter.
2. **[Google Speech Recognizer](./google_speech_recognizer/)**: Converting voice to text.
3. **[LiFi & Serial Communication](./lifi_serial_communication/)**: Serial data transfer (concept for LiFi).
4. **[Multithreading Basics](./multithreading_basics/)**: Running tasks in parallel.
5. **[QR & Barcode Scanning](./qr_barcode_scanning/)**: Generating and reading QR/Barcodes.
6. **[Socket Client-Server](./socket_client_server/)**: Basic TCP networking.
7. **[Socket Communication](./socket_communication/)**: Advanced networking (Pickle, Chat).
8. **[ThingSpeak API Functions](./thingspeak_api_functions/)**: Interacting with ThingSpeak IoT cloud via Python.
9. **[Tkinter ThingSpeak](./tkinter_thingspeak/)**: GUI app to push data to ThingSpeak.
10. **[Wikipedia Voice Bot](./wikipedia_voice_bot/)**: A voice-activated AI that searches Wikipedia for you.

## ⚙️ General Requirements

To run these tutorials, ensure you have **Python 3.10+** installed. You can check your version with:
```bash
python --version
```

Most tutorials require a virtual environment to manage dependencies:
```bash
python -m venv venv
source venv/bin/activate  # On Windows: venv\Scripts\activate
```

## 📜 Execution
Most basic scripts can be run directly:
```bash
python lists.py
```
For tutorials in subfolders, navigate into the folder first:
```bash
cd google_speech_recognizer
python SpeechRecognition.py
```