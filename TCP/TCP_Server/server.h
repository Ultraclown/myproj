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
#include <arpa/inet.h>
#endif

class Server
{
    private:
        int sock_ser_, sock_cli_;
        sockaddr_in addr_ser_, addr_cli_;
        
        void interact(int sock_cli, sockaddr_in addr_cli);

    public:
        Server(u_short port, const char* ip_addr);
        ~Server();
        void run();
};

void print_time();
void print_time(in_addr addr);
