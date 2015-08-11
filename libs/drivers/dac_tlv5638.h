#ifndef _DAC_TLV5638_H_
#define _DAC_TLV5638_H_

#include "mbed.h"

class DacTLV5638 {
public:
    static const int REFSRC_EXT = 0x0;
    static const int REFSRC_1024 = 0x1;
    static const int REFSRC_2048 = 0x2;

    static const int REG_DACB_BUFFER = 0x0;
    static const int REG_BUFFER = 0x1;
    static const int REG_DACA_BUFFER_TO_DACB = 0x2;

    DacTLV5638(DigitalOut *cs, DigitalInOut *sclk, DigitalInOut *din);
    void write(uint16_t data);
    void setRef(int ref_src);
    void writeValue(int reg, float value);
private:
    DigitalOut *cs;
    DigitalInOut *sclk;
    DigitalInOut *din;
};

#endif