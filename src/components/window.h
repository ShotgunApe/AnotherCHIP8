#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window* init_sdl_window();
void display_text(SDL_Renderer *gRenderer);

#endif