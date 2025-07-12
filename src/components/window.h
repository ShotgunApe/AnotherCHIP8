#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void init_sdl_window(SDL_Window **gWindow, SDL_Renderer **gRenderer);
void display_text(SDL_Renderer **gRenderer);

#endif