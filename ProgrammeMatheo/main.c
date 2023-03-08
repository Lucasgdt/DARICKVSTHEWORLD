#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "move.h"
#include "inventaire.h"
#include "personnage.h"
#include "mob.h"
#include "name.h"

int main(){

    SDL_Window *window = NULL;


// Initialiser SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  // Créer la fenêtre
  window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }
  menu();
  quit:
  //Fermer la fenetre
  SDL_DestroyWindow(window);
  // Quitter SDL
  SDL_Quit();

  /*personnage_t * joueur = create_personnage();
  objet_t * obj = create_objet();
  inventaire_t * inventaire = create_inventaire();
  obj->id = 2;
  afficher_stat_joueur(joueur);
  equiper(joueur,obj);
  printf("\n");
  afficher_stat_joueur(joueur);*/
    /*printf("Avant crea mob liste \n");
    mob_liste_t * mob_liste = create_liste_mob();
    printf("Apres crea mob liste \n");
    mob_t * mob = create_mob();
    printf("Apres crea mob \n");
    objet_t * obj = create_objet();
    printf("Apres crea obj \n");
    obj->id = 2;
    mob->id = 2;
    printf("Avant ajuste \n");
    ajuste(mob);
    printf("Apres ajuste");
    ajouter_mob(mob_liste,mob);
    printf("%d",liste_mobs[mob_liste->liste[0]->id-1].id);*/
  return 0;
}