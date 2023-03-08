#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#define TAILLE_MAX 256
#define TAILLE_INV 20


typedef struct objet_s{
    int id;
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int armure;
    int regen;
    int as;
    int mana;
    int pv;
}objet_t;

// Liste total des objects du jeu
static objet_t liste_objets[] = {
    {1, "Epee du Nain", "daricksword.png", 1, 0, 0, 1, 0, 0},
    {2, "Casque du guerrier", "daricksword.png", 1, 10, 0, 1, 5000, 300},
    {3, "Baton du vide", "daricksword.png", 1, 0, 0, 1, 0, 0}
};


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


objet_t * create_objet();

/* Nombre d'elements */
extern int inventaire_nb_lire( inventaire_t * const inventaire );

/* -- Acces individuel a un element */
extern void * inventaire_elem_lire( inventaire_t * const inventaire  , const int ind );

/* On initialise l'inventaire*/
inventaire_t * create_inventaire();

/* On ajoute un item dans l'inventaire */
void loot(inventaire_t * joueur, objet_t * obj);

void afficher_inventaire(inventaire_t * joueur);

void supprimer_objet_inv(inventaire_t * joueur, objet_t * obj);

#endif