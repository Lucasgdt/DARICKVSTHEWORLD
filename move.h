#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mapstruct.h"

#ifndef MOVE_H
#define MOVE_H


#define speed 1



Sprite* InitialiserSprite(Sint16 x,Sint16 y,Sint16 w,Sint16 h, Map_t* map);
void LibereSprite(Sprite* sp);
void AfficherSprite(Sprite* perso,SDL_Renderer* renderer, SDL_Texture * skin);
int CollisionDecor(Sprite* perso, SDL_Rect test);
int EssaiDeplacement(Sprite* perso,int vx,int vy);
void Affine(Sprite* perso,int vx,int vy);
int DeplaceSprite(Sprite* perso,int vx, int vy);


#endif