#include "client.h"

using namespace std;

int main()
{
    // 启动套接字编程
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock.\\n");
        return USER_ERROR;
    }

    Client client(20000, "127.0.0.1");
    client.run();
    client.~Client();

    WSACleanup();
    return 0;
}