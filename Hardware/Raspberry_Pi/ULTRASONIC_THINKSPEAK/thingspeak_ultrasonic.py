import sys
import urllib.request
import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
TRIG = 3
ECHO = 5

GPIO.setup(TRIG,GPIO.OUT)
GPIO.setup(ECHO,GPIO.IN)
myAPI = "YOUR_API_KEY_HERE"  # Replace with your ThinkSpeak Write API Key
baseURL = 'https://api.thingspeak.com/update?api_key=%s' % myAPI 
def ultrason():
    while True:
        GPIO.output(TRIG, True)
        time.sleep(0.00001)
        GPIO.output(TRIG, False)
        StartTime = time.time()
        StopTime = time.time()
        while GPIO.input(ECHO) == 0:
            StartTime = time.time()
        while GPIO.input(ECHO) == 1:
            StopTime = time.time()
     

        TimeElapsed = StopTime - StartTime

        distance = (TimeElapsed * 34300) / 2
        
        conn = urllib.request.urlopen(baseURL + '&field1=%s' % distance)
        print(conn.read())

        time.sleep(20)
        conn.close()

if __name__ == '__main__':
    try:
        while True:
            ultrason()
    finally:
        GPIO.cleanup()
        while True:
                ultrason()
