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

    public:
        Server(int port, const char* ip_addr);
        void run();
        ~Server();
};

