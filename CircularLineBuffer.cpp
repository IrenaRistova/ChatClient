//
// Created by Gebruiker on 22/02/2019.
//

#include "CircularLineBuffer.h"
bool CircularLineBuffer::_writeChars(const char *chars, size_t nchars) {
    if (nchars > freeSpace() || nchars == 0) {
        return false;
    }

    int begin = nextFreeIndex();
    for (int i = 0; i < nchars; i++) {
        buffer[(begin+i)%bufferSize] = chars[i];
    }

    count += nchars;
    return true;
}

std::string CircularLineBuffer::_readLine() {
    if (hasLine()) {
        std::string result;
        int end = findNewline();

        result.resize(abs(end-start));

        for (int i = 0; i < abs(end-start); i++) {
            result[i] = buffer[(start+i)%bufferSize];
//            std::cout << buffer[(start+i)%bufferSize] << std::endl;
        }


        count -= end+1-start;
        start = end+1;
        return result;
    } else {
        return "";
    }
}

int CircularLineBuffer::findNewline() {
    int i = 0;
    while (buffer[(i+start)%bufferSize] != '\n') {
        i++;
        if (i >= count) {
            return -1;
        }
    }

    return start+i;
}

bool CircularLineBuffer::hasLine() {
    return findNewline() >= 0;
}

