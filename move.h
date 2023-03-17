#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "environnement.h"

#ifndef MOVE_H
#define MOVE_H


#define speed 30



typedef struct coord_s{
    int up;
    int down;
    int left;
    int right;
}coord_t;



int move(coord_t dir, SDL_Rect * destRect, Tile_t ** Map_Rect) ;


#endif