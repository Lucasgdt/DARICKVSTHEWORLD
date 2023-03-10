#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "inventaire.h"

/*
    TEST EFFECTUER : - Limite de la taille de l'inventaire, exemple : Si nous avez 20 items dans l'inventaire, et que je rajoute un 21 eme item, ça me met comme quoi l'inventaire est full
                     - Si on a 19 items, et que j'en rajoute un, tout fonctionne
                     - Le nom est bien print quand on demande, aucun soucis d'id ou quoi que ce soit
*/

/* for (i = 0; i < TAILLE_INV; i++){
        free(joueur->liste[i]);
    }
    free(joueur->liste);
    free(joueur);
    
    Au cas ou si jamais il faut libéré toute la mémoire de l'inventaire

    */



/* Nombre d'elements */

extern 
int inventaire_nb_lire( inventaire_t * const inventaire )
{
  return(inventaire->taille);
} 

/* -- Acces individuel a un element */

extern 
void * inventaire_elem_lire( inventaire_t * const inventaire  , const int ind )
{
  if( (ind < 0) || (ind > inventaire_nb_lire(inventaire)-1 ) )
    {
      fprintf( stderr , "liste_elem_lire: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind , 0 , inventaire_nb_lire(inventaire)-1 );
      return(NULL);
    }

  return( inventaire->liste[ind] ) ;
}

inventaire_t * create_inventaire() {
    int i;
    inventaire_t * inventaire = malloc(sizeof(inventaire_t)*TAILLE_INV);
    inventaire->taille = TAILLE_INV;

    inventaire->liste = malloc(inventaire->taille * sizeof(inv_objet_t *));
    memset(inventaire->liste, 0, inventaire->taille * sizeof(inv_objet_t *));
    for (i = 0; i < TAILLE_INV; i++) {
        inventaire->liste[i] = malloc(sizeof(inv_objet_t));
        inventaire->liste[i]->id = -1;
    }
    // Initialisez les autres membres de inventaire_t ici
    return inventaire;
}

void loot(inventaire_t * joueur, objet_t * obj){
    int i;
    int temp = 0;

    for (i = 0; i < TAILLE_INV; i++){
        if (joueur->liste[i]->id == -1){
            joueur->liste[i]->id = obj->id;
            joueur->liste[i]->nb = 1;
            temp = i;
            break;
        }
        else if (i == TAILLE_INV - 1){
            printf("Inventaire pleins \n");
            exit(0);
        }
    }
    printf("Vous avez ramassez l'item suivant : %s \n",liste_objets[joueur->liste[temp]->id-1].nom);
}
