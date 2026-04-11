import socket
import _thread
import time
import pickle

HEADER_SIZE=5
new_msg=True
full_msg=" "
msg_length=0

def trans():
    ct_msg=input()
    s.send(bytes(ct_msg,"utf-8"))       #converting the string to bytes inorder to transmit
def recv():
    cr_msg=s.recv(1024)
    msg_length=int(cr_msg[:HEADER_SIZE])#this will get the first 5 bytes ffrom msg, which inturns is the length of the message
    cr_msg=cr_msg[HEADER_SIZE:]         #this will capture only the message after the space allocted for header length 
    full_msg=cr_msg.decode("utf-8")     #this is the message to decode the message recieved in bytes to string
    if(len(full_msg)!=msg_length):
       print("some datas are lost")
    print('server:',full_msg)           #recieving the msg in bytes and decode to char


def close():
    s.close()

   
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)#actually it is (IPV4,TCP)
s.connect((socket.gethostname(),1234))   #connect to the server ip, in this to local host ip

while 1:
    recv()

    
    


'''    _thread.start_new_thread(trans,() )
       _thread.start_new_thread(recv,() )        '''
    








