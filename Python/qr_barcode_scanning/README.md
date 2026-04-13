# QR & Barcode Scanning and Generation

Learn how to generate and read both QR codes and Barcodes using Python.

## 📝 Description
This tutorial covers two main tasks:
1. **Scanning**: Detecting and decoding symbols from images using `pyzbar` and `OpenCV`.
2. **Generation**: Creating your own custom QR codes and Barcodes (`Code128`, `EAN8`, etc.) as image files.

## 🛠 Installation
You will need to install several libraries for scanning and generation:

```bash
pip install pyzbar opencv-python numpy pyqrcode pypng python-barcode
```

*Note: For `pyzbar` to work, you may also need to install the ZBar shared library on your system (e.g., `sudo apt-get install libzbar0` on Linux).*

## 🚀 Execution
### 1. Generating a QR Code / Barcode
Navigate to the `QR_BAR_CODE_GENERATION` folder:
```bash
cd QR_BAR_CODE_GENERATION
python qcode_gen.py  # Generates ONAM.png
python bcode_gen.py  # Generates barcode images
```

### 2. Scanning / Decoding
```bash
python q_b_code_reader.py
```
This script will read `barcode_code128.png` (or any image path you provide), decode the data, and display the result with a bounding box.

## 📖 Step-by-Step Instructions
1. **Generation**:
   - The script uses `pyqrcode.create()` to generate a QR object from a string.
   - It then saves it as a `.png` with the desired scale.
2. **Decoding**:
   - `cv2.imread()` loads the image.
   - `pyzbar.decode(im)` scans the image for all known symbols.
   - The program loops through the `decodedObjects`, prints the data, and draws a polygon around the detected code using `cv2.line`.
   - `cv2.imshow` displays the final annotated image.

---
**💡 Discussion**: This technology is widely used in inventory management, mobile payments, and ticketing systems.
