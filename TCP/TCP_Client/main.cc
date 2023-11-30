#include "client.h"

using namespace std;

int main()
{
    // 启动套接字编程
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load Winsock.\\n");
        exit(-1);
    }

    Client client(20000, "116.62.6.98");
    client.run();
    client.~Client();

    WSACleanup();
    return 0;
}