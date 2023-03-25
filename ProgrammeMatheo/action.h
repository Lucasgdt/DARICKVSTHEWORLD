#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ACTION_H
#define ACTION_H

#include "personnage.h"
#include "mob.h"

void joueur_attaque(personnage_t * joueur, mob_t * mob);
void mob_attaque(personnage_t * joueur, mob_t * mob);

#endif