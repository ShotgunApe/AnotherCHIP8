#include <SDL3/SDL.h>
#include <stdlib.h>
#include <string.h>

#include "components/window.h"

#define DEBUG_MSGS_HEIGHT 12
#define DEBUG_MSGS_LENGTH 20

int main(int argc, char **argv) {

    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Event event;
    bool render_debug_msgs = true;

    int debug_msg_size;
    char debug_msgs[DEBUG_MSGS_HEIGHT][DEBUG_MSGS_LENGTH];

    SDL_Init(SDL_INIT_VIDEO);
    create_sdl_window(&gWindow, &gRenderer);

    bool running = true;

    while (running) {

        while (SDL_PollEvent(&event) != 0 ) {
		    switch (event.type) {
                case SDL_EVENT_KEY_DOWN:
                    render_debug_msgs = !render_debug_msgs;
                    break;
			    case SDL_EVENT_QUIT:
			    	running = false;
			    	break;
		    }
	    }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(gRenderer);
        
        if (render_debug_msgs) {
            display_debug(&gRenderer, debug_msgs);
        }
        
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}