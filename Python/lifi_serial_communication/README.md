# LiFi Serial Communication Tutorial

Simulate LiFi (Light Fidelity) data transmission using Python and Serial communication.

## 📝 Description
This tutorial demonstrates how to transmit and receive files (text, images, and videos) over a serial port. In a real-world LiFi system, the serial data would be converted into light pulses and decoded by a receiver. 

The project includes both a transmitter (`cardtocardtx.py`) and a receiver (`cardtocardrx.py`) with a Tkinter-based GUI.

## 🛠 Installation
You will need to install the `pyserial` library:

```bash
pip install pyserial
```

## 🚀 Execution
### 1. Identify the COM Ports
Check your Device Manager (Windows) or `/dev/` directory (Linux/macOS) to find the COM ports for your serial adapters. Update the `port='COM6'` line in both transmitter and receiver scripts if necessary.

### 2. Run the Receiver
```bash
cd CODES
python cardtocardrx.py
```
Click **Receive file** and select a location to save the incoming data.

### 3. Run the Transmitter
```bash
cd CODES
python cardtocardtx.py
```
Click **Send file** and select the file you wish to transmit.

## 📖 Step-by-Step Instructions
1. **Connect Hardware**: Ensure your serial hardware (TTL to USB adapters or microcontrollers) is connected.
2. **Launch Receiver**: The receiver must be ready before transmission begins.
3. **Select File**: Use the GUI to pick a file to send.
4. **Data Conversion**: The transmitter encodes the file into Base64 format and sends it byte-by-byte.
5. **Reconstruction**: The receiver captures the bytes, decodes them back from Base64, and saves the file to your disk.

---
**Note**: This tutorial also includes helper scripts for simple image-to-string and string-to-image conversions (`imgtotstring.py` and `stringtoimg.py`).
