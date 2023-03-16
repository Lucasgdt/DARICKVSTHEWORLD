#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "personnage.h"



personnage_t * create_personnage() {
    personnage_t * personnage = malloc(sizeof(personnage_t));
    personnage->as = 0;
    personnage->armure = 0;
    personnage->degats = 10;
    personnage->mana = 0;
    personnage->pv = 20;
    personnage->regen = 0;

    return personnage;
}

void equiper(personnage_t * personnage, objet_t * obj) {
    
    personnage->armure += liste_objets[obj->id - 1].armure;

    personnage->as += liste_objets[obj->id - 1].as;

    personnage->degats += liste_objets[obj->id - 1].degats;

    personnage->regen += liste_objets[obj->id - 1].regen;

    personnage->pv += liste_objets[obj->id - 1].pv;

    personnage->mana += liste_objets[obj->id - 1].mana;

}

void retirer (personnage_t * personnage, objet_t * obj){
    personnage->armure -= liste_objets[obj->id - 1].armure;

    personnage->as -= liste_objets[obj->id - 1].as;

    personnage->degats -= liste_objets[obj->id - 1].degats;

    personnage->regen -= liste_objets[obj->id - 1].regen;

    personnage->pv -= liste_objets[obj->id - 1].pv;

    personnage->mana -= liste_objets[obj->id - 1].mana;
}

void afficher_stat_joueur(personnage_t * personnage){
    printf("Voici les statistiques de %s : \n", personnage->nom);
    printf("Degats : %d \n",personnage->degats);
    printf("Vitesse d'attaque : %d \n",personnage->as);
    printf("Armure : %d \n",personnage->armure);
    printf("Regeneration : %d \n",personnage->regen);
    printf("PV : %d \n",personnage->pv);
    printf("Mana : %d \n",personnage->mana);
}



