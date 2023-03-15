#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>

#ifndef MOVE_H
#define MOVE_H


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define DARICK_SIZE 96

#define speed 30



typedef struct coord_s{
    int up;
    int down;
    int left;
    int right;
}coord_t;


int move(coord_t dir, SDL_Rect * destRect) ;


#endif