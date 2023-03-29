#include <stdio.h>
#include <stdlib.h>

#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "inventaire.h"
#include "outil.h"
#define PV_START 5
extern objet_t liste_objets[];

personnage_t * create_personnage();

void equiper(personnage_t * personnage, objet_t * obj, inventaire_t * inv, int indice);

void retirer (personnage_t * personnage, objet_t * obj, inventaire_t * inv);

void afficher_stat_joueur(personnage_t * personnage);



#endif /* PERSONNAGE_H */
