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
    personnage->degats = 10;
    personnage->pv = PV_START;
    personnage->pv_max = PV_START;
    personnage->as = 1;
    personnage->arme_obj = NULL;
    personnage->armure_obj = NULL;
    personnage->distance = 50;
    return personnage;
}

void equiper(personnage_t * personnage, objet_t * obj, inventaire_t * inv, int indice, texture_t * obj_sdl) {
    if(liste_objets[obj->id-1].categorie == 2){
        if(personnage->pv >=personnage->pv_max - personnage->pv){
            personnage->pv += personnage->pv_max - personnage->pv;
            supprimer_objet_inv(inv, obj, indice, obj_sdl);
        }
        else{
            personnage->pv += liste_objets[obj->id - 1].pv;
            supprimer_objet_inv(inv, obj, indice, obj_sdl);
        }
    }
    else{
        personnage->degats += liste_objets[obj->id - 1].degats;

        personnage->pv += liste_objets[obj->id - 1].pv;

        personnage->pv_max += liste_objets[obj->id - 1].pv;

        personnage->as += liste_objets[obj->id - 1].as;

        if (liste_objets[obj->id-1].categorie == 0){
            printf("Vous vous êtes equiper d'une arme \n");
            personnage->arme_obj = create_objet();
            personnage->arme_obj->id = obj->id;
        }
        if (liste_objets[obj->id-1].categorie == 1){
            printf("Vous vous êtes equiper d'une armure \n");
            personnage->armure_obj = create_objet();
            personnage->armure_obj->id = obj->id;
        }
        // Suprimer item inv
        supprimer_objet_inv(inv, obj, indice, obj_sdl);
        }
}

void retirer (personnage_t * personnage, objet_t * obj, inventaire_t * inv){
    if(personnage->arme_obj != NULL || personnage->armure_obj){
        personnage->as -= liste_objets[obj->id - 1].as;
        personnage->degats -= liste_objets[obj->id - 1].degats;
        personnage->pv -= liste_objets[obj->id - 1].pv;
        personnage->pv_max -= liste_objets[obj->id - 1].pv;
        loot(inv, obj);
        if (liste_objets[obj->id-1].categorie == 0){
            printf("Vous avez retirer votre arme ! \n");
            personnage->arme_obj = NULL;
        }
        if (liste_objets[obj->id-1].categorie == 1){
            printf("Vous avez retirer votre armure ! \n");
            personnage->armure_obj = NULL;
        }
    }
}

void afficher_stat_joueur(personnage_t * personnage){
    printf("Voici les statistiques de %s : \n", personnage->nom);
    printf("Degats : %d \n",personnage->degats);
    printf("Vitesse d'attaque : %d \n",personnage->as);
    printf("PV : %d \n",personnage->pv);
    printf("PV Max : %d \n",personnage->pv_max);
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



