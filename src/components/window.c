#include "window.h"

SDL_Window* init_sdl_window() {
    SDL_Window *gWindow = NULL;

    const int kScreenWidth = 640;
    const int kScreenHeight = 480;

    gWindow = SDL_CreateWindow("AnotherCHIP8", kScreenWidth, kScreenHeight, 0);
    return gWindow;
}

void display_text(SDL_Renderer *gRenderer) {

    const int charsize = SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE;

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* black, full alpha */
    SDL_RenderClear(gRenderer);  /* start with a blank canvas. */

    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */
    SDL_RenderDebugText(gRenderer, 272, 100, "Hello world!");
    SDL_RenderDebugText(gRenderer, 224, 150, "This is some debug text.");

    SDL_SetRenderDrawColor(gRenderer, 51, 102, 255, SDL_ALPHA_OPAQUE);  /* light blue, full alpha */
    SDL_RenderDebugText(gRenderer, 184, 200, "You can do it in different colors.");
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);  /* white, full alpha */
}