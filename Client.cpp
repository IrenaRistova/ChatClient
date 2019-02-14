#include "Client.h"
#include <string>

const std::string ip_adress = "52.58.97.202";
const std::string port = "5378";

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
    addrinfo AddrInfo;
    AddrInfo.ai_family = AF_INET;
    AddrInfo.ai_socktype = SOCK_STREAM;
    // objAddrInfo.ai_addr = ;
    int getaddrinfo(const char ip_adress, const char port,
                    const struct addrinfo *hints, struct addrinfo **res);
};

void Client::closeSocket(){};