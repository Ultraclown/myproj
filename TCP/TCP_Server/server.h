#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
#endif
#include <stdio.h>
#include <time.h>
#include <string.h>
#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
#define USER_ERROR -1

class Server
{
    
};

