#include "vusocket.h"
#include "Server.h"
#include <string>

void Server::createSocket()
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
};

//
//// Resolve the server address and port

//
//// Create a SOCKET for connecting to server
//ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//if (ListenSocket == INVALID_SOCKET) {
//printf("socket failed with error: %ld\n", WSAGetLastError());
//freeaddrinfo(result);
//WSACleanup();
//return 1;
//}
//
//// Setup the TCP listening socket
//iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
//if (iResult == SOCKET_ERROR) {
//printf("bind failed with error: %d\n", WSAGetLastError());
//freeaddrinfo(result);
//closesocket(ListenSocket);
//WSACleanup();
//return 1;
//}
//
//freeaddrinfo(result);
//
//iResult = listen(ListenSocket, SOMAXCONN);
//if (iResult == SOCKET_ERROR) {
//printf("listen failed with error: %d\n", WSAGetLastError());
//closesocket(ListenSocket);
//WSACleanup();
//return 1;
//}
//
//// Accept a client socket
//ClientSocket = accept(ListenSocket, NULL, NULL);
//if (ClientSocket == INVALID_SOCKET) {
//printf("accept failed with error: %d\n", WSAGetLastError());
//closesocket(ListenSocket);
//WSACleanup();
//return 1;
//}
//
//// No longer need server socket
//closesocket(ListenSocket);
//
//// Receive until the peer shuts down the connection
//do {
//
//iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
//if (iResult > 0) {
//printf("Bytes received: %d\n", iResult);
//
//// Echo the buffer back to the sender
//iSendResult = send( ClientSocket, recvbuf, iResult, 0 );
//if (iSendResult == SOCKET_ERROR) {
//printf("send failed with error: %d\n", WSAGetLastError());
//closesocket(ClientSocket);
//WSACleanup();
//return 1;
//}
//printf("Bytes sent: %d\n", iSendResult);
//}
//else if (iResult == 0)
//printf("Connection closing...\n");
//else  {
//printf("recv failed with error: %d\n", WSAGetLastError());
//closesocket(ClientSocket);
//WSACleanup();
//return 1;
//}
//
//} while (iResult > 0);
//
//// shutdown the connection since we're done
//iResult = shutdown(ClientSocket, SD_SEND);
//if (iResult == SOCKET_ERROR) {
//printf("shutdown failed with error: %d\n", WSAGetLastError());
//closesocket(ClientSocket);
//WSACleanup();
//return 1;
//}
//
//// cleanup
//closesocket(ClientSocket);
//WSACleanup();
//
//

//#include "Server.h"
///** Sets the needed info
// *  @param port to listen on
// */
//Server::Server(int setport) {
//    mPort = setport;
//}
///** Starts the server
// */
//void Server::Start() {
//    mSocket = socket(AF_INET, SOCK_STREAM, 0);
//    cout << "Socket succesfully started." << endl;
//    if (setsockopt(mSocket, SOL_SOCKET, SO_REUSEADDR, &mTrue, sizeof(int)) < 0) {
//        cout << "ERROR" << endl;
//    }
//    server.sin_family = AF_INET;
//    server.sin_port = htons(mPort);
//    server.sin_addr.s_addr = INADDR_ANY;
//    mSize = sizeof(server);
//    if(bind(mSocket, (struct sockaddr*)(&server), mSize) < 0) {
//        cout << "ERROR" << endl;
//    }
//    cout << "Starting server on port " << mPort << endl;
//    cout << "LIVE" << endl;
//}
///** Listens to the incoming packets
// */
//void Server::Listen() {
//    listen(mSocket, 5);
//    cout << "Listening." << endl;
//    while(1) {
//        const int size = 512;
//        char buffer[size+1];
//        int status = 0;
//        mConnection = accept(mSocket, (struct sockaddr*)(&client), &mSize);
//        mConnectionPool.push_back(mConnection);
//        cout << "Handling connection " << mConnection << endl;
//
//        for (int i = 0; i < mConnectionPool.size(); i++) {
//            cout << mConnectionPool[i] << endl;
//            cout << mConnectionPool.size() << endl;
//            int flags = fcntl(mConnectionPool[i], F_GETFL, 0);
//            fcntl(mConnectionPool[i], F_SETFL, flags | O_NONBLOCK);
//            do {
//                status = read(mConnectionPool[i], buffer, size);
//                cout << status << endl;
//                if(status == 0) {
//                    mConnectionPool.erase(mConnectionPool.begin() + i);
//                    cout << "Connection " << mConnectionPool[i] << " was erased, reason: disconnection." << endl;
//
//                } else {
//
//                    buffer[size] = '\0';
//                    cout << "Msg Recv'd:" << buffer << endl;
//                    send(mConnectionPool[i], buffer, strlen(buffer), 0);
//                    cout << "Wrote to Client: " << buffer << endl << "With the size of: " << strlen(buffer) << endl;
//                }
//            } while(status != -1);
//        }
//    }
//}
///** Handles character packets
// *  @param Handle the desired character packet
// */
//void Server::HandleCharPackets(char* packet) {
//}
///** Handles integer packets
// *  @param Handle the desired integer packet
// */
//void Server::HandleIntPackets(int packet) {
//
//}