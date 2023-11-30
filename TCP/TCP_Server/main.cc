#include "server.h"

using namespace std;

int main()
{
    Server server(20000, "116.62.6.98");
    server.run();
    server.~Server();

    return 0;
}