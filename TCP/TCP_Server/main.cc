#include "server.h"

using namespace std;

int main()
{
    Server server(20000, "0.0.0.0");
    server.run();
    server.~Server();

    return 0;
}