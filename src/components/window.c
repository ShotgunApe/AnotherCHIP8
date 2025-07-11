#include "window.h"

SDL_Window* init_sdl_window() {
    SDL_Window *gWindow = NULL;
    const int kScreenWidth = 640;
    const int kScreenHeight = 480;

    gWindow = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3!", kScreenWidth, kScreenHeight, 0);

    return gWindow;
}