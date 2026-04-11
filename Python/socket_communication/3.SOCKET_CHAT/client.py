import socket
import select
import errno #t find the specified error
import sys

IP=socket.gethostname()
PORT=1234
HEADER_SIZE=5
u_name=input("Username:")
u_name=u_name.encode("utf-8")

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((IP,PORT))
s.setblocking(False)

u_header=f"{len(u_name):<{HEADER_SIZE}}".encode("utf=8")
s.send(u_header+u_name)

while 1:
   
    msg=input(f"{u_name}:")
    if(msg):#if something is inputed, then msg value > 0
        msg=msg.encode("utf-8")
        msg_header=f"{len(msg):<{HEADER_SIZE}}".encode("utf=8")
        s.send(msg_header+msg)
    try:
        while 1:#recieve things from server, that includer broadcast msg from other users also
            #we recv from header is usr_header&data and msg_header&data
            usr_header=s.recv(HEADER_SIZE)
            if not len(usr_header):#if we didnt get any data
                print("connection closed by the server")
                sys.exit()
            usr_len=int(usr_header.decode("utf-8"))
            usr_name=s.recv(usr_len).decode("utf-8")#now we got the user name , next is msg
    
            mesg_header=s.recv(HEADER_SIZE)
            mesg_len=int(mesg_header.decode("utf-8"))
            mesg=s.recv(mesg_len).decode("utf-8")
                    
            print(f"{usr_name}:{mesg}")

    except IOError as e:
        if e.errno != errno.EAGAIN and e.errno != errno.EWOULDBLOCK:
            print("reading error",str(e))
            sys.exit()
        continue

    except Exception as e:
        print("General Error")
        sys.exit()

                         
        
