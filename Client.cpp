#include "Client.h"
#include "vusocket.h"
#include <string>

const char *IP_ADDRESS = "52.58.97.202";
const int PORT = 5382;
const char *PORT_STR = "5382";
#define DEFAULT_BUFLEN 4096
struct sockaddr_in address;

void Client::tick() {
    while (stdinBuffer.hasLine()) {
        std::string message = stdinBuffer.readLine();
        message+= "\n";
        std::cout << "sent: "  << message << std::endl;
        int iResult = send(sock, message.c_str(), message.size(), 0);
        if (iResult == SOCKET_ERROR) {
            wprintf(L"send failed with error: %d\n", WSAGetLastError());
        }
    }

    while (socketBuffer.hasLine()) {
        std::cout << "Received: " << socketBuffer.readLine() << std::endl;
    }
};

int Client::readFromStdin() {
    std::string input;
    std::getline(std::cin, input);
    if (input.size() == 0) {
        return 0;
    }

    if (input == "!exit") {
        return -1;
    } else if (input == "!quit") {
        this->stopApplication();
        return 0;
    } else if (input == "!who") {
        input = "WHO";
    } else if (input[0] == '@') {
        input = input.substr(1, input.size());
        input = "SEND " + input;
    }

    input += '\n';
    stdinBuffer.writeChars(input.c_str(), input.size());
    return input.size();
};

int Client::readFromSocket() {
    std::string recvbuf;
    recvbuf.resize(DEFAULT_BUFLEN);
    int numbytes = recv(sock, &recvbuf.at(0), DEFAULT_BUFLEN, 0);

    if (recvbuf.find("IN-USE") == 0) {
        createSocketAndLogIn();

        std::cout << "Please choose another name: " << std::endl;
        return 0;
    }
    if (numbytes > 0) {
        socketBuffer.writeChars(recvbuf.c_str(), numbytes);
    } else if (numbytes < 0) {
        wprintf(L"recv failed with error: %d\n", WSAGetLastError());
    }
    return numbytes;
};

void Client::createSocket() {
    sock_init();

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int iResult;

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

void Client::createSocketAndLogIn() {
    createSocket();
}

void Client::closeSocket() {
    int iResult;
    iResult = closesocket(sock);

    if (iResult == SOCKET_ERROR) {
        wprintf(L"closesocket failed with error = %d\n", WSAGetLastError());
    }

    WSACleanup();
};