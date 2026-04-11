import tkinter
import tkinter.filedialog
from tkinter import filedialog
from tkinter import Tk, Label, Button
import base64
import time

import serial


lifi = serial.Serial(
              
               port='COM6',
               baudrate = 9600,
               parity=serial.PARITY_NONE,
               stopbits=serial.STOPBITS_ONE,
               bytesize=serial.EIGHTBITS,
               timeout=.1
    )






    




class MyFirstGUI:
    def __init__(self, master):
        self.master = master
        master.title("LIFI MALABAR COLLEGE")

        self.label = Label(master, text="LiFi Data Transfer!")
        self.label.pack()

        self.greet_button = Button(master, text="Recieve file", command=self.filez)
        self.greet_button.pack()

        self.greet_button = Button(master, text="Save image", command=self.file_save)
        self.greet_button.pack()

        self.close_button = Button(master, text="Save video", command=self.file_save1)
        self.close_button.pack()

    def filez(self):
        
        f = filedialog.asksaveasfile(parent=root,mode='w',title='recieve file', defaultextension=".txt")
        print(f)
        if f is None: # asksaveasfile return `None` if dialog closed with "cancel".
            return

        while True:
            llf=0
            for line in lifi:
                print(line)
                f.write(line)
                f.close()
                llf=1
            if llf==1:
                break
                #lifi.close()
                #print"breaked"
                #quit()
            
                
        

    def file_save(self):
        filez = filedialog.askopenfilenames(parent=root,title='Choose a file')
       # print root.tk.splitlist(filez)
        #print filez
        lis = list(filez)
        print(lis)
        file = open(lis[0],'rb')
        imgstring = file.read()
        file.close()
        save = filedialog.askdirectory(initialdir='.')
        print(save)
        imgdata = base64.b64decode(imgstring)
        filename = '/image1.png'  # I assume you have a way of picking unique filenames
        with open(save+filename, 'wb') as f:
            f.write(imgdata)
    def file_save1(self):
        filez = tkFileDialog.askopenfilenames(parent=root,title='Choose a file')
       # print root.tk.splitlist(filez)
        #print filez
        lis = list(filez)
        print(lis)
        file = open(lis[0],'rb')
        imgstring = file.read()
        file.close()
        save = filedialog.askdirectory(initialdir='.')
        print(save)
        imgdata = base64.b64decode(imgstring)
        filename = '/video.gif'  # I assume you have a way of picking unique filenames
        with open(save+filename, 'wb') as f:
            f.write(imgdata)

root = Tk()
my_gui = MyFirstGUI(root)
root.mainloop()  
