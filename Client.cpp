#include "Client.h"
#include "vusocket.h"
#include <string>
//is a data structure tha*-t uses a single, fixed-size buffer as if it were connected end-to-end
const char *IP_ADDRESS = "52.58.97.202";
const int PORT = 5378;
const char *PORT_STR = "5378";
#define DEFAULT_BUFLEN 4096
//This method is called after you have successfully logged in using 'createSocketAndLogIn'
//     * It is called repeatedly (see main.cpp), which means you don't need a loop in this method.
void Client::tick() {
    if (stdinBuffer.hasLine()) {
        std::string message = stdinBuffer.readLine();
        message+= '\n';
        std::cout << "sent: "  << message << std::endl;
        send(sock, message.c_str(), message.size(), 0);
    }
//These buffers allow you to read in a character stream(stdinBuffer), and read out complete lines(socketBuffer)
// 1. Check for user input by polling 'stdinBuffer'. If it contains a line, read it and process it.
//  2. Check for data sent by the server by polling 'socketBuffer'. If it contains a line,
//   read it and show it to the user.
    if (socketBuffer.hasLine()) {
        std::cout << "Received: " << socketBuffer.readLine() << std::endl;
    }
};
//If there is a line in the socket buffer, you received something from the server and might need to display it to the user.
// If there is a line in the standard input buffer the user has typed something into the console and your program should respond correctly.


//This method reads data from the standard input and writes it into the 'stdinBuffer'.
//     * This method is called repeatedly, which means you don't need to add a loop yourself.
//@return Returns -1 if the user writes '!exit', returns the number of characters read otherwise.
int Client::readFromStdin() {
    std::string input;
    std::getline(std::cin, input);
    if (input.size() == 0) {
        return 0;
    }

    if (input == "!exit" || "!quit") {
        return -1;
    } else if (input == "!quit") {
        this->stopApplication();
        return 0;
    } else if (input == "!who") {
        input = "WHO";
    } else if (input[0] == '@') {
        input = input.substr(1, input.size()); //starts from the first(skips) till the end
        input = "SEND " + input;
    }

    input += '\n';
    stdinBuffer.writeChars(input.c_str(), input.size());
    return input.size();
};
//This method reads data from 'sock' and writes it into 'socketBuffer'.
//* This method is called repeatedly, which means you don't need to add a loop yourself.
//     * #return Return the return value of 'recv'.
int Client::readFromSocket() {
    std::string recvbuf;
    recvbuf.resize(DEFAULT_BUFLEN); //its lenght is being set to the size of the buffer 4000smth
    int numbytes = recv(sock, &recvbuf.at(0), DEFAULT_BUFLEN, 0);
    //If no error occurs, recv returns the number of bytes received and the buffer pointed to by the buf parameter will contain this data received(&recvbuf.at(0))
    if (numbytes > 0) {
        socketBuffer.writeChars(recvbuf.c_str(), numbytes); //?
    } else if (numbytes < 0) {
        wprintf(L"recv failed with error: %d\n", WSAGetLastError());
    }
    return numbytes;
};

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