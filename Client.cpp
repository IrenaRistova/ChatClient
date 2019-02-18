#include "Client.h"
#include "vusocket.h"
#include <string>

const char *IP_ADDRESS = "52.58.97.202";
const int PORT = 5378;
const char *PORT_STR = "5378";
#define DEFAULT_BUFLEN 512

void Client::tick() {
    std::string command;
    std::cin >> command;

    if (command == "!quit") {
        this->stopApplication();
    } else if (command == "!who") {
        this->who();
    } else if (command[0] == '@') {
        std::string username = command.substr(1,username.size());
        std::string messageText;
        std::cin >> messageText;
        message(username, messageText);
    } else if (command == "!delivery") {
        delivery();
    }
};

int Client::readFromStdin() {
    return 0;
};

int Client::readFromSocket() {
    return 0;
};

void Client::sendReq(std::string sendbuf) {
    int iResult;
    iResult = send(sock, sendbuf.c_str(), sendbuf.size(), 0);
    if (iResult == SOCKET_ERROR) {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closeSocket();
    }

    printf("Bytes Sent: %d\n", iResult);
    std::cout << sendbuf << std::endl;
}

int Client::receive(std::string &recvbuf) {
    int iResult;
    iResult = recv(sock, &recvbuf.at(0), DEFAULT_BUFLEN, 0);

    if (iResult > 0) {
        wprintf(L"Bytes received: %d\n", iResult);
        std::cout << recvbuf << std::endl;
    } else if (iResult == 0)
        wprintf(L"Connection closed\n");
    else
        wprintf(L"recv failed with error: %d\n", WSAGetLastError());

    return iResult;
}

void Client::createSocket() {
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        printf("Could not find a usable version of Winsock.dll\n");
        WSACleanup();
    } else
        printf("The Winsock 2.2 dll was found okay\n");

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    int iResult;

    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    address.sin_port = htons(PORT);

    if (sock == INVALID_SOCKET)
        wprintf(L"socket function failed with error = %d\n", WSAGetLastError());
    else {
        wprintf(L"socket function succeeded\n");

        iResult = connect(sock, (SOCKADDR *) &address, sizeof(address));

        if (iResult == SOCKET_ERROR) {
            wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
            iResult = closesocket(sock);
            if (iResult == SOCKET_ERROR)
                wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
        }

        wprintf(L"Connected to server.\n");
    }
}

void Client::logIn(std::string name) {
    std::cout << "Trying to log in" << std::endl;

    std::string request = "HELLO-FROM ";
    int iResult;
    std::string recvbuf;
    recvbuf.resize(DEFAULT_BUFLEN);

    sendReq(request + name + "\n");
    receive(recvbuf);

    if (recvbuf.find("HELLO Serghei") < recvbuf.size()) {
        std::cout << "Hand-shake ok" << std::endl;
    } else if (recvbuf.find("IN-USE") < recvbuf.size()) {
        std::cout << "Name taken" << std::endl;
        name += '0';
        logIn(name);
        return;
    } else if (recvbuf.find("BUSY") < recvbuf.size()) {
        std::cout << "Server busy" << std::endl;
        logIn(name);
        return;
    }
}


void Client::createSocketAndLogIn() {
    name = "Serghei1";
    createSocket();
    logIn(name);
};

void Client::who() {
    int iResult;
    std::string recvbuf;
    recvbuf.resize(DEFAULT_BUFLEN);

    sendReq("WHO\n");
    receive(recvbuf);
}

void Client::message(std::string user, std::string message) {
    std::string recvbuf;
    recvbuf.resize(DEFAULT_BUFLEN);

    sendReq("SEND "+user+" "+name+": "+message+"\n");
    receive(recvbuf);
}

void Client::delivery() {
    std::string recvbuf;
    recvbuf.resize(DEFAULT_BUFLEN);
    receive(recvbuf);
}

void Client::closeSocket() {
    int iResult;
    iResult = closesocket(sock);

    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error = %d\n", WSAGetLastError());
    }

    WSACleanup();
};