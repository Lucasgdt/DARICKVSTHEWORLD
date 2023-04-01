#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mob.h"

/**
 * @brief Liste des mobs contenenant les noms des monstres, les textures, ainsi que leurs statistiques
 * 
 */

mob_t liste_mobs[] = {
    {1, "Gobelin", "ressources/Mobs/Mob.png", 1, 0, 0, 1, 20, 0},
    {2, "Gnome", "ressources/Mobs/Mob2.png", 1, 10, 0, 1, 20, 300},
    {3, "Azir", "daricksword.png", 1, 20, 0, 1, 200, 0}
};

/**
 * @brief Permet de créer et initialiser un mob à 0, sans prendre les parametres de la liste
 * 
 * @return mob_t* 
 */

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

/**
 * @brief Fonction afin d'ajuster les statistiques à un mob créer correspondant à la liste des mobs
 * 
 * @param mob 
 * @return mob_t* 
 */

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

/**
 * @brief Créer une liste de mob et initialise tout à 0;
 * 
 * @return mob_liste_t* 
 */

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

/**
 * @brief Ajout d'un mob à la liste de mob
 * 
 * @param liste_des_mobs 
 * @param mob 
 * @return mob_liste_t* 
 */
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
/**
 * @brief Affiche l'intégralité des noms des mobs présents dans la liste
 * 
 * @param liste 
 */
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

/**
 * @brief Fonction permettant d'afficher les statistiques d'un mob
 * 
 * @param mob 
 */

void afficher_stat_mob(mob_t * mob){
    printf("Voici les statistiques de %s : \n", mob->nom);
    printf("Degats : %d \n",mob->degats);
    printf("Vitesse d'attaque : %d \n",mob->as);
    printf("Armure : %d \n",mob->armure);
    printf("Regeneration : %d \n",mob->regen);
    printf("PV : %d \n",mob->pv);
    printf("Mana : %d \n",mob->mana);   
}

/*void delete_mob(mob_liste_t * liste_des_mobs, mob_t * mob){
    int i;
    int temp = 0;

    for (i = 0; i < TAILLE_LISTE_MOB; i++){
        if (liste_des_mobs->liste[i] != NULL ){
            if (liste_des_mobs->liste[i] == mob){
                liste_des_mobs->liste[i] = NULL;
                temp = i;
                break;
            }
        }
    }
    printf("%d",temp);
    printf("Mobs tué : %s \n",liste_mobs[temp+1].nom);
}*/

/**
 * @brief Fonction supprimant un mob d'une liste et affichant le nom du mob supprimer
 * 
 * @param liste_des_mobs 
 * @param i 
 * @param mob 
 */

void delete_mob(mob_liste_t * liste_des_mobs, int i, texture_t * mob[TAILLE_LISTE_MOB]){
    if(liste_des_mobs->liste[i] != NULL){
        liste_des_mobs->liste[i] = NULL;
        mob[i]->texture = NULL;
    }
    printf("Mobs tué : %s \n",liste_mobs[i+1].nom);
}

/**
 * @brief Fonction afin de savoir si le mob existe
 * 
 * @param mob 
 * @return int 
 */

int mob_existe(mob_t * mob) {
    if (mob == NULL){
        return 0;
    }
    else{
        return 1;
    }
}


