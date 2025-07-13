#include "window.h"

const char *emu_types[24] = {
    "pc", "i",
    "  ", "  ",
    "v0", "v8",
    "v1", "v9",
    "v2", "va",
    "v3", "vb",
    "v4", "vc",
    "v5", "vd",
    "v6", "ve",
    "v7", "vf",
    "  ", "  ", 
    "sp", "  "
};

void create_sdl_window(SDL_Window **gWindow, SDL_Renderer **gRenderer) {

    int kScale = 8;

    int kScreenWidth = 64 * kScale;
    int kScreenHeight = 32 * kScale;

    *gWindow = SDL_CreateWindow("AnotherCHIP8", kScreenWidth, kScreenHeight, 0);
    *gRenderer = SDL_CreateRenderer(*gWindow, NULL);
}

void display_debug(SDL_Renderer **gRenderer, char debug_msgs[DEBUG_MSGS_HEIGHT][DEBUG_MSGS_LENGTH]) {

    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;
    
    for (int i = 0; i < DEBUG_MSGS_HEIGHT; i++) {
        char tmp[DEBUG_MSGS_LENGTH];
        construct_message(tmp, i);
        strncpy(debug_msgs[i], tmp, DEBUG_MSGS_LENGTH);
    }

    SDL_SetRenderDrawColor(*gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(*gRenderer);
    SDL_SetRenderDrawColor(*gRenderer, 255, 255, 255, 0x7F); /* text is slightly transparent */

    for (int i = 0; i < DEBUG_MSGS_HEIGHT; i++) {
        SDL_RenderDebugText(*gRenderer, 0, ((float) i * charsize) + 2, debug_msgs[i]);
    }
}

void construct_message(char *line, int i) {

    const char *left = emu_types[i * 2];
    const char *right = emu_types[i * 2 + 1];

    bool blank_right = strcmp(right, "  ") == 0;

    if (strcmp(left, "pc") == 0 || strcmp(left, "sp") == 0) {
        if (blank_right) {
            snprintf(line, DEBUG_MSGS_LENGTH, "%s 0x0000", left);
        } else {
            snprintf(line, DEBUG_MSGS_LENGTH, "%s 0x0000  %s 0x0000", left, right);
        }
    }
    else if (strcmp(left, "  ") == 0) {
        snprintf(line, DEBUG_MSGS_LENGTH, "                   ");
    }
    else {
        snprintf(line, DEBUG_MSGS_LENGTH, "%s  0x00   %s  0x00", left, right);
    }
}