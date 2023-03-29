#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "inventaire.h"
#include "action.h"

#ifndef MOVE_H
#define MOVE_H

#include "inventaire.h"
#include "action.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define DARICK_SIZE 96

#define speed 30

void anim(SDL_Renderer *renderer, SDL_Rect destRect, int left, int right);
void deplacement_mob(texture_t * mob[TAILLE_LISTE_MOB]);
void deplacement_mobV2(texture_t * mob[TAILLE_LISTE_MOB], int i);
void mob_aggro(texture_t *mob[TAILLE_LISTE_MOB], int i, SDL_Rect destRect);
int move(personnage_t * joueur, inventaire_t * inventaire_joueur);

#endif