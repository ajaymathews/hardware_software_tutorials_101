# Multithreading Basics Tutorial

Learn how to run multiple functions simultaneously in Python using the `_thread` module.

## 📝 Description
This tutorial demonstrates basic multithreading where two separate loops (`test1` and `test2`) are started as independent threads. This allows "test1" (counting from 1000) and "test2" (counting from 1) to print to the console at same time, rather than waiting for one to finish before starting the other.

## 🛠 Installation
This tutorial uses the built-in `_thread` and `time` modules. No external `pip` installations are required.

## 🚀 Execution
Run the script using Python:
```bash
python thread_test.py
```

## 📖 Step-by-Step Instructions
1. **Thread Start**: The program calls `_thread.start_new_thread(test1, () )` and `_thread.start_new_thread(test2, () )`.
2. **Execution**: You will see interleaved output in the console. 
   - `test1: 1000`
   - `test2: 1`
   - `test1: 1001`
   - `test2: 2`
3. **Observation**: Notice how both functions are executing in parallel.

---
**💡 Discussion**: While `_thread` is a low-level module, for most modern Python applications, it is recommended to use the higher-level `threading` module ($import threading$).
