# Client.py
# from multiprocessing import Pool
from multiprocessing.pool import ThreadPool as Pool
import socket
import time

def receiving_thread(socket):
    while True:
        msg = socket.recv(1024).decode('utf-8')
        if msg == 'exit':
            break
        if msg != '':
            print('[' + str(addr) + ']: ' + msg)
        
    socket.close()
    
def sending_thread(socket):
    while True:
        msg = input()
        s.send(msg.encode('utf-8'))
        time.sleep(1)
        if (msg == 'exit'):
            break
            
    # close the connection        
    s.close()

def run():
    # create a socket object
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

    # get local machine name
    host = socket.gethostname()                           

    port = 9999 

    # connection to hostname on the port.
    s.connect((host, port)) 
    
    pool = Pool(2)                          

    pool.apply_async(receiving_thread, (s,))
    pool.apply_async(sending_thread, (s,))
    
    while True:
        pass
                                    
if __name__ == '__main__':
    run()
else:
    pass