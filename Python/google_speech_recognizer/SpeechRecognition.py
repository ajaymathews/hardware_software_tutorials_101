import time,pyttsx3
import speech_recognition as sr

def texttospeech(tex):
    engine = pyttsx3.init()
    engine.setProperty('rate', 150)   #100 means the speed of voice
    voices = engine.getProperty('voices')
    engine.say(tex)
    engine.runAndWait()
     
   
def voice(msg):
   texttospeech(msg)
   
def listen():
    r = sr.Recognizer()
    with sr.Microphone() as source:
        print('listening...')
        audio = r.listen(source)
        try:
            q=r.recognize_google(audio)
            print(q)
            return q
        except sr.UnknownValueError:
            print('could identify the message')
            return 'err'

while(1):
        voice('hi how can i help you')
        speech =listen()
        if speech == 'err':
            voice('could identify the message, please repeat once more')
        elif speech == 'stop':
            exit(1)
        else:
            voice('you have said'+speech)
            voice('do you want to say anything again')
            speech=listen()
            if ((speech == 'no') | (speech == 'stop')):
                voice('thank you, see you soon')
                exit(1)
            elif speech == 'yes':
                continue
            else:
                voice('could identify the message')
