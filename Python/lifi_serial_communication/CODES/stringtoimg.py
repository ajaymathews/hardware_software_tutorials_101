import base64
file = open('file.txt','r')
imgstring = file.read()
file.close()
imgdata = base64.b64decode(imgstring)
filename = 'yang.jpg'  # I assume you have a way of picking unique filenames
with open(filename, 'wb') as f:
    f.write(imgdata)
