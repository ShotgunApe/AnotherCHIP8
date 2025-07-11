#include <SDL3/SDL.h>

#include "components/window.h"

int main(int argc, char **argv) {

    SDL_Window* gWindow = init_sdl_window();
    SDL_Init(SDL_INIT_VIDEO);

    bool running = true;
    while (running) {
        SDL_UpdateWindowSurface( gWindow );
    }
    return 0;
}