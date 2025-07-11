#include <SDL3/SDL.h>

#include "components/window.h"

int main(int argc, char **argv) {

    SDL_Window* gWindow = init_sdl_window();
    SDL_Renderer* gRenderer = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    bool running = true;

    while (running) {
        SDL_RenderClear(gRenderer);
        display_text(gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}