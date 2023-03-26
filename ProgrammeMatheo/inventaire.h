#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#ifndef INVENTAIRE_H
#define INVENTAIRE_H

#include "personnage.h"
#include "outil.h"
extern objet_t liste_objets[];

#define TAILLE_MAX 256
#define TAILLE_INV 18



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

void afficher_inv_SDL(SDL_Renderer * renderer, SDL_Texture * inventaire, SDL_Rect inv, inventaire_t * joueur, SDL_Surface * screenSurface, SDL_Window *window, personnage_t * perso);

#endif