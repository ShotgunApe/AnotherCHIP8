#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_render.h>

#include "chip8.h"

#define DEBUG_MSGS_HEIGHT 12
#define DEBUG_MSGS_LENGTH 20

extern const char *emu_types[24];

void create_sdl_window(SDL_Window **gWindow, SDL_Renderer **gRenderer);
void display_debug(struct Chip8 *state, SDL_Renderer **gRenderer, char debug_msgs[DEBUG_MSGS_HEIGHT][DEBUG_MSGS_LENGTH]);
void construct_message(struct Chip8 *state, char line[DEBUG_MSGS_LENGTH], int i);

#endif