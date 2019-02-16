#include "Client.h"
#include <string>

const std::string IP_ADDRESS = "52.58.97.202";
const std::string PORT = "5378";
// std::string result = " ";
void Client::tick(){};

int Client::readFromStdin()
{
    return 0;
};

int Client::readFromSocket()
{
    return 0;
};

void Client::createSocketAndLogIn()
{

    addrinfo AddrInfo;
    AddrInfo.ai_family = AF_INET;
    AddrInfo.ai_socktype = SOCK_STREAM;
    AddrInfo.ai_protocol = IPPROTO_TCP;
    // AddrInfo.ai_addr = result;

    int getaddrinfo(const char IP_ADDRESS, const char PORT,
                    const struct addrinfo AddrInfo, struct addrinfo **res);
};

void Client::closeSocket(){};