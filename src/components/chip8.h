#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32
#define VX_REGISTERS 16
#define STACK_DEPTH 16
#define WRITABLE_MEM 4096

// http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
struct Chip8 {
    uint16_t pc;
    uint16_t i;
    uint8_t  sp;
    uint8_t  registers[VX_REGISTERS];
    uint16_t stack[STACK_DEPTH];
    unsigned char memory[WRITABLE_MEM];
    bool display[SCREEN_WIDTH][SCREEN_HEIGHT];
};

void initialize_emu(struct Chip8 *state, char *argv[]);
uint16_t decode(struct Chip8 *state);
void process(struct Chip8 *state, uint16_t opcode);

#endif