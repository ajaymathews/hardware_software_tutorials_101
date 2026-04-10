# C Programming Tutorial

A comprehensive guide from basic C syntax to advanced Data Structures and Embedded Hardware Mocking (CAN). 

This repository serves as a meticulously structured learning path for mastering the core tenets of the C programming language, prioritizing system architecture safety, cross-platform portability, and explicit memory handling.

## Curriculum

This masterclass explores several rigorous domains in C, including:

* **Pointers**
  * Single & Double Pointers
  * Function Pointers
  * Void Pointers and Array Mapping
* **Data Structures**
  * Linked Lists
  * Stacks
  * Queues
* **File I/O & Preprocessors**
  * Advanced System Macro Configurations
  * Sequential Read/Write Mechanics
* **Embedded Concepts**
  * Mock Hardware Drivers (CAN Simulation)
  * Low-Level Bitwise Operations

## How to Run

### For VSCode Users
1. Ensure you have the **C/C++ Extension** (by Microsoft) installed in VSCode.
2. Open the cloned directory `c_tutorials` within your VSCode workspace.
3. Open any targeted `.c` source file.
4. If you have the **Code Runner** extension installed, you can simply click the **Play Button** in the top right corner.
5. *(Optional)* Alternatively, configure your `tasks.json` to build via GCC directly dynamically.

### For Terminal Users (GCC)
If compiling and executing purely from a terminal environment:

1. **Compile the file:** Navigate to the folder containing your target script and compile it using `gcc`:
   ```bash
   gcc filename.c -o my_program
   ```
2. **Execute the compiled binary:** 
   - **On Linux / macOS:**
     ```bash
     ./my_program
     ```
   - **On Windows (PowerShell/CMD):**
     ```cmd
     .\my_program.exe
     ```