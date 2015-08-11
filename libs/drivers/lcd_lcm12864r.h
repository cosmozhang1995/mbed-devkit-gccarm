#ifndef _LCD_LCM12864R_H_
#define _LCD_LCM12864R_H_

#include "mbed.h"

class LcdLCM12864R {
public:
    LcdLCM12864R(BusInOut *data_pins, DigitalOut *rs, DigitalOut *rw, DigitalOut *en, DigitalOut *rst);
    void setMode(bool rs, bool rw);
    void setMode(int rs, int rw);
    void enable();
    void disable();
    void write(int data);
    int read();
    void reset();
    
    bool checkStatus();  // true if status is busy
    void waitStatus();
    
    void writeCommand(int cmd);
    void writeData(int data);
    int readData();
    
    void initialize();
    void expandCommand(bool expand);
    
    void clearDisplay();
    void turnDisplay(bool on);
    void startAt(int pos_x, int pos_y);
    void putChar(char ch);
    void printString(char *str);
private:
    BusInOut *data;
    DigitalOut *rs;
    DigitalOut *rw;
    DigitalOut *en;
    DigitalOut *rst;
    bool _expand_command;
    int _pos_x;
    int _pos_y;
    bool _printing_word;
    bool _clean;
};

#endif