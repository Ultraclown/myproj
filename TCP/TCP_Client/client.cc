#include "client.h"

using namespace std;

Client::Client(u_short port, const char* ip_addr)
{
    // 设置ip, port信息
    server_in_.sin_family = AF_INET;
    server_in_.sin_port = htons(port);
    server_in_.sin_addr.S_un.S_addr = inet_addr(ip_addr);

    // 创建套接字
    socket_client_ = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_client_ == INVALID_SOCKET)
    {
        printf(" Failed socket() \\n");
        exit(-1);
    }
}

Client::~Client()
{
    #ifdef __WIN32__
    closesocket(socket_client_);
    #else
    close(socket_client_);
    #endif
}

void Client::run()
{
    int ret;

    // 连接服务器
    if(connect(socket_client_, (sockaddr*)&server_in_, sizeof(server_in_)) == -1)
    {
        printf(" Failed connect() \\n");
        exit(-1);
    }

    // 连接成功
    print_time();
    printf("connect %s.%d\\n", inet_ntoa(server_in_.sin_addr), server_in_.sin_port);

    char recvData[200];
    char sendData[200];
    while(true)
    {
        memset(recvData, '\\0', sizeof(recvData));
        memset(sendData, '\\0', sizeof(sendData));

        // 发送消息
        printf("请发送消息： ");
        gets(sendData);
        print_time_to(server_in_.sin_addr);
        printf("发送消息：【%s】\\n", sendData);

        send(socket_client_, sendData, strlen(sendData), 0);

        if(strcmp(sendData, "quit") == 0)
        {
            break;
        }

        // 接收消息
        recvData[0] = '\\0';
        ret = recv(socket_client_, recvData, 200, 0);
        recvData[ret] = '\\0';

        print_time_from(server_in_.sin_addr);
        printf("读取消息： ");

        printf("%s\\n", recvData);

        if(strcmp(recvData, "quit") == 0)
        {
            break;
        }
    }
    
    return;
}

void print_time() {
    time_t cur_time;
    time(&cur_time);
    char* now = ctime(&cur_time);
    now[24] = '\\0';
    printf("[%s]", now);
}

void print_time_from(in_addr addr) {
    time_t cur_time;
    time(&cur_time);
    char* now = ctime(&cur_time);
    now[24] = '\\0';
    printf("[%s](From %s):", now, inet_ntoa(addr));
}

void print_time_to(in_addr addr) {
    time_t cur_time;
    time(&cur_time);
    char* now = ctime(&cur_time);
    now[24] = '\\0';
    printf("[%s](To %s):", now, inet_ntoa(addr));
}
