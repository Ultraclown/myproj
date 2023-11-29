#include "server.h"

using namespace std;

Server::Server(int port, const char* ip_addr)
{
    // 初始化ip, port
    memset(&addr_ser_, 0, sizeof(addr_ser_));
    addr_ser_.sin_family = AF_INET;
    addr_ser_.sin_port = htons(port);
    addr_ser_.sin_addr.s_addr = inet_addr(ip_addr);
}

void Server::run()
{
    // 建立监听套接字
    sock_ser_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_ser_ == -1)
    {
        printf("error:监听套接字建立失败");
        exit(-1);
    }
    
    // 套接字绑定ip, port
    if(bind(sock_ser_, (sockaddr*)&addr_ser_, sizeof(addr_ser_)) == -1)
    {
        printf("error:监听套接字绑定失败");
        exit(-1);
    }

    // 监听客户端连接
    if(listen(sock_ser_, 3) == -1)
    {
        printf("error:监听套接字监听失败");
        exit(-1);
    }

    int len = sizeof(struct sockaddr_in);
    char buffer[] = "hello world";
    while(true)
    {
        sock_cli_ = accept(sock_ser_, (sockaddr*)&addr_ser_, &len);
        if(sock_cli_ < 0)
        {
            printf("error:接收客户端失败");
            exit(-1);
        }
        write(sock_cli_, buffer, sizeof(buffer));
    }
    close(sock_cli_);
    close(sock_ser_);
}
