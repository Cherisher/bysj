from socket import *
from time import ctime

HOST=''
PORT=8000
BUFSIZ=1024
ADDR=(HOST,PORT)
def openServ():
    tcpSerSock = socket(AF_INET,SOCK_STREAM)
    tcpSerSock.bind(ADDR)
    tcpSerSock.listen(5)
    while True:
        print 'Wating for connection...'
        tcpCliSock,addr=tcpSerSock.accept()
        print '...connected from: ',addr
        while True:
            data = tcpCliSock.recv(BUFSIZ)
            if not data:
                break
            #  print data
            tcpCliSock.send('[%s]%s'%(ctime(), data))
        tcpCliSock.close()
    tcpSerSock.close()

if __name__ =="__main__":
    openServ()

