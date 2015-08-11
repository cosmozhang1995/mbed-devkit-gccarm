#include "keyboard_16.h"

Keyboard16::Keyboard16(BusInOut *pins_row, BusInOut *pins_col) {
    this->row = pins_row;
    this->col = pins_col;
}

uint8_t Keyboard16::read_raw() {
    uint8_t read_col, write_row;
    this->row->output();
    this->col->input();
    this->col->mode(PullDown);
    write_row = 1;
    for (int i = 0; i < 4; i++) {
        *(this->row) = write_row;
        wait_ms(1);
        read_col = *(this->col);
        if (read_col != 0) return (write_row << 4) + read_col;
        write_row = write_row << 1;
    }
    return 0;
}

char Keyboard16::read() {
    uint8_t raw_data = this->read_raw();
    switch (raw_data) {
        case 0x11: return 'D';
        case 0x12: return '#';
        case 0x14: return '0';
        case 0x18: return '*';
        case 0x21: return 'C';
        case 0x22: return '9';
        case 0x24: return '8';
        case 0x28: return '7';
        case 0x41: return 'B';
        case 0x42: return '6';
        case 0x44: return '5';
        case 0x48: return '4';
        case 0x81: return 'A';
        case 0x82: return '3';
        case 0x84: return '2';
        case 0x88: return '1';
        default: return 0;
    }
}

int Keyboard16::read_num() {
    char ch = this->read();
    if (ch < '0' || ch > '9') return -1;
    else return ch - '0';
}