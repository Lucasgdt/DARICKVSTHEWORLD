#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mapstruct.h"
#include "mob.h"
#ifndef MOVE_H
#define MOVE_H

#define AGGRO_DISTANCE 300 // distance d'aggro en pixels
#define speed 2



Sprite* InitialiserSprite(int x,int y,int w,int h, Map_t* map);
void LibereSprite(Sprite* sp);
void AfficherSprite(Sprite* perso,SDL_Renderer* renderer, SDL_Texture * skin);
int CollisionDecor(Sprite* perso, SDL_Rect test);
int EssaiDeplacement(Sprite* perso,int vx,int vy);
void Affine(Sprite* perso,int vx,int vy);
int DeplaceSprite(Sprite* perso,int vx, int vy);
void init_mob(Map_t * map, SDL_Renderer * renderer, mob_liste_t * mob_liste, Sprite * mob_sdl[TAILLE_LISTE_MOB]);
void deplacement_mobV2(Sprite * mob[TAILLE_LISTE_MOB], int i);
void free_mob_sdl(Sprite * mob_sdl[TAILLE_LISTE_MOB]);
int fonction_calcul(SDL_Rect destRect, Sprite * mob_sdl[TAILLE_LISTE_MOB], mob_liste_t * mob_liste, int i);
void mob_aggro(Sprite *mob[TAILLE_LISTE_MOB], int i, SDL_Rect destRect);
void anim(SDL_Renderer *renderer, Sprite * skin, personnage_t * joueur, Sprite * mob_sdl[TAILLE_LISTE_MOB], Map_t * map);

#endif