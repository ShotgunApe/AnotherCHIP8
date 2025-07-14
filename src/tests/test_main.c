#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#include "../components/chip8.h"

int main() {
    struct Chip8 emu;
    struct Chip8 *state;
    state = &emu;

    state->pc = 0x200;
    
    // TEST 1 - 1NNN
    process(state, 0x1FAA);
    assert(state->pc == 0x0FAA);

    process(state, 0x1A43);
    assert(state->pc == 0x0A43);

    // TEST 2 - 00E0
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            state->display[i][j] = true;
        }
    }

    process(state, 0x00E0);
    assert(state->pc == 0x0A45);

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            assert(state->display[i][j] == false);
        }
    }

    // TEST 3 - 6XNN
    process(state, 0x6A22);
    assert(state->registers[10] == 0x22);

    // TEST 4 - 7XNN
    process(state, 0x7A22);
    assert(state->registers[10] == 0x44);

    // TEST 5 - ANNN
    process(state, 0xA200);
    assert(state->i == 0x0200);

    printf("Tests Passed.\n");
    return 0;
}