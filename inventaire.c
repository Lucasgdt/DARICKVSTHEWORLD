#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_MAX 256
#define TAILLE_INV 20


typedef struct object_s{
    int id;
    char nom[SIZE_MAX];
    char texture[SIZE_MAX];
    int degats;
    int armure;
    int regen;
    int as;
}objet_t;

// Liste total des objects du jeu
static objet_t liste_objets[] = {
    {1, "Epee du Nain", "daricksword.png", 1, 0, 0, 1},
    {2, "Epee du feur", "daricksword.png", 1, 0, 0, 1},
    {3, "Baton du vide", "daricksword.png", 1, 0, 0, 1}
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
    int temp;

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



// Quand tu compiles, met tout le main en commentaire en attendant

int main(){

    int choix;
    int i;
    inventaire_t * joueur = create_inventaire();
    objet_t * obj = malloc(sizeof(objet_t));

    printf("Chiffre entre 1 et 3 : ");
    scanf("%d",&choix);

    obj->id = choix; 
    loot(joueur, obj);

    for(i = 0; i<TAILLE_INV; i++){
        if (joueur->liste[i]->id != -1){
            printf("Vous avez dans votre inventaire : \n");
            printf("- %s \n",liste_objets[joueur->liste[i]->id-1].nom);
        }
    }
}