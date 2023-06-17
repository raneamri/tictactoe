#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "main.hpp"
#include "globals.hpp"
#include "defs.hpp"
#include "types.hpp"

SDL_Window *window;
SDL_Renderer *renderer;

Cursor cursor;
int mouseX, mouseY;