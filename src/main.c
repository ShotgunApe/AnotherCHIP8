#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "components/window.h"

#define DEBUG_MSGS_HEIGHT 12
#define DEBUG_MSGS_LENGTH 20
#define SCALE 8
#define FRAMERATE 60.0

int main(int argc, char **argv) {

    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    SDL_Window *gWindow = NULL;
    SDL_Renderer *gRenderer = NULL;
    SDL_Event event;
    bool render_debug_msgs = true;

    struct Chip8 emu;
    struct Chip8 *state;
    state = &emu;
    uint16_t opcode;

    unsigned int delta_a = SDL_GetTicks();
    unsigned int delta_b = SDL_GetTicks();
    double delta_time = 0;

    initialize_emu(state, argv);

    int debug_msg_size;
    char debug_msgs[DEBUG_MSGS_HEIGHT][DEBUG_MSGS_LENGTH];

    SDL_Init(SDL_INIT_VIDEO);
    create_sdl_window(&gWindow, &gRenderer);
    
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);

    bool running = true;

    while (running) {

        delta_a = SDL_GetTicks();
        delta_time = delta_a - delta_b;

        if (delta_time > 1000 / FRAMERATE) {
            opcode = decode(state);
            process(state, opcode);

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

            for (int i = 0; i < 64; i++) {
                for (int j = 0; j < 32; j++) {
                    if (state->display[i][j]) {
                        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                        SDL_FRect pixel = {
                            i * SCALE,
                            j * SCALE,
                            SCALE,
                            SCALE
                        };
                        SDL_RenderFillRect(gRenderer, &pixel);
                    }
                }
            }

            if (render_debug_msgs) {
                display_debug(state, &gRenderer, debug_msgs);
            }

            SDL_RenderPresent(gRenderer);
            delta_b = delta_a;
        }
    }

    return 0;
}