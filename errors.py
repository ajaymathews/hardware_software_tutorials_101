#error avoid
'''
try:
  {code that cause error}
except:
  {code to execute if that happens}
'''

#errors 
'''
ImportError: an import fails;
IndexError: a list is indexed with an out-of-range number;
NameError: an unknown variable is used;
SyntaxError: the code can't be parsed properly; 
TypeError: a function is called on a value of an inappropriate type;
ValueError: a function is called on a value of the correct type, but with an inappropriate value
'''

#test
'''
try:
    print("No error found")
    
except:
    print("Error is executed")
'''


#raise error
'''
for i in range(10):
    print(i)
    raise ValueError #in pgm will generate that error and stops execution,can apply with any error.
'''
'''
for i in range(10):
    print(i)
    assert (i<5)#assert condition #condition output=> F: stops execution, T: continue
'''



