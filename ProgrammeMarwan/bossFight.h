#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TAILLE_MAP_MAX 20

#ifndef BOSS_H
#define BOSS_H

#ifndef MOVE_H
#define MOVE_H

#include "move.h"
#include "outil.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define speed 30

typedef struct boss_s{
    int id;
    char nom[TAILLE_MAP_MAX];
    char texture[TAILLE_MAP_MAX];
    int degats;
    int armure;
    int regen;
    int as;
    int pv;
    int mana;
}boss_t;

boss_t boss[] = {
    {0,"","",0,0,0,0,0,0},
    {1,"Gabil'baraz","",1,2,0.5,30},
    {2,"Bund'zigl","",2,4,2,20},
    {3,"Uzn'gor","",1,},
    {4,"Ayoub, le nain dechu","",0,0,0,0}
};














extern void deplacementSerpent(SDL_Window *window);

#endif 
#endif