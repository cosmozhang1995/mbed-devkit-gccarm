#include "pccomm.h"

char *readline(Serial *serial) {
    char *buffer = new char[1024];
    char ch;
    int read_cnt = 0;
    while (true) {
        while (!serial->readable()) ;
        ch = serial->getc();
        if (ch == '\n') break;
        buffer[read_cnt++] = ch;
    }
    buffer[read_cnt] = 0;
    return buffer;
}