# Tutorial: Advanced Servo Sequencing with PCA9685

This tutorial demonstrates how to program complex, smooth robotic movements (like a "Pick and Place" sequence) on a Raspberry Pi using the PCA9685 I2C Servo Driver.

## 🔌 Hardware Setup

### Wiring PCA9685 to Raspberry Pi
- **VCC (Logic):** Pin 1 - 3.3V
- **GND:** Pin 6 - Ground
- **SDA:** Pin 3 - (I2C Data)
- **SCL:** Pin 5 - (I2C Clock)
- **V+ (Power):** External 5V/6V Power Supply (Crucial for motors!)

---

## 💻 Smooth Motion Logic

A common problem with robotics is "jerky" movements. Using a `transition_to` function ensures your servos move step-by-step rather than jumping.

```python
import time
from Adafruit_PWM_Servo_Driver import PWM

# Initialize PCA9685
pwm = PWM(0x40)
pwm.setPWMFreq(60)

# Track current positions of all servos
current_pos = {0: 375, 1: 375} # Channel: Pulse

def transition_to(channel, target, delay=0.01):
    """Smoothly moves a servo from current position to target."""
    global current_pos
    start = current_pos[channel]
    
    # Determine direction of movement
    step = 1 if target > start else -1
    
    for pos in range(start, target, step):
        pwm.setPWM(channel, 0, pos)
        time.sleep(delay)
        
    current_pos[channel] = target

# Example Sequence: Pick and Place
def pick_sequence():
    print("Lowering arm...")
    transition_to(1, 600) # Lower arm servo
    
    print("Closing gripper...")
    transition_to(0, 1600) # Close gripper servo
    
    print("Raising arm...")
    transition_to(1, 400) # Raise arm servo

if __name__ == "__main__":
    pick_sequence()
```

---

## 🚀 Key Optimization Tips
1. **The Current Map:** Always keep a dictionary of the `current_pos`. This prevents the servo from "snapping" back to a default when a new command starts.
2. **External Power:** Never power multiple servos directly from the Raspberry Pi 5V pin. It will cause brownouts and crashes.
3. **Step Delays:** Adjust the `delay` in `transition_to` to change the speed of the robot.

## 📝 Learning Objectives
- **Interpolation:** Calculating incremental steps between two points.
- **I2C Communication:** Multiplexing multiple servos over a 2-wire bus.
- **Power Management:** Understanding current draw requirements for robotics.
