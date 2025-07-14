#include "chip8.h"

void initialize_emu(struct Chip8 *state, char *argv[]) {

    state->pc = 0x0200;
    state->i  = 0x0000;
    state->sp = 0x00;
    
    for (int i = 0; i < VX_REGISTERS; i++) {
        state->registers[i] = 0x00;
    }

    for (int i = 0; i < STACK_DEPTH; i++) {
        state->stack[i] = 0x00;
    }

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            state->display[i][j] = false;
        }
    }

    FILE *file;
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fread(&state->memory[0x200], 1, sizeof(state->memory) - 0x200, file);
}

uint16_t decode(struct Chip8 *state) {
    uint16_t opcode = (state->memory[state->pc] << 8) | state->memory[state->pc + 1];
    return opcode;
}

void process(struct Chip8 *state, uint16_t opcode) {

    state->pc += 2;

    switch (opcode & 0xF000) {
        case 0x0000:
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                for (int y = 0; y < SCREEN_HEIGHT; y++) {
                    state->display[x][y] = false;
                }
            }
            break;

        case 0x1000:
            state->pc = (opcode & 0x0FFF);
            break;
        
        case 0x2000:
            state->stack[state->sp] = state->pc;
            (state->sp) += 1;
            state->pc = (opcode & 0x0FFF);
            break;
        
        case 0x3000: {
            int reg = (opcode & 0x0F00) >> 8;
            if (state->registers[reg] == (opcode & 0x00FF)) {
                state->pc += 2;
            }
            break;
        }
        
        case 0x4000: {
            int reg = (opcode & 0x0F00) >> 8;
            if (state->registers[reg] != (opcode & 0x00FF)) {
                state->pc += 2;
            }
            break;
        }
        
        case 0x5000:
            break;

        case 0x6000: {
            int reg = (opcode & 0x0F00) >> 8;
            state->registers[reg] = (opcode & 0x00FF);
            break;
        }

        case 0x7000: {
            int reg = (opcode & 0x0F00) >> 8;
            state->registers[reg] += (opcode & 0x00FF);
            break;
        }

        case 0x8000:
            break;

        case 0x9000:
            break;

        case 0xA000:
            state->i = (opcode & 0x0FFF);
            break;
        
        case 0xD000: {
            int x = (state->registers[(opcode & 0x0F00) >> 8]) % 64;
            int y = (state->registers[(opcode & 0x00F0) >> 4]) % 32;
            state->registers[15] = 0x00;

            for (int i = 0; i < (opcode & 0x000F); i++) {
                uint8_t byte = state->memory[state->i + i];

                for (int j = 0; j < 8; j++) {
                    uint8_t pixel = (byte >> (7 - j)) & 1;

                    int sprite_x = (x + j) % 64;
                    int sprite_y = (y + i) % 32;

                    bool current = state->display[sprite_x][sprite_y];
                    bool new = current ^ pixel;

                    state->display[sprite_x][sprite_y] = new;

                    if (current && pixel) {
                        state->registers[15] = 1;
                    }
                }
            }
            break;
        }
    }
}