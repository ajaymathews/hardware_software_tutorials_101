import tkinter as tk
from tkinter import Label,Entry
from urllib.request import urlopen
r=tk.Tk()

WRITE_API_KEY='N7OCE4YXKZFG8GGJ'
CHANNEL_ID ='823600'
field_no=1                  #Setting  field as 1

Label(r, text='INPUT DATA :',font=12).grid(row=0,column=0)
e1 = Entry(r,font=12)
e1.grid(row=0, column=1)

def send():
    val = e1.get()                       #Getting the value from the entry field
    value=int(val)                       #Typecasted to int
    field_id=str("field"+str(field_no))
    upload=urlopen('http://api.thingspeak.com/update?api_key=%s&%s=%d'% (WRITE_API_KEY,field_id,value))
    print(str("status code:"+str(upload.getcode())))

button_1 = tk.Button(r, text='SEND', bg='LightSkyBlue1',activebackground='green2',width=25, font=12,command=send)
button_1.grid(row=1)
r.mainloop()