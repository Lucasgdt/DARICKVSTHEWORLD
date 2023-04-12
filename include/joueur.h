#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "personnage.h"
#include "mapstruct.h"
#include "mob.h"
#include "action.h"
#ifndef JOUEUR_H
#define JOUEUR_H

#define DARICK_SIZE 96
#define FPS 24
typedef struct MOUSE_COORD_S{
    int x;
    int y;
}MOUSE_COORD;

int joueur(SDL_Window *window, int * nbsalle, int * kill);
int ecran_fin(SDL_Window * window, int * nbsalle, int * kill);

#endif