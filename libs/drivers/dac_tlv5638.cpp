#include "dac_tlv5638.h"

DacTLV5638::DacTLV5638(DigitalOut *cs, DigitalInOut *sclk, DigitalInOut *din) {
    this->cs = cs;
    this->sclk = sclk;
    this->din = din;
    *(this->cs) = 1;
}

void DacTLV5638::write(uint16_t data) {
    this->sclk->output();
    this->din->output();
    *(this->sclk) = 0;
    *(this->cs) = 0;
    int output_bit;
    printf("\n");
    for (int i = 15; i >= 0; i--) {
        output_bit = ((data & (1 << i)) >> i);
        *(this->din) = output_bit;
        printf("%d", output_bit);
        *(this->sclk) = 1;
        // asm("NOP");
        wait_us(1);
        *(this->sclk) = 0;
        // asm("NOP");
        wait_us(1);
    }
    *(this->sclk) = 1;
    // asm("NOP");
    wait_us(1);
    *(this->sclk) = 0;
    // asm("NOP");
    wait_us(1);
    printf("\n");
    *(this->cs) = 1;
}

void DacTLV5638::setRef(int ref_src) {
    uint16_t write_value;
    switch (ref_src) {
        case DacTLV5638::REFSRC_EXT: write_value = 0x0; break;
        case DacTLV5638::REFSRC_1024: write_value = 0x1; break;
        case DacTLV5638::REFSRC_2048: write_value = 0x2; break;
        default: return;
    }
    this->write(0xd000 + write_value);
}

void DacTLV5638::writeValue(int reg, float value) {
    if (value < 0 || value >= 1) return;
    uint16_t write_value = value * 4096;
    uint16_t base_cmd;
    switch (reg) {
        case DacTLV5638::REG_DACB_BUFFER: base_cmd = 0x4000; break;
        case DacTLV5638::REG_BUFFER: base_cmd = 0x5000; break;
        case DacTLV5638::REG_DACA_BUFFER_TO_DACB: base_cmd = 0xc000; break;
        default: return;
    }
    this->write(base_cmd + write_value);
}