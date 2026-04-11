import time
import random
from tkinter import *


# collection = ['C', 'D', 'E', 'F', 'L', 'N', 'O', 'P', 'T', 'Z', 'a', 'r', 'U', 'X', 'M', 'H', 'h', 'l', 'g', 't', '7', '4']
# size = [210, 180, 150, 120, 90, 60, 30, 20, 15, 10, 5]

collection = ['C', 'D', 'E', 'F', 'L', 'N', 'O', 'P', 'T', 'Z', 'a', 'r', 'U', 'X', 'M', 'H', 'h', 'l', 'g', 't', '7', '4']
size = [210, 150, 120, 60, 20, 10]

vision = ""

for i in range(0, len(size)):

    letters = ""
    # adding space between each char in letter variable will cause issue while comparing seen variable with letter in test_vision() function
    # at each iteration the no of letters shown increases
    for j in range(0, i+1):
        letters = letters + random.choice(collection)

    # creating a space separated sequence of letters to be shown in the window
    letters_for_window = ""
    for each_letter in letters:
        letters_for_window = letters_for_window + each_letter + " "
    
    root = Tk()
    root.title('Test Your Vision 1.0 - Test')
    root.geometry("800x600+80+60") # resolution (1024x768) as string with starting coordinate of window as left top (0+0)

    canvas = Frame(root, bg = 'red')
    canvas.pack(side="top", expand = 1, fill = 'both')

    read_area = Label(canvas, text = letters)
    read_area.config(bg = 'white', fg = 'black')
    read_area_font = ('Times', size[i], 'bold')
    read_area.config(font = read_area_font)
    read_area.pack(side="top", expand = 1, fill = 'both')

    seen_message = Label(canvas, text = "What do you see (type without spaces and press ENTER/RETURN):", bg = 'white', fg = 'black')
    seen_message.pack(side="left")
    seen_data = StringVar() # creating a string variable to link to the entry box to fetch user input from window
    
    entry_box = Entry(canvas, textvariable = seen_data)
    entry_box.pack(side="left")
    
    def show_result(vision):
        # Test completed. Printing the details of current eyesight stored in vision variable
        # bcz at each level correct ans is evaluated eg:20/20 if all true.
        root = Tk()
        root.title('Test Your Vision 1.0 - Result')
        root.geometry("800x600+80+60") # resolution (1024x768) as string with starting coordinate of window as left top (0+0)

        canvas = Frame(root, bg = 'red')
        canvas.pack(side="top", expand = 1, fill = 'both')

        result = Label(canvas, text = vision)
        result.config(bg = 'white', fg = 'black')
        result_font = ('Lucida Sans Unicode', "20", "bold")
        result.config(font = result_font)
        result.pack(side="top")

        root.mainloop()
        exit(0)

    def test_vision():
        seen = str(seen_data.get())
        
        # set result and set flag so that the next iteration of outer for loop with looping variable i stops
        if seen == "" or len(seen) == 0 or len(seen) != len(letters):
            vision = "You have {0} / {1} vision. Thank you".format(i+1, len(size))
            root.destroy() # closes the window
            show_result(vision)
        else:
            for x in range(len(letters)):
                if seen[x] != letters[x]:
                    vision = "You have {0} / {1} vision. Thank you".format(i, len(size))
                    root.destroy() # closes the window
                    show_result(vision)
                    break
            else:
                root.destroy() # closes the window
                if i == len(size)-1:
                    vision = "You have {0} / {1} vision. Thank you".format(i+1, len(size))
                    show_result(vision)
                
    
    test_button = Button(canvas, text="Test", command=test_vision)
    test_button.bind('<Key-Return>', test_vision)
    test_button.pack(side="left")

    root.mainloop()
        

