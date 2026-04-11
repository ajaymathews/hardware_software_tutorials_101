import socket
import _thread
import time
import pickle

HEADER_SIZE=5
new_msg=True
full_msg=" "
msg_length=0


def recv_pickle():
    rec_byt=s.recv(1024)
    cr_msg=pickle.loads(rec_byt)
    msg_length=int(cr_msg[:HEADER_SIZE])#this will get the first 5 bytes ffrom msg, which inturns is the length of the message
    full_msg=cr_msg[HEADER_SIZE:]         #this will capture only the message after the space allocted for header length 
    if(len(full_msg)!=msg_length):
       print("some datas are lost")
    print('server:',full_msg)           #recieving the msg in bytes and decode to char



def close():
    s.close()

   
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)#actually it is (IPV4,TCP)
s.connect((socket.gethostname(),1234))   #connect to the server ip, in this to local host ip

while 1:
    recv_pickle()

    








