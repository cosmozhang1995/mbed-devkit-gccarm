#include "lcd_lcm12864r.h"

LcdLCM12864R::LcdLCM12864R(BusInOut *data_pins, DigitalOut *rs, DigitalOut *rw, DigitalOut *en, DigitalOut *rst) {
    this->data = data_pins;
    this->rs = rs;
    this->rw = rw;
    this->en = en;
    this->rst = rst;
    this->_expand_command = false;
    this->_pos_x = 0;
    this->_pos_y = 0;
    this->_printing_word = false;
    this->_clean = false;
}

void LcdLCM12864R::setMode(bool rs, bool rw) {
    if (rs) *(this->rs) = 1;
    else *(this->rs) = 0;
    if (rw) *(this->rw) = 1;
    else *(this->rw) = 0;
}

void LcdLCM12864R::setMode(int rs, int rw) {
    *(this->rs) = rs;
    *(this->rw) = rw;
}

void LcdLCM12864R::enable() {
    *(this->en) = 1;
}

void LcdLCM12864R::disable() {
    *(this->en) = 0;
}

void LcdLCM12864R::write(int data) {
    this->data->output();
    *(this->data) = data;
}

int LcdLCM12864R::read() {
    this->data->input();
    return (int)(*(this->data));
}

void LcdLCM12864R::reset() {
    *(this->rst) = 0;
    wait_ms(30);
    *(this->rst) = 1;
    wait_ms(30);
}

bool LcdLCM12864R::checkStatus() {
    this->disable();
    this->setMode(0, 1);
    this->write(0xff);
    this->enable();
    bool status = ((this->read() & 0x80) == 0x80);
    this->disable();
    this->setMode(1, 0);
    return status;
}

void LcdLCM12864R::waitStatus() {
    while (this->checkStatus());
}

void LcdLCM12864R::writeCommand(int cmd) {
    this->waitStatus();
    this->write(cmd);
    this->setMode(0, 0);
    this->enable();
    this->disable();
}

void LcdLCM12864R::writeData(int data) {
    this->waitStatus();
    this->write(data);
    this->setMode(1, 0);
    this->enable();
    this->disable();
}

int LcdLCM12864R::readData() {
    this->waitStatus();
    this->setMode(1, 1);
    this->enable();
    int data = this->read();
    this->disable();
    return data;
}

void LcdLCM12864R::initialize() {
    this->reset();
    this->expandCommand(false);
    this->turnDisplay(false);
    this->clearDisplay();
    this->writeCommand(0x06);
    this->turnDisplay(true);
}

void LcdLCM12864R::expandCommand(bool expand) {
    if (expand) {
        if (!this->_expand_command) {
            this->writeCommand(0x34);
            this->_expand_command = true;
        }
    } else {
        if (this->_expand_command) {
            this->writeCommand(0x30);
            this->_expand_command = false;
        }
    }
}

void LcdLCM12864R::clearDisplay() {
    this->writeCommand(0x1);
    this->_clean = true;
}

void LcdLCM12864R::turnDisplay(bool on) {
    if (on) this->writeCommand(0x0c);
    else this->writeCommand(0x08);
}

void LcdLCM12864R::startAt(int pos_x, int pos_y) {
    printf("start at: %d, %d\n", pos_x, pos_y);
    if ((pos_x < 0) || (pos_x > 7)) return;
    if ((pos_y < 0) || (pos_y > 3)) return;
    int row_base_addr = 0;
    switch (pos_y) {
        case 0: row_base_addr=0x80;break;
        case 1: row_base_addr=0x90;break;
        case 2: row_base_addr=0x88;break;
        case 3: row_base_addr=0x98;break;
        default: return;
    }
    this->writeCommand(row_base_addr + pos_x);
    this->_pos_x = pos_x * 2;
    this->_pos_y = pos_y;
}

void LcdLCM12864R::putChar(char ch) {
    this->_clean = false;
    this->writeData(ch);
    if (this->_pos_x >= 15) {
        if (this->_pos_y < 3) this->startAt(0, this->_pos_y + 1);
        else this->startAt(0, 0);
    } else {
        this->_pos_x ++;
    }
}

void LcdLCM12864R::printString(char *str) {
    char ch;
    while ((!((this->_pos_y == 0) && (this->_pos_x == 0))) || (this->_clean)) {
        printf("pos: x = %02d, y = %01d     ", this->_pos_x, this->_pos_y);
        ch = *(str++);
        printf("0x%02x - %c\n", (int)ch, ch);
        if (this->_printing_word) {
            this->putChar(ch);
            this->_printing_word = false;
            continue;
        }
        if (ch == 0) break;
        if ((ch & 0x80) == 0x80) {
            this->putChar(ch);
            this->_printing_word = true;
            continue;
        }
        if (ch == '\n') {
            if (this->_pos_y < 3) {
                this->startAt(0, this->_pos_y + 1);
                continue;
            } else break;
        }
        this->putChar(ch);
    }
}