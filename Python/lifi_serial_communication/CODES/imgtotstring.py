import base64
 
with open("yin.png", "rb") as imageFile:
    str = str(base64.b64encode(imageFile.read()))
    file  = open('file.txt','a')
    file.write(str)
    file.close()
