#include "server.h"

using namespace std;

Server::Server(u_short port, const char* ip_addr)
{
    // 初始化ip, port
    memset(&addr_ser_, 0, sizeof(addr_ser_));
    addr_ser_.sin_family = AF_INET;
    addr_ser_.sin_port = htons(port);
    addr_ser_.sin_addr.s_addr = inet_addr(ip_addr);

    // 建立监听套接字
    sock_ser_ = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_ser_ == -1)
    {
        printf("error:监听套接字建立失败");
        exit(-1);
    }
}

Server::~Server()
{
    #ifdef __WIN32__
    closesocket(sock_cli_);
    closesocket(sock_ser_);
    #else
    close(sock_cli_);
    close(sock_ser_);
    #endif
}

void Server::run()
{
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

    socklen_t len = sizeof(struct sockaddr_in);
    char buffer[200];
    while(true)
    {
        sock_cli_ = accept(sock_ser_, (sockaddr*)&addr_ser_, &len);
        if(sock_cli_ < 0)
        {
            printf("error:接收客户端失败");
            exit(-1);
        }
        //write(sock_cli_, buffer, sizeof(buffer));
        interact(sock_cli_, addr_cli_);
        break;
    }

    return;
}

void Server::interact(int sock_cli, sockaddr_in addr_cli)
{
    char recvData[200];
    char sendData[200];
    printf("收到一个连接\\n");

    while(true)
    {
        memset(recvData, 0, sizeof(recvData));

        // 读取消息
        int ret = recv(sock_cli, recvData, 199, 0);
        if(ret < 0)
        {
            printf("***Somethin wrong***");
            continue;
        }
        recvData[ret] = '\0';

        print_time(addr_cli.sin_addr);
        printf("读取消息： ");
        printf("%s\\n", recvData);

        if(strcmp(recvData, "quit") == 0)
        {
            break;
        }

        // 发送消息
        printf("请发送消息： ");
        //gets(sendData);
        scanf("%s", &sendData);
        print_time();
        printf("发送消息：%s", sendData);
        printf("\\n");

        send(sock_cli, sendData, 199, 0);
        
        if (strcmp("quit", sendData) == 0)
            break;
    }

    return;
}

void print_time(){
    time_t cur_time;
    time(&cur_time);
    char *now=ctime(&cur_time);
    now[24]='\0';
    printf("[%s]",now);
}
 
void print_time(in_addr addr){
    time_t cur_time;
    time(&cur_time);
    char *now=ctime(&cur_time);
    now[24]='\0';
    printf("[%s](From %s):",now,inet_ntoa(addr));
}