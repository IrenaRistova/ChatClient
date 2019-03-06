////
//// Created by User on 19-Feb-19.
////
//
#ifndef SERVER_H
#define SERVER_H

#endif SERVER_H

#ifdef _WIN32
#else
#include <pthread.h>

#endif

#include <thread>
#include <string.h>
#include "Application.h"
#include "vusocket.h"
#include "CircularLineBuffer.h"


class Server  {
private:
    SOCKET sock;
    std::string name;
    std::thread socketThread, stdinThread;
    CircularLineBuffer socketBuffer, stdinBuffer;


public:
    Server(int);
//    int server;
    void createSocket();


};

//#ifndef _SERVER_H
//#define	_SERVER_H
//
//#include "vusocket.h"
//
//#include <iostream>
//#include <string>
//#include <vector>
//#include <string.h>
//#include <cstdlib>
////#include <sys/ioctl.h>
//#include <sys/types.h>
////#include <sys/socket.h>
////#include <arpa/inet.h>
////#include <netinet/in.h>
////#include <netdb.h>
//#include <fcntl.h>
//
//
//class Server {
//public:
//    Server(int);
//    void Start();
//    void Listen();
//    void HandleCharPackets(char*);
//    void HandleIntPackets(int);
//private:
//
//    struct sockaddr_in server, client;
//    int mPort;
//    int mSocket;
//    int mTrue;
//    int mConnection;
//    socklen_t mSize;
////    vector<int> mConnectionPool;
//};
//#endif	/* _SERVER_H */
