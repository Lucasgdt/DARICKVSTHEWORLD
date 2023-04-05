
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#ifndef OUTIL_H
#define OUTIL_H

#define TAILLE_MAX 256
#define TAILLE_INV 18

typedef struct texture_s{
    SDL_Texture *texture;
    SDL_Rect rect;
    SDL_Surface *surface;
}texture_t;

typedef struct objet_s{
    int id;
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int as;
    int pv;
    int categorie; // 0 = Arme, 1 = Armure, 2 = Potion
    int type; // 0 = epee, 1 = dague, 2 = shuriken, 3 = arc, 4 = baguette, 5 = autre
    int distance; // Distance auquel le joueur peut toucher un ennemie
    int taux;
}objet_t;

// Liste total des objects du jeu
extern objet_t liste_objets[];


typedef struct inv_objet_s{
    int id;
    // Nombre d'objet dans une case (permet de stack plusieurs items, comme des potions par exemple)
    int nb;
}inv_objet_t;

typedef struct inventaire_s{
    // Taille inventaire = nb;
    int taille;
    inv_objet_t ** liste;
}inventaire_t;


typedef struct personnage_s{
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int as;
    int pv;
    int pv_max;
    int distance;
    objet_t * armure_obj;
    objet_t * arme_obj;
}personnage_t;




#endif

