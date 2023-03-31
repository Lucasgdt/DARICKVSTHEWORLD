#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>

#ifndef FIGHT_H
#define FIGHT_H

void fight(SDL_Renderer* renderer, SDL_Texture* characterTexture, SDL_Rect destRect, MOUSE_COORD mouse, coord_t dir);

#endif