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

class Server
{
    
};

