#function defnition
'''
def add(x, y):
    return x + y        
def twice(op, a, b):
    return op(op(a, b), op(a, b)) #we can add the function name as the parameter
                                  #the return function is the addition of 2 function
print(twice(add,2,8))

'''

#standard functions

#random
'''
import random
print("random value:",random.randint(1,100))
'''


#time
'''
import time
data=time.localtime()
#print(data)#time.struct_time(tm_year=2019, tm_mon=12, tm_mday=21,
           #tm_hour=11, tm_min=31, tm_sec=29, tm_wday=5, tm_yday=355,
           #tm_isdst=0)
print("TIME:"+str(data[3])+":"+str(data[4])+":"+str(data[5]))
print("DATE:"+str(data[2])+"/"+str(data[1])+"/"+str(data[0]))
'''

#math
'''
from math import pi
from math import pi,sqrt   #importing a var and a function only
print(pi)
'''

