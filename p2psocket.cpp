#include"p2psocket.h"


p2pSocket::p2pSocket()
{
    m_Status = SOCKET_STATUS_INVALID;
}

p2pSocket::~p2pSocket()
{
    m_Status = SOCKET_STATUS_INVALID;
    // SocketManger::DelSocketToPool(*this);
}

int p2pSocket::Create(int SocketType)
{
    if(SOCK_STREAM != SocketType && SOCK_DGRAM != SocketType)
        return -1;
    m_Socket = socket(AF_INET, SocketType, SOCK_STREAM == SocketType?IPPROTO_TCP:IPPRPTP_UDP);
    int flags = 1;

// SocketManger::AddSocketToPool(*this);
    return 0;
}

int p2pSocket::CreateClinet(const char* server_addr, int port, int SocketType, const char* my_addr)
{
    Create(SocketType);
    if(SOCK_STREAM == SocketType)
    {
        Connect(serv_addr, port);
    }
    return 0;
}

int p2pSocket::CreateServer(int port, int SocketType, const char* my_addr)
{
    Create(SocketType);
    Bind(port);
    if(SOCK_STREAM == SocketType ==  SocketType)
    {
        Listen();
    }
    return 0;
}


SOCKET p2pSocket::GetSocket()
{
    return m_Socket;
}

int p2pSocket::GetEvent()
{
    return m_Event;
}

int p2pSocket::GetStatus()
{
    return m_Status;
}

int p2pSocket::SetEvent(int Event)
{
    m_Event = Event;
}

int p2pSocket::SetStatus(int Status)
{
    m_Status = Status;
}

int p2pSocket::HandleEvent(int Event)
{
    printf("Socket: %x Event: %d ", m_Socket, Event);
    switch(Event)
    {
        case 0x1:
            printf("\t SOCKET_EVENT_READ");
            break;
        case 0x2:
            printf("\t SOCKET_EVENT_WRITE");
            break;
        case 0x4:
            printf("\t SOCKET_EVENT_ERROR");
            break;
        case 0x8:
            printf("\t SOCKET_EVENT_00B");
            break;
        default:
    }
    printf("\n");
}

