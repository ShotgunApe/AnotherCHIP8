#include "window.h"
#include <SDL3/SDL_render.h>

#define DEBUG_MSGS_HEIGHT 12
#define DEBUG_MSGS_LENGTH 20

void create_sdl_window(SDL_Window **gWindow, SDL_Renderer **gRenderer) {

    int kScale = 16;

    int kScreenWidth = 64 * kScale;
    int kScreenHeight = 32 * kScale;

    *gWindow = SDL_CreateWindow("AnotherCHIP8", kScreenWidth, kScreenHeight, 0);
    *gRenderer = SDL_CreateRenderer(*gWindow, NULL);
}

void display_debug(SDL_Renderer **gRenderer, char debug_msgs[DEBUG_MSGS_HEIGHT][DEBUG_MSGS_LENGTH]) {

    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    strncpy(debug_msgs[0], "pc 0x0000  i 0x0000", DEBUG_MSGS_LENGTH);
    strncpy(debug_msgs[2], "v0  0x00   v8  0x00", DEBUG_MSGS_LENGTH);

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(*gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(*gRenderer);  /* start with a blank canvas. */
    SDL_SetRenderDrawColor(*gRenderer, 255, 255, 255, 0x7F); /* text is slightly transparent */

    for (int i = 0; i < DEBUG_MSGS_HEIGHT; i++) {
        SDL_RenderDebugText(*gRenderer, 0, ((float) i * charsize) + 2, debug_msgs[i]);
    }
}