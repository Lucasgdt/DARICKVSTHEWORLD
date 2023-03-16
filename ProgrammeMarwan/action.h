#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "personnage.h"
#include "mob.h"

void joueur_attaque(personnage_t * joueur, mob_t * mob);
void mob_attaque(personnage_t * joueur, mob_t * mob);