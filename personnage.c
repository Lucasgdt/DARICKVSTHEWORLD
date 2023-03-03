#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "personnage.h"
#include "inventaire.h"

personnage_t * create_personnage() {
    personnage_t * personnage = malloc(sizeof(personnage_t));
    personnage->as = 0;
    personnage->armure = 0;
    personnage->degats = 0;
    personnage->mana = 0;
    personnage->pv = 20;
    personnage->regen = 0;

    printf("Quel est votre nom : ");
    scanf("%s",personnage->nom);
    printf("Bonjour %s ! \n",personnage->nom);
    return personnage;
}

void equiper (personnage_t * personnage, objet_t * obj){
    personnage->armure += liste_objets[obj->armure].armure;
    personnage->as += liste_objets[obj->as].as;
    personnage->degats += liste_objets[obj->degats].degats;
    personnage->regen += liste_objets[obj->regen].regen;
}

void retirer (personnage_t * personnage, objet_t * obj){
    personnage->armure -= liste_objets[obj->armure].armure;
    personnage->as -= liste_objets[obj->as].as;
    personnage->degats -= liste_objets[obj->degats].degats;
    personnage->regen -= liste_objets[obj->regen].regen;
}

void afficher_stat(personnage_t * personnage){
    printf("Voici les statistiques de %s : \n", personnage->nom);
    printf("Degats : %d \n",personnage->degats);
    printf("Vitesse d'attaque : %d \n",personnage->as);
    printf("Armure : %d \n",personnage->armure);
    printf("Regeneration : %d \n",personnage->regen);
}



