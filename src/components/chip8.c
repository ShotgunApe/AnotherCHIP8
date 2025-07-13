#include "chip8.h"

void decode() {

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

        case 0x6000:
            break;
    }
}