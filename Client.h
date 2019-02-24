//
// Created by Jesse on 2019-01-09.
//

#ifndef CPP_CHAT_CLIENT_CLIENT_H
#define CPP_CHAT_CLIENT_CLIENT_H

#ifdef _WIN32
#else
#include <pthread.h>
#endif

#include <thread>
#include <string.h>
#include "Application.h"
#include "vusocket.h"
#include "CircularLineBuffer.h"

class Client : public Application {
private:
    /**
     * You are free to add new member variables and methods here if needed.
     * Please do not remove the ones that are already here.
     */
    SOCKET sock;
    std::string name;
    std::thread socketThread, stdinThread;
    CircularLineBuffer socketBuffer, stdinBuffer;

    /**
     * Assignment 2
     *
     * See the lab manual for the assignment description.
     */
    void tick() override;

    /**
 * Assignment 4
 *
 * This method reads data from the standard input and writes it into the 'stdinBuffer'.
 * This method is called repeatedly, which means you don't need to add a loop yourself.
 * After implementation, it should look something like this:
 *
 * std::string input = [read string from stdin];
 * stdinBuffer.writeChars([change string to char array], [number of elements]);
 *
 * Make sure that you also write newline (\n) characters into the stdinBuffer,
 * otherwise stdinBuffer.readLine() will never return a line.
 *
 * See the lab manual for more details.
 *
 * @return Returns -1 if the user writes '!exit', returns the number of characters read otherwise.
 */
    int readFromStdin();

    /**
     * Assignment 4
     *
     * This method reads data from 'sock' and writes it into 'socketBuffer'.
     * This method is called repeatedly, which means you don't need to add a loop yourself.
     * After implementation, it should look something like this:
     *
     * int numbytes = recv([socket], [buffer], [buffer size], 0);
     * socketBuffer.writeChars([buffer], numbytes);
     *
     * See the lab manual for more details.
     *
     * #return Return the return value of 'recv'.
     */
    int readFromSocket();

    inline void threadReadFromStdin() {
        while (!isStopped()) {
            auto res = readFromStdin();
            if (res < 0) {
                stopApplication();
            }
        }
    }

    inline void threadReadFromSocket() {
        while (!isStopped()) {
            auto res = readFromSocket();
            if (res < 0) {
                stopApplication();
            }
        }
    }

    void createSocket();

    void logIn(std::string name);

    void createSocketAndLogIn();

    void closeSocket();

    inline void startThreads() {
        socketThread = std::thread(&Client::threadReadFromSocket, this);
        stdinThread = std::thread(&Client::threadReadFromStdin, this);
    }

    inline void stopThreads() {
        this->stopApplication();
        socketThread.join();
        stdinThread.join();
    }

public:
    inline ~Client() override {
        closeSocket();
        stopThreads();
    }

    /**
     * Assignment 1
     *
     * See the lab manual for the assignment description.
     */
    inline void setup() override {
        createSocketAndLogIn();
        startThreads();
    }
};


#endif //CPP_CHAT_CLIENT_CLIENT_H
