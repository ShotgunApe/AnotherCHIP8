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
    process(state, 0xAA00);
    assert(state->i == 0x0A00);

    // TEST 6 - 2NNN
    state->pc = 0x0200;
    process(state, 0x2120);
    assert(state->sp == 0x01);
    assert(state->stack[0] == 0x0202);
    assert(state->pc == 0x0120);

    // TEST 7 - 3XKK
    state->pc = 0x0200;
    state->registers[1] = 0xFF;
    process(state, 0x31FF);
    assert(state->pc == 0x0204);

    // TEST 8 - 4XKK
    state->pc = 0x0200;
    state->registers[1] = 0xFF;
    process(state, 0x41FF);
    assert(state->pc == 0x0202);

    // TEST 9 - 5XY0
    state->pc = 0x0200;
    state->registers[1] = 0xAF;
    state->registers[2] = 0xAF;
    process(state, 0x5120);
    assert(state->pc == 0x0204);

    // TEST 10 - 00EE
    state->pc = 0x0200;
    process(state, 0x2300);
    process(state, 0x00EE);
    assert(state->pc == 0x0202);

    // TEST 11 - 8XY0
    state->pc = 0x0200;
    state->registers[1] = 0x22;
    process(state, 0x8210);
    assert(state->registers[1] == state->registers[2]);

    // TEST 12 - 8XY1
    state->pc = 0x0200;
    state->registers[1] = 0x22;
    state->registers[2] = 0x00;
    process(state, 0x8211);
    assert(state->registers[2] == (0x00 | 0x22));

    // TEST 13 - 8XY2
    state->pc = 0x0200;
    state->registers[1] = 0x22;
    state->registers[2] = 0x01;
    process(state, 0x8212);
    assert(state->registers[2] == (0x01 & 0x22));

    // TEST 14 - 8XY3
    state->pc = 0x0200;
    state->registers[1] = 0x22;
    state->registers[2] = 0x01;
    process(state, 0x8213);
    assert(state->registers[2] == (0x01 ^ 0x22));

    // TEST 15 - 8XY4 - (VF Flag set)
    state->pc = 0x0200;
    state->registers[1] = 0xA2;
    state->registers[2] = 0xD7;
    state->registers[15] = 0x00;
    process(state, 0x8214);
    uint8_t res = 0xA2 + 0xD7;
    assert(state->registers[2] == res);
    assert(state->registers[15] == 1);

    // TEST 16 - 8XY5
    state->pc = 0x0200;
    state->registers[1] = 0xA2;
    state->registers[2] = 0xD7;
    state->registers[15] = 0x00;
    process(state, 0x8215);
    res = 0xD7 - 0xA2;
    assert(state->registers[2] == res);
    assert(state->registers[15] == 1);

    // TEST 17 - 8XY6
    state->pc = 0x0200;
    state->registers[1] = 0x88;
    state->registers[2] = 0x23;
    state->registers[15] = 0x00;
    process(state, 0x8216);
    res = 0x23 / 0x02;
    assert(state->registers[2] == res);
    assert(state->registers[15] == 1);

    // TEST 18 - 8XY7
    state->pc = 0x0200;
    state->registers[1] = 0xA2;
    state->registers[2] = 0xD7;
    state->registers[15] = 0x00;
    process(state, 0x8217);
    res = 0xA2 - 0xD7;
    assert(state->registers[2] == res);
    assert(state->registers[15] == 0);

    // TEST 19 - 8XYE
    state->pc = 0x0200;
    state->registers[1] = 0x88;
    state->registers[2] = 0x93;
    state->registers[15] = 0x00;
    process(state, 0x821E);
    res = 0x93 * 0x02;
    assert(state->registers[2] == res);
    assert(state->registers[15] == 1);

    printf("Tests Passed.\n");
    return 0;
}