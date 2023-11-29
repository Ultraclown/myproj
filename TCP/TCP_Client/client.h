#include <stdio.h>
#include <time.h>
#include <string.h>
#include <string>
#ifdef __WIN32__
# include <winsock2.h>
#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
#else
# include <sys/socket.h>
#endif

class Client
{
    private:
        SOCKET socket_client_;
        sockaddr_in server_in_;

    public:
        Client(int port, const char* ip_addr);
        ~Client();
        int run();
};

void print_time();
void print_time_from(in_addr addr);
void print_time_to(in_addr addr);