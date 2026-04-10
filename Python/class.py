class student:#creating a class,with name and roll_no as arguemnts
    def __init__(self,name,roll_no):#defining an initialization to receieve name,roll_no
        self.name=name
        self.roll_no=roll_no

ajay=student("ajy",3)#in this ajay is the object created with name'ajy' and roll no'3'
kk=student("iii",10)
print(ajay.roll_no)
print(kk.name)
