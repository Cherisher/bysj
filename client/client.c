#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
    struct sockaddr_in addr;
    char buffer[256];
    int tcpCliSock;
    if((tcpCliSock = socket(AF_INET,SOCK_STREAM,0))< 0)
    {
        perror("socket");
        exit(-1);
    }
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(tcpCliSock,(struct sockaddr*)&addr, sizeof(addr))<0)
    {
        perror("connect");
        exit(-1);
    }
    while(1)
    {
        memset(buffer,'\0', sizeof(buffer));
        //scanf("%s", buffer);
        gets(buffer);
        if(strlen(buffer) == 0)
            break;
        send(tcpCliSock,buffer,strlen(buffer),0);
        memset(buffer, '\0', sizeof(buffer));
        recv(tcpCliSock, buffer, 256,0);
        if(strlen(buffer)== 0)
            break;
        printf("%s\n", buffer);
    }
    close(tcpCliSock);
    return 0;
}
