#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdbool.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define VX_REGISTERS 16

// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
struct Chip8 {
    uint16_t pc;
    uint16_t i;
    uint8_t registers[VX_REGISTERS];
    bool display[SCREEN_WIDTH][SCREEN_HEIGHT];
};

void decode();
void process(struct Chip8 *state, uint16_t opcode);

#endif