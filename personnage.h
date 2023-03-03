#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "inventaire.h"
#define TAILLE_MAX 256

typedef struct personnage_s{
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int armure;
    int regen;
    int as;
    int pv;
    int mana;
}personnage_t;

personnage_t * create_personnage();

void equiper (personnage_t * personnage, objet_t * obj);

void afficher_stat(personnage_t * personnage);