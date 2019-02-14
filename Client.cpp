#include "Client.h"
#include <string>

const std::string IP_ADDRESS = "52.58.97.202";
const std::string PORT = "5378";

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
    //TODO
    addrinfo objAddrInfo;
    objAddrInfo.ai_family = AF_INET;
    objAddrInfo.ai_socktype = SOCK_STREAM;
    // objAddrInfo.ai_addr = ;
    int getaddrinfo(const char IP_ADDRESS, const char PORT,
                    const struct addrinfo *hints, struct addrinfo **res);
};

void Client::closeSocket(){};