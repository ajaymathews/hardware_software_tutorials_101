from pickle import *
f=open("client_data","rb")
db=load(f)
f.close()
print(db)

