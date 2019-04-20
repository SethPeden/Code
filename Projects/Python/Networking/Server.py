# Server.py
# from multiprocessing import Pool
from multiprocessing.pool import ThreadPool as Pool
import time
import socket

def receiving_thread(client_socket, addr):
    while True:
        msg = client_socket.recv(1024).decode('utf-8')
        if msg == 'exit':
            break
        if msg != '':
            print('[' + str(addr) + ']: ' + msg)
        
    client_socket.close()

def sending_thread(client_socket, addr):
    while True:
        msg = input()
        client_socket.send(msg.encode('utf-8'))
        time.sleep(1)
        if (msg == 'exit'):
            break   
        
    # close the connection        
    client_socket.close()

def run():
    # create a socket object
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
            
    # get local machine name
    host = socket.gethostname()                           

    port = 9999

    # bind to the port
    server_socket.bind((host, port))                                  

    # queue up to 10 requests
    queue_limit = 10;
    server_socket.listen(queue_limit)                                           
    # your "parallelness"
    pool = Pool(queue_limit)

    while True:
        # accept a connection
        client_socket, addr = server_socket.accept()
        pool.apply_async(receiving_thread, (client_socket, addr,))
        pool.apply_async(sending_thread, (client_socket, addr,))

if __name__ == '__main__':
    run()
else:
    pass