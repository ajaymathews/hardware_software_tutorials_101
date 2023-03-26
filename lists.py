#list data assignment and printing
emp_list=[]             #creating an empty list

lists=list(range(6,20,3))
print("adding numbrs to new list using range() :",lists)

lists=['a',9,6,"hello",[10,20,30]] #list can store any type of data as elemnts
print("New list:",lists)            #prints complete lists
print("selcting a letter from a string,which is an elmnt:",lists[3][3])      #prints 'l' from hello
print("selcting num from a list:",lists[4][2])      #prints 30

print("used to print list: ",end="")
for i in lists:
    print(i,end=" ")
print()





#-A string is list of characters





#Num of elemnts in list
print("length of current list:",len(lists))      #prints no of elemnts in a list





#Checking elemnt in list:
print("if a in lists:",'a' in lists)    #to check an elemnt present in list or not prints True
print("if 20 in lists:",20 in lists)     #doesnt identify list inside a list, prints false
print("if 5 not in lists:",5 not in lists)  #to check number is not present or not

print("finding postn of 6 in list:",lists.index(6))





#list elemnt insertion
lists.append("mine")  #list_name.apppend is used to add another elemnt
print("list after appended string,",lists)           #to the list to its end

lists.insert(4,"world")#used to add an elemnt to the given position in a list , 4 is the position
print("inserted string to 4th pos,",lists)












