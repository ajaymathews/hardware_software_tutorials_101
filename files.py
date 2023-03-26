#file operations
'''
#this functions read all the content upto end, then only it prints the data as per list
#so after every read,readlines, doing an ftell prints the pointer at end of file
f=open("test.txt","r") #fo=open("file.frmt","mode")
'''
'''
with open("test.txt") as f:#same as opening file in read mode
    print(f.read())
'''    


    
#modes of opening file
'''
modes:
r: read only,from begining
rb: read only in binary, from begining
r+: read & write, from begining
rb+:read & write in binary, from begining
w:write only,overwrites.if not exists then create file
wb:write only in binary,overwrites. if not exist then create
w+:write & read, overwrite. if not exist create
wb+:write & read in binary,overwrite. if not exist create
a:file pointr in end of fie, if not exists create
ab:opens file in append mode in binary, creates if not
a+:opens file in appnd & read,at the end of file. else create
ab+:opens file in appnd & read,at the end of file in binary. else create
'''



#file Reading
'''
print(f.read())         #f.read():read complete text char by char as list
print(f.read()[11])      #read each chrcter in every line as charcter
print(f.readlines())     #read complte by each line as a list
print(f.readlines()[1])  #read 2nd line
f.readlines() :read line by line
'''


#filepointer position 
'''
print(f.tell())  #prints current position of file pointer
f.seek(11, 0)  #f.seek(pos, optn),optn be 0,1,2: positioning pointer to begining
print(f.tell())
f.close                 #f.close()
'''


#file checking
'''
print(f.closed) #file.closed :if file closed or not(T/F)
print(f.mode)  #file.mode : retun the mode which file opened
print(f.name)  #file.name : returns the name of file.frmt
'''


