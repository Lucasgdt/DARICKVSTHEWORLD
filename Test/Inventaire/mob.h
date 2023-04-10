#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "outil.h"
#include "mapstruct.h"
#ifndef MOB_H
#define MOB_H

#define TAILLE_MAX 256
#define TAILLE_LISTE_MOB 10

typedef struct mob_s{
    int id;
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int armure;
    int regen;
    int as;
    int pv;
    int mana;
}mob_t;

typedef struct mob_liste_s{
    int taille;
    mob_t ** liste;
}mob_liste_t;

// Liste total des objects du jeu
extern mob_t liste_mobs[];

mob_t * create_mob();
void afficher_stat_mob(mob_t * mob);
//void delete_mob(mob_liste_t * liste_des_mobs, mob_t * mob);
void delete_mob(mob_liste_t * liste_des_mobs, int i, Sprite * mob[TAILLE_LISTE_MOB]);
int mob_existe(mob_t * mob);
mob_liste_t * create_liste_mob();
mob_liste_t * ajouter_mob(mob_liste_t * liste_des_mobs, mob_t * mob);
mob_t * ajuste(mob_t * mob);
void afficher_liste_mob(mob_liste_t * liste);

#endif