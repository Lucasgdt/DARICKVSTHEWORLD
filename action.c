#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "action.h"
extern objet_t liste_objets[];
extern mob_t liste_mobs[];

void joueur_attaque(personnage_t * joueur, mob_t * mob){
    printf("Vous avez mis %d de degats à %s \n",joueur->degats,liste_mobs[mob->id - 1].nom);
    mob->pv-=joueur->degats;
}

void mob_attaque(personnage_t * joueur, mob_t * mob){
    int choix;
    choix = rand()%3;
    if(choix == 1){
        printf("%s a mis %d de degats \n",mob->nom, mob->degats);
        joueur->pv-=mob->degats;
    }
    else{
        printf("%s, à loupé son coup \n",mob->nom);
    }

}