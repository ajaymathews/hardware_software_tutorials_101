import socket
import _thread
import time
import pickle#using pickle we can pass any type of information through socket

HEADER_SIZE=5
st_msg="Welcome to Server"



def trans_pickle():
    st_msg=input(":")
    st_msg=f'{len(st_msg):< {HEADER_SIZE}}'+st_msg #will allocate 5 space to display msg length(0-99999) and prints msg length alongside msg
                                       #f'{ }' is similar to str(), but :< works in f'{ }' only as far asd i know
                                       #(:< prints on left, :> prints on right, :^ prints on center
    snd_byt=pickle.dumps(st_msg)
    conn.send(snd_byt)



def close():
    conn.close()                   #i think only the server can close the connection to its client



s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)#actually it is (IPV4,TCP)
s.bind((socket.gethostname(),1234))#we need to bind to a (ip,port)tuple, since we are using local host, acquire local host name/ip
                                   #socket is the end point of tranmsiter and reciever in this communication
s.listen(5)                        #listen to only 5 devices
conn,address = s.accept()          #connect to any ip and store the connected ip to address
print("Connected to client:",address[0])

#conn.send(bytes("Welcome to Server","utf-8"))#sending the data as bytes client

while 1:
    trans_pickle()
    
    



'''    _thread.start_new_thread(trans,() )
       _thread.start_new_thread(recv,() )        '''    
    
      
    

    

