#include <SDL3/SDL.h>

#include "components/window.h"

int main(int argc, char **argv) {

    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    init_sdl_window(&gWindow, &gRenderer);

    bool running = true;

    while (running) {
        while (SDL_PollEvent(&event) != 0 ) {
		    switch (event.type) {
			    case SDL_EVENT_QUIT:
			    	running = false;
			    	break;
		    }
	    }
        
        SDL_RenderClear(gRenderer);
        display_text(&gRenderer);
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}