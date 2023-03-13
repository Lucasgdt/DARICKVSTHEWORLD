#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "environnement.h"

#ifndef MOVE_H
#define MOVE_H


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


#define speed 30



typedef struct coord_s{
    int up;
    int down;
    int left;
    int right;
}coord_t;


int move(coord_t dir, SDL_Rect * destRect, int map[TILES_X][TILES_Y]) ;


#endif