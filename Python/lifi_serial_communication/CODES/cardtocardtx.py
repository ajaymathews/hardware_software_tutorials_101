import tkinter
import tkinter.filedialog
from tkinter import filedialog
from tkinter import Tk, Label, Button
import base64

import serial


lifi = serial.Serial(
              
               port='COM3',
               baudrate = 4800,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_ONE,
               bytesize=serial.EIGHTBITS,
               timeout=.1
    )
"""
pic = serial.Serial(
              
               port='COM9',
               baudrate = 9600,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_ONE,
               bytesize=serial.EIGHTBITS,
               timeout=.1
    )
f = open('automation.txt','r')
message = f.read()
print(message)
if(message=="f"):
    pic.write(message)
f.close()
"""


class MyFirstGUI:
    def __init__(self, master):
        self.master = master
        master.title("LIFI")

        self.label = Label(master, text="LiFi Data Transfer!")
        self.label.pack()

        self.greet_button = Button(master, text="Choose File", command=self.filez)
        self.greet_button.pack()

        self.greet_button = Button(master, text="Choose image", command=self.img)
        self.greet_button.pack()

        self.close_button = Button(master, text="Choose video ", command=self.vid)
        self.close_button.pack()

    def filez(self):
        print("Choosing file!")
        filez = filedialog.askopenfilenames(parent=root,title='Choose a file')
        print(root.tk.splitlist(filez))
        lis = list(filez)
        print(lis)
        file  = open(lis[0], "rb")
        str = file.read()
        lifi.write(str)
        file.close()
    def img(self):
        print("Choosing! image")
        filez = filedialog.askopenfilenames(parent=root,title='Choose a file')
       # print root.tk.splitlist(filez)
        #print filez
        lis = list(filez)
        print(lis)

        with open(lis[0], "rb") as imageFile:
            str =str(base64.b64encode(imageFile.read()))
            file  = open('file.txt','a')
            file.write(str)
            lifi.write(str)
            file.close()
    def vid(self):
        print("Choosing! video")
        filez = filedialog.askopenfilenames(parent=root,title='Choose a file')
       # print root.tk.splitlist(filez)
        #print filez
        lis = list(filez)
        print(lis)

        with open(lis[0], "rb") as imageFile:
            str = str(base64.b64encode(imageFile.read()))
            file  = open('vid.txt','a')
            file.write(str)
            lifi.write(str)
            file.close()

root = Tk()
my_gui = MyFirstGUI(root)
root.mainloop()

