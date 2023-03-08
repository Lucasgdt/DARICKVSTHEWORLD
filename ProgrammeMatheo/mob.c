#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mob.h"

// Créer un mob initialiser à 0 partout (il faut donc ajuste les stats apres avec la fonction ajuste)
mob_t * create_mob() {
    mob_t * mob = malloc(sizeof(mob_t));
    mob->as = 0;
    mob->armure = 0;
    mob->degats = 0;
    mob->mana = 0;
    mob->pv = 0;
    mob->regen = 0;

    return mob;
}

// Permet de mettre les bonnes statistiques à un mob vierge
mob_t * ajuste(mob_t * mob){
    strcpy(mob->nom , liste_mobs[mob->id-1].nom);
    mob->as = liste_mobs[mob->id-1].as;
    mob->armure = liste_mobs[mob->id-1].armure;
    mob->degats = liste_mobs[mob->id-1].degats;
    mob->mana = liste_mobs[mob->id-1].mana;
    mob->pv = liste_mobs[mob->id-1].pv;
    mob->regen = liste_mobs[mob->id-1].regen;

    return mob;
}

mob_liste_t * create_liste_mob(){
    int i;
    mob_liste_t * liste_des_mobs = malloc(sizeof(mob_liste_t)*TAILLE_LISTE_MOB);
    liste_des_mobs->taille = TAILLE_LISTE_MOB;
    liste_des_mobs->liste = malloc(liste_des_mobs->taille * sizeof(mob_liste_t *));
    memset(liste_des_mobs->liste, 0, liste_des_mobs->taille * sizeof(mob_liste_t *));
    for (i = 0; i < TAILLE_LISTE_MOB; i++) {
        liste_des_mobs->liste[i] = malloc(sizeof(mob_t));
        liste_des_mobs->liste[i] = NULL;
    }

    return liste_des_mobs;
}
// Ajoute un mob à la liste de mob
mob_liste_t * ajouter_mob(mob_liste_t * liste_des_mobs, mob_t * mob){
    int i;
    int temp;

    for (i = 0; i < TAILLE_LISTE_MOB; i++){
        if (liste_des_mobs->liste[i] == NULL){
            liste_des_mobs->liste[i] = mob;
            temp = i;
            break;
        }
        else if (i == TAILLE_LISTE_MOB - 1){
            printf("Liste des mobs pleines \n");
            exit(0);
        }
    }
    printf("Mobs ajoute : %s et il est ici %d \n",liste_mobs[liste_des_mobs->liste[temp]->id-1].nom, temp);
    return liste_des_mobs;
}

void afficher_liste_mob(mob_liste_t * liste){
    int i;
    int temp = 0;
    printf("Liste des mobs : \n");
    for (i = 0; i<TAILLE_LISTE_MOB; i++){
        if (liste->liste[i] != NULL){
            printf("- %s \n",liste_mobs[liste->liste[i]->id-1].nom);
            temp++;
        }
    }
    if (temp == 0){
        printf("Liste des mobs vides \n");
    }
}

void afficher_stat_mob(mob_t * mob){
    printf("Voici les statistiques de %s : \n", mob->nom);
    printf("Degats : %d \n",mob->degats);
    printf("Vitesse d'attaque : %d \n",mob->as);
    printf("Armure : %d \n",mob->armure);
    printf("Regeneration : %d \n",mob->regen);
    printf("PV : %d \n",mob->pv);
    printf("Mana : %d \n",mob->mana);   
}

void delete_mob(mob_liste_t * liste_des_mobs, mob_t * mob){
    int i;
    int temp = 0;

    for (i = 0; i < TAILLE_LISTE_MOB; i++){
        if (liste_des_mobs->liste[i] != NULL ){
            if (liste_des_mobs->liste[i] == mob){
                liste_des_mobs->liste[i] = NULL;
                temp = i;
            }
        }
    }
    printf("Mobs tué : %s \n",liste_mobs[temp+1].nom);
}

int mob_existe(mob_t * mob) {
    if (mob == NULL){
        return 0;
    }
    else{
        return 1;
    }
}