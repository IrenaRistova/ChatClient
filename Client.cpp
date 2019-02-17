#include "Client.h"
#include "vusocket.h"
#include <string>

const char *IP_ADDRESS = "52.58.97.202";
const int PORT = 5378;
const char *PORT_STR = "5378";
const char *name = "Serghei";
#define DEFAULT_BUFLEN 512

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
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0)
    {
        printf("WSAStartup failed with error: %d\n", err);
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
    {
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");

    int iResult;

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    address.sin_port = htons(PORT);

    if (sock == INVALID_SOCKET)
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
    else
    {
        wprintf(L"socket function succeeded\n");

        iResult = connect(sock, (SOCKADDR *)&address, sizeof(address));

        if (iResult == SOCKET_ERROR)
        {
            wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
            iResult = closesocket(sock);
            if (iResult == SOCKET_ERROR)
                wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        }

        wprintf(L"Connected to server.\n");
    }

    int recvbuflen = DEFAULT_BUFLEN;
    char *sendbuf = "HELLO-FROM Serghei \n ";
    char recvbuf[DEFAULT_BUFLEN] = "";

    //----------------------
    // Send an initial buffer
    iResult = send(sock, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR)
    {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closeSocket();
    }

    printf("Bytes Sent: %d\n", iResult);
    std::cout << sendbuf << std::endl;

    iResult = recv(sock, recvbuf, recvbuflen, 0);
    if (iResult > 0)
    {
        wprintf(L"Bytes received: %d\n", iResult);
        std::cout << recvbuf << std::endl;
    }
    else if (iResult == 0)
        wprintf(L"Connection closed\n");
    else
        wprintf(L"recv failed with error: %d\n", WSAGetLastError());
};

void Client::closeSocket()
{
    std::cout << "outro" << std::endl;
    int iResult;
    iResult = closesocket(sock);
    if (iResult == SOCKET_ERROR)
    {
        wprintf(L"closesocket failed with error = %d\n", WSAGetLastError());
    }

    WSACleanup();
};