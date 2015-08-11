#ifndef _KEYBOARD_16_H_
#define _KEYBOARD_16_H_

#include "mbed.h"

class Keyboard16 {
public:
    Keyboard16(BusInOut *pins_row, BusInOut *pins_col);
    uint8_t read_raw();
    char read();
    int read_num();
private:
    BusInOut *row;
    BusInOut *col;
};

#endif