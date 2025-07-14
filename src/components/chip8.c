#include "chip8.h"

void initialize_emu(struct Chip8 *state, char *argv[]) {

    state->pc = 0x0200;
    state->i  = 0x0000;
    
    for (int i = 0; i < VX_REGISTERS; i++) {
        state->registers[i] = 0x00;
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

    fread(state->memory, 1, sizeof(state->memory), file);
}

uint16_t decode(struct Chip8 *state) {
    return 0x200;
}

void process(struct Chip8 *state, uint16_t opcode) {

    state->pc += 2;

    switch (opcode & 0xF000) {
        case 0x0000:
            for (int i = 0; i < SCREEN_WIDTH; i++) {
                for (int j = 0; j < SCREEN_HEIGHT; j++) {
                    state->display[i][j] = false;
                }
            }
            break;

        case 0x1000:
            state->pc = (opcode & 0x0FFF);
            break;
        
        case 0x2000:
            break;
        
        case 0x3000:
            break;
        
        case 0x4000:
            break;
        
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
            int x = state->registers[(opcode & 0x0F00)] >> 8 % 64;
            int y = state->registers[(opcode & 0x00F0)] >> 4 % 32;
            state->registers[15] = 0x00;


            break;
        }
    }
}