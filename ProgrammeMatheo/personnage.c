#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "personnage.h"
#include "outil.h"
extern objet_t liste_objets[];


personnage_t * create_personnage() {
    personnage_t * personnage = malloc(sizeof(personnage_t));
    personnage->as = 0;
    personnage->armure = 0;
    personnage->degats = 10;
    personnage->mana = 0;
    personnage->pv = 20;
    personnage->regen = 0;
    personnage->arme_obj = NULL;
    personnage->armure_obj = NULL;
    return personnage;
}

void equiper(personnage_t * personnage, objet_t * obj, inventaire_t * inv) {
    
    personnage->armure += liste_objets[obj->id - 1].armure;

    personnage->as += liste_objets[obj->id - 1].as;

    personnage->degats += liste_objets[obj->id - 1].degats;

    personnage->regen += liste_objets[obj->id - 1].regen;

    personnage->pv += liste_objets[obj->id - 1].pv;

    personnage->mana += liste_objets[obj->id - 1].mana;

    if (liste_objets[obj->id-1].categorie == 0){
        printf("Vous vous êtes equiper d'une arme \n");
        personnage->arme_obj = create_objet();
        personnage->arme_obj->id = obj->id;
    }
    if (liste_objets[obj->id-1].categorie == 1){
        personnage->armure_obj = create_objet();
        personnage->armure_obj->id = obj->id;
    }
    // Suprimer item inv
    supprimer_objet_inv(inv, obj);
}

void retirer (personnage_t * personnage, objet_t * obj, inventaire_t * inv){
    personnage->armure -= liste_objets[obj->id - 1].armure;

    personnage->as -= liste_objets[obj->id - 1].as;

    personnage->degats -= liste_objets[obj->id - 1].degats;

    personnage->regen -= liste_objets[obj->id - 1].regen;

    personnage->pv -= liste_objets[obj->id - 1].pv;

    personnage->mana -= liste_objets[obj->id - 1].mana;

    loot(inv, obj);



    if (liste_objets[obj->id-1].categorie == 0){
        printf("Vous avez retirer votre arme ! \n");
        personnage->arme_obj = NULL;
    }

    if (obj->categorie == 1){
        printf("test \n");
        personnage->armure_obj = NULL;
    }


}

void afficher_stat_joueur(personnage_t * personnage){
    printf("Voici les statistiques de %s : \n", personnage->nom);
    printf("Degats : %d \n",personnage->degats);
    printf("Vitesse d'attaque : %d \n",personnage->as);
    printf("Armure : %d \n",personnage->armure);
    printf("Regeneration : %d \n",personnage->regen);
    printf("PV : %d \n",personnage->pv);
    printf("Mana : %d \n",personnage->mana);
    if (personnage->arme_obj != NULL){
        printf("Arme equiper : %s \n",liste_objets[personnage->arme_obj->id-1].nom);
    }
    else{
        printf("Aucune arme equiper \n");
    }
    if(personnage->armure_obj != NULL){
        printf("Armure equiper : %s \n",liste_objets[personnage->armure_obj->id].nom);
    }
    else{
        printf("Aucune armure equiper \n");
    }
}



