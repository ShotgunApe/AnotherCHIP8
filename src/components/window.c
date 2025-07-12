#include "window.h"
#include <SDL3/SDL_render.h>

void init_sdl_window(SDL_Window **gWindow, SDL_Renderer **gRenderer) {

    const int kScreenWidth = 640;
    const int kScreenHeight = 480;

    *gWindow = SDL_CreateWindow("AnotherCHIP8", kScreenWidth, kScreenHeight, 0);
    *gRenderer = SDL_CreateRenderer(*gWindow, NULL);
}

void display_text(SDL_Renderer **gRenderer) {

    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(*gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(*gRenderer);  /* start with a blank canvas. */

    SDL_SetRenderDrawColor(*gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */
    SDL_RenderDebugText(*gRenderer, 272, 100, "Hello world!");
    SDL_RenderDebugText(*gRenderer, 224, 150, "This is some debug text.");
}