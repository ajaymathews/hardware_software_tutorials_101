import _thread
import time
def test1():
    for i in range(1000,10000,1):
        print("test1:",i)
        time.sleep(1)
        
def test2():
    for j in range(1,100,1):
        print("test2:",j)
        time.sleep(1)

        
_thread.start_new_thread(test1,() )
_thread.start_new_thread(test2,() )
