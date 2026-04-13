# Computer Vision Basics: Vision Eye Test

A GUI application built with Python and Tkinter to test visual acuity (similar to a Snellen chart).

## 📝 Description
The program displays random letters of decreasing size. The user must type the letters they see into an entry box. The program then calculates the user's vision level based on the smallest font size they correctly identified (e.g., "nYou have 4 / 6 vision").

## 🛠 Installation
This tutorial uses standard Python libraries. No external `pip` installations are required if you have Python installed with Tkinter.

On most Linux systems, you might need to install Tkinter manually:
```bash
sudo apt-get install python3-tk
```

## 🚀 Execution
Run the script using Python:
```bash
python vision-test.py
```

## 📖 Step-by-Step Instructions
1. **Launch**: A window will appear with large letters and an input field.
2. **Identification**: Type the letters you see (without spaces) and press the **Test** button or hit **ENTER**.
3. **Progression**: If correct, the letters will get smaller.
4. **Completion**: If you enter an incorrect sequence or reach the end, the program will close and open a "Result" window showing your final score.

---
**Note**: This is a coding demonstration of font-handling and GUI state-management in Tkinter, not a calibrated medical tool.
