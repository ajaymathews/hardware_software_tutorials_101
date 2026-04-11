import pickle
import  socket
import select #DONT KNOW YET

IP=socket.gethostname()
PORT=1234
HEADER_SIZE=5

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)#allow us to reconnect
s.bind((IP,PORT))
s.listen()                          #make it as the server and wait for the client to accpt connection

sock_list = [s]                     #sockets list contains sockts,now server only
client = {}                         #dictonary socket as key and userdata as value

def srv_rec_msg(c):                 #here c is the conn variabe, tht can send and recv data
    try:
        msg_hdr=c.recv(HEADER_SIZE) #recives the lengh of the msg from header
        if not len(msg_hdr):        #check if the length is zero, then return from functn
            return False
        msg_lng=int(msg_hdr.decode("utf-8"))
        return {"header": msg_hdr, "data":c.recv(msg_lng)}#recieves data as per the header size, and return recived data as a dictonary
            
    except:
        print("client closed connctn")#mostly happens in case if client close connection.
        return False
    
while 1:
    read_sock,_,excpt_sock = select.select(sock_list, [], sock_list)

    for noti_sock in read_sock:     #if comming client request is in read_conn then 2 chances
        if(noti_sock == s):         #this means someone just connected and we need to accpt it
            c_conn,c_addr = s.accept()
            usr=srv_rec_msg(c_conn) #now the usr contains the data from current connected client data
            if usr is False:        #if they disconnected
                continue
            sock_list.append(c_conn)#othrwise add them to our sock list
            client[c_conn]=usr      #if im corrrect, the client contains the dataabase of the usr dictonary with c_conn as position
            print(f"Accepted Connection IP:{c_addr[0]} PORT:{c_addr[1]} USR:{usr['data'].decode('utf-8')}")
        else:                       #if the client is already in the connection
            msg=srv_rec_msg(noti_sock)#recieves the new msg from already connected client into messages
            if msg is False:         #in case the client is disconnected from the connection
               print(f"closed connection from {client[noti_sock]['data'].decode('utf-8')}")
               sock_list.remove(noti_sock)
               del client[noti_sock]
               continue
            usr=client[noti_sock]  #if client is already in, then fetch the client details from client{} as the position is the conn
            print(f"Message from {usr['data'].decode('utf-8')}:{msg['data'].decode('utf-8')}")

            for c_conn in client: #sending the recieved msg to all the clients in client{}
                if c_conn != noti_sock: #but not sending to the sender itself
                    c_conn.send(usr['header']+usr['data']+msg['header']+msg['data'])

    for noti_sock in excpt_sock:
        sock_list.remove(noti_sock)
        del clients[noti_sock]
