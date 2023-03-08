#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "action.h"

void joueur_attaque(personnage_t * joueur, mob_t * mob){
    printf("Vous avez mis %d de degats à %s \n",joueur->degats,liste_mobs[mob->id - 1].nom);
    mob->pv-=joueur->degats;
}

void mob_attaque(personnage_t * joueur, mob_t * mob){
    printf("Le mob a mis %d de degats \n",mob->degats);
    joueur->pv-=mob->degats;
}