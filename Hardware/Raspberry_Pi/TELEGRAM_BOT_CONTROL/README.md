# Tutorial: Telegram Bot Control for Raspberry Pi

This tutorial demonstrates how to build a remote control interface for your Raspberry Pi using a Telegram Bot. This allows you to control GPIO pins, capture photos, and receive sensor alerts from anywhere in the world.

## 🛠 Prerequisites
1. **Telegram Account:** Installed on your phone or desktop.
2. **Bot Token:** Message [@BotFather](https://t.me/botfather) on Telegram to create a new bot and receive your unique API Token.
3. **Library:** Install the `python-telegram-bot` wrapper:
   ```bash
   pip install python-telegram-bot==13.7
   ```

---

## 🔌 Example Code: Remote LED & Photo Capture

This standalone script allows you to turn an LED ON/OFF and capture a photo using a USB Webcam or Pi Camera via Telegram.

```python
import telegram
from telegram.ext import Updater, CommandHandler
import RPi.GPIO as GPIO
import cv2 # For USB Webcam support

# CONFIGURATION
TOKEN = 'YOUR_BOT_TOKEN_HERE'
LED_PIN = 18

# Setup GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_PIN, GPIO.OUT)

def start(update, context):
    update.message.reply_text("RPi Bot Online! Use /led_on, /led_off, or /photo")

def led_on(update, context):
    GPIO.output(LED_PIN, True)
    update.message.reply_text("LED is now ON 💡")

def led_off(update, context):
    GPIO.output(LED_PIN, False)
    update.message.reply_text("LED is now OFF 🌑")

def photo(update, context):
    update.message.reply_text("Capturing photo... 📸")
    cap = cv2.VideoCapture(0)
    ret, frame = cap.read()
    if ret:
        cv2.imwrite('shot.jpg', frame)
        with open('shot.jpg', 'rb') as f:
            update.message.reply_photo(photo=f)
    cap.release()

def main():
    updater = Updater(TOKEN, use_context=True)
    dp = updater.dispatcher

    dp.add_handler(CommandHandler("start", start))
    dp.add_handler(CommandHandler("led_on", led_on))
    dp.add_handler(CommandHandler("led_off", led_off))
    dp.add_handler(CommandHandler("photo", photo))

    print("Bot is polling...")
    updater.start_polling()
    updater.idle()

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        GPIO.cleanup()
```

---

## 🚀 How to Use
1. Replace `'YOUR_BOT_TOKEN_HERE'` with the token from BotFather.
2. Run the script on your Pi.
3. Open your Bot on Telegram and type `/start`.
4. Use the commands to control your hardware remotely!

## 📝 Learning Objectives
- **Webhooks vs Polling:** Understanding how the Pi receives messages.
- **Payload Handling:** Sending media (images) over the Telegram API.
- **Asynchronous Logic:** How the bot handles multiple users.
