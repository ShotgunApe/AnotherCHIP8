#ifndef CHIP8_H
#define CHIP8_H

struct Chip8 {
    int pc;
    int i;
    int registers[16];
};

#endif