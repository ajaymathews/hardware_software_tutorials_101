# Linux Kernel Module: Tutorial Series

A comprehensive set of 10+ tutorials for mastering Linux Device Driver development. This repository covers everything from basic module loading to advanced `ioctl`, `procfs`, `sysfs`, and `Interrupt` management.

## 📁 Repository Structure

1.  **MODULE_LOAD_UNLOAD:** Basic skeleton for kernel modules.
2.  **MODULE_WITH_PARAMETER:** Passing arguments to a module at load time.
3.  **MAJ_MIN_NUM:** Allocating and managing major/minor device numbers.
4.  **DEVICE_FILES:** Registering character devices and creating nodes in `/dev`.
5.  **DEVICE_DRIVER:** Full character driver implementation with file operations.
6.  **IOCTL:** User-space communication using `ioctl` calls.
7.  **PROC_FILE:** Monitoring kernel data through the `/proc` filesystem.
8.  **SYSFS:** Interface for managing device attributes in `/sys`.
9.  **INTERRUPT:** Handling hardware interrupts and GPIO interaction.
10. **WAIT_QUEUE_CREATION:** Sleeping and waking up processes synchronously.

## 🛠 Prerequisites

Ensure you have the necessary build headers and tools installed on your Linux system:
```bash
sudo apt-get update
sudo apt-get install build-essential linux-headers-$(uname -r)
```

## 🚀 Building the Tutorials

### Build Everything
To build all 10 tutorials at once, run the root Makefile:
```bash
make
```

### Build Individual Module
Navigate to the specific folder and run:
```bash
make
```

## 🧪 Testing the Drivers

I have included an automated testing script `test_module.sh`. It will build the module, clean your `dmesg` buffer, load the module, show the logs, and then unload it safely.

**Usage:**
```bash
chmod +x test_module.sh
./test_module.sh DEVICE_DRIVER/1.MODULE_LOAD_UNLOAD
```

## ⚖ License
This project is open-source and intended for educational purposes.

---
*Happy Kernel Coding!*
