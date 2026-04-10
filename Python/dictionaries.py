#a dictionary can only one key,no keys with same name is allowed,
#but can have same value to different keys 

dic={1:"one" , "two":2 , 3:3} #key and value pair can be same value
                              #and of different types, 
dic.update({3:5})   #if same key with diffrnt value cms, it replaces

dic.update({input("key:") : input("value:")} ) #insert value by key:value method
##dic.update('six'=6) #insert value by key=value method

dic.update("key-name")=input("value");



print(dic)
