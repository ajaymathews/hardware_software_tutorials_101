
import wikipedia
import requests
import win32com.client
import time,pyttsx3,re
import speech_recognition as sr

def search_wiki(keyword=''):
  # running the query
  searchResults = wikipedia.search(keyword)
  # If there is no result, print no result
  if not searchResults:
    print("No result from Wikipedia")
    return
  # Search for page... try block 
  try:
    page = wikipedia.page(searchResults[0])
  except (wikipedia.DisambiguationError, err):
    page = wikipedia.page(err.options[0])
  
  wikiTitle = str(page.title.encode('utf-8'))
  wikiSummary = str(page.summary.encode('utf-8'))
  print(wikiSummary)
  texttospeech(wikiSummary)

def texttospeech(tex):
    engine = pyttsx3.init()
    engine.setProperty('rate', 170)

    voices = engine.getProperty('voices')
    engine.say(tex)
    engine.runAndWait()
    

while True:
##    texttospeech("Google Speech Recognition could not understand audio")
    r = sr.Recognizer()
    with sr.Microphone() as source:
      print("Say something!")
      audio = r.listen(source)  
    try:
      q=r.recognize_google(audio)
##      q=q.decode()
##      q=r.recognize_bing(audio)
      print(q)
      if 'hello' in q:
          texttospeech("HAI")
      else:
          search_wiki(q)
    except sr.UnknownValueError:
      print("Google Speech Recognition could not understand audio")
      texttospeech("Google Speech Recognition could not understand audio")
      








    
