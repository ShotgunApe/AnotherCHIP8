#include "chip8.h"
#include "font.h"

void initialize_emu(struct Chip8 *state, char *argv[]) {

    state->pc = 0x0200;
    state->i  = 0x0000;
    state->sp = state->dt = state->st = 0x00;
    
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

    for (int i = 0; i < 80; i++) {
        state->memory[i] = font[i];
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
        case 0x0000: {
            if ((opcode & 0x00FF) == 0x00EE) {
                state->sp -= 1;
                state->pc = state->stack[state->sp];
            }
            else {
                for (int x = 0; x < SCREEN_WIDTH; x++) {
                    for (int y = 0; y < SCREEN_HEIGHT; y++) {
                        state->display[x][y] = false;
                    }
                }
            }
            break;
        }

        case 0x1000: {
            state->pc = (opcode & 0x0FFF);
            break;
        }
        
        case 0x2000: {
            state->stack[state->sp] = state->pc;
            state->sp += 1;
            state->pc = (opcode & 0x0FFF);
            break;
        }
        
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
        
        case 0x5000: {
            int reg_x = (opcode & 0x0F00) >> 8;
            int reg_y = (opcode & 0x00F0) >> 4;
            if (state->registers[reg_x] == state->registers[reg_y]) {
                state->pc += 2;
            }
            break;
        }

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

        case 0x8000: {
            int reg_x = (opcode & 0x0F00) >> 8;
            int reg_y = (opcode & 0x00F0) >> 4;
            
            switch (opcode & 0x000F) {
                case 0x0000: {
                    state->registers[reg_x] = state->registers[reg_y];
                    break;
                }
                case 0x0001: {
                    state->registers[reg_x] = (state->registers[reg_x] | state->registers[reg_y]);
                    break;
                }
                case 0x0002: {
                    state->registers[reg_x] = (state->registers[reg_x] & state->registers[reg_y]);
                    break;
                }
                case 0x0003: {
                    state->registers[reg_x] = (state->registers[reg_x] ^ state->registers[reg_y]);
                    break;
                }
                case 0x0004: {
                    uint16_t tmp = (state->registers[reg_x] + state->registers[reg_y]);
                    state->registers[reg_x] = tmp;
                    // Set VF Flag if carry
                    if (state->registers[reg_x] != tmp) {
                        state->registers[15] = 1;
                    }
                    else {
                        state->registers[15] = 0;
                    }
                    break;
                }
                case 0x0005: {
                    if (state->registers[reg_x] > state->registers[reg_y]) {
                        state->registers[15] = 1;
                    }
                    else {
                        state->registers[15] = 0;
                    }
                    state->registers[reg_x] = state->registers[reg_x] - state->registers[reg_y];
                    break;
                }
                case 0x0006: {
                    if ((state->registers[reg_x] % 2) == 1) {
                        state->registers[15] = 1;
                    }
                    else {
                        state->registers[15] = 0;
                    }
                    state->registers[reg_x] = (state->registers[reg_x] / 2);
                    break;
                }
                case 0x0007: {
                    if (state->registers[reg_y] > state->registers[reg_x]) {
                        state->registers[15] = 1;
                    }
                    else {
                        state->registers[15] = 0;
                    }
                    state->registers[reg_x] = state->registers[reg_y] - state->registers[reg_x];
                    break;
                }
                case 0x000E: {
                    if (((state->registers[reg_x] >> 4) % 2) == 1) {
                        state->registers[15] = 1;
                    }
                    else {
                        state->registers[15] = 0;
                    }
                    state->registers[reg_x] = (state->registers[reg_x] * 2);
                    break;
                }
            }
            break;
        }

        case 0x9000: {
            int reg_x = (opcode & 0x0F00) >> 8;
            int reg_y = (opcode & 0x00F0) >> 4;

            if (state->registers[reg_x] != state->registers[reg_y]) {
                state->pc += 2;
            }
            break;
        }

        case 0xA000: {
            state->i = (opcode & 0x0FFF);
            break;
        }
        
        case 0xB000: {
            state->pc = (opcode & 0x0FFF) + state->registers[0];
            break;
        }

        case 0xC000: {
            int reg_x = (opcode & 0x0F00) >> 8;
            state->registers[reg_x] = rand() & (opcode & 0x00FF);
            break;
        }

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

        case 0xE000: {
            // TODO: Figure out input
            int reg_x = (opcode & 0x0F00) >> 8;

            if ((opcode & 0x00FF) == 0x009E) {
                if (state->ib == state->registers[reg_x]) {
                    state->pc += 2;
                }
            }
            else {
                if (state->ib != state->registers[reg_x]) {
                    state->pc += 2;
                }
            }
            break;
        }
        case 0xF000: {
            int reg_x = (opcode & 0x0F00) >> 8;
            switch (opcode & 0x00FF) {
                case 0x0007: {
                    state->registers[reg_x] = state->dt;
                    break;
                }
                case 0x000A: {
                    // Waits for input, stay on opcode if no input
                    if (state->ib == 0)  {
                        state->pc -= 2;
                    }
                    break;
                }
                case 0x0015: {
                    state->dt = state->registers[reg_x];
                    break;
                }
                case 0x0018: {
                    state->st = state->registers[reg_x];
                    break;
                }
                case 0x001E: {
                    state->i = state->i + state->registers[reg_x];
                    break;
                }
                case 0x0029: {
                    state->i = state->memory[state->registers[reg_x] * 5];
                    break;
                }
                case 0x0033: {
                    break;
                }
                case 0x0055: {
                    for (int i = 0; i < reg_x; i++) {
                        state->memory[state->i + (i * 4)] = state->registers[i];
                    }
                    break;
                }
                case 0x0065: {
                    for (int i = 0; i < reg_x; i++) {
                        state->registers[i] = state->memory[state->i + (i * 4)];
                    }
                    break;
                }
            }
        }
    }
    if (state->dt > 0) {
        state->dt -= 1;
    }
    if (state->st > 0) {
        state->st -= 1;
    }
}