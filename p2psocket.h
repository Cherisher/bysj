#ifndef __P2PSOCKET_H__
#define __P2PSOCKET_H__
typedef enum
{
    SOCKET_STATUS_INVALID = -1,
    SOCKET_STATUS_CLOSED = 0,
    SOCKET_STATUS_LISTENING,
    SOCKET_STATUS_CONNETTING,
    SOCKET_STATUS_CONNECTED,
}SOCKET_STATUS;

class p2pSocket{
public:
    p2pSocket();
    ~p2pSocket();
    
    int Create(int SocketType = SOCK_STREAM);
    int CreateClient(const char* serv_addr, int port, int SocketType = SOCK_STREAM, const char* my_addr = NULL );

    int CreateServer(int port, int SocketType = SOCK_STREAM, const char* my_addr);

    int Accept(p2pSocket &connectedSocket);
    int Bind(u_short SocketPort, const char* SocketAddress = NULL);
    int Bind(const sockaddr* SockAddr, int SockAddrLen);

    int Connect(const char* ServerAddress, int port);
    int Connect(sockaddr* ServerAddr, int ServerAddrLen);


    virtual int Send(const void* Buffer, int BufferLen, int Flags = 0);
    int SendTo(const void* Buffer, int BufferLen, const sockadd* SockAddr, int SockAddrLen, int Flags = 0);

    int Recv(void* Buffer, int BufferLen, int Flags = 0);
    int RecvFrom(void *Buffer, int BufferLen, string& SocketAddress, u_short& SocketPort, int Flags = 0);
    int Close();
    int Listen(int ConnectingBacklog = SOMAXCONN);

    int ShutDown(int how);


    int GetPeerName(string& PeerAddr, u_short& PeerPort);
    int GetPeerName(sockaddr* SockAddr, int* SockAddrLen);
    int GetSockName(string& SocketAddress, u_short& SocketPort);
    int GetSockName(sockaddr* SockAddr, int *SockAddrLen);

    int GetSockOpt(int Level, int OptName, void* OptVal, int* OptLen);
    int SetSockOpt(int Level, int OptName, const void* OptVal, int* OptLen);

    SOCKET GetSocket();
    int GetEvent();
    int GetStatus();
    int SetEvent(int Event);
    int setStatus(int Status);
    int HandleEvent(int Event);



private: 
    int Attach(SOCKET Socket, int Status, int Event);
    int m_Status;
    int m_Event;
    SOCKET m_Socket;

};


#endif  // __P2PSOCKET_H__
