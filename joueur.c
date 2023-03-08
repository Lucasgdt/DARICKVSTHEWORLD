#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "move.h"
#include "inventaire.h"
#include "personnage.h"

int joueur(SDL_Window *window){

  SDL_Renderer *renderer = NULL;
  SDL_Texture *skin = NULL;
  SDL_Texture *textureright = NULL;
  SDL_Texture *textureleft = NULL;
  SDL_Texture *inventaire = NULL;
  SDL_Event event;
  SDL_Rect srcRect, destRect;
  coord_t dir = {0, 0, 0, 0};
  bool showInventaire = false;
  bool iPressed = false;
  int quit = 0;


  // Créer le rendu
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  // Charger l'image
  textureright = IMG_LoadTexture(renderer, "ressources/perso/darickright.png");
  if (!textureright) {
    printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  textureleft = IMG_LoadTexture(renderer, "ressources/perso/darickleft.png");
  if (!textureleft) {
    printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }
  // Créer la texture de Darick
  skin = textureright;

  //menu();


  // Définir la source et la destination du rendu
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = DARICK_SIZE;
  srcRect.h = destRect.h = DARICK_SIZE;
  destRect.x = 600;
  destRect.y = 624;

/*
  int choix;
  int i;
  personnage_t * personnage = create_personnage();
  inventaire_t * joueur = create_inventaire();
  objet_t * obj = malloc(sizeof(objet_t));
  printf("Chiffre entre 1 et 3 : ");
  scanf("%d",&choix);
  obj->id = choix; 
  loot(joueur, obj);

  printf("Chiffre entre 1 et 3 : ");
  scanf("%d",&choix);
  obj->id = choix; 
  loot(joueur, obj);
  printf("Vous avez dans votre inventaire : \n");
  for(i = 0; i<TAILLE_INV; i++){
      if (joueur->liste[i]->id != -1){
          printf("- %s \n",liste_objets[joueur->liste[i]->id-1].nom);
      }
  }
  afficher_stat(personnage);
  equiper(personnage,obj);
  afficher_stat(personnage);
  free(obj);

*/

  // Boucle de récupération des events

  while (!quit) {
    SDL_PollEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            dir.up = 1;
            break;
          case SDLK_s:
            dir.down = 1;
            break;
          case SDLK_q:
            skin = textureleft;
            dir.left = 1;
            break;
          case SDLK_d:
            skin = textureright;
            dir.right = 1;
            break;
          case SDLK_i:
            if (!iPressed) { // Si la touche i n'a pas déjà été pressée
              iPressed = true; // Marquer la touche comme pressée
              showInventaire = !showInventaire; // Inverser l'état d'affichage de l'inventaire
            }
            break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            dir.up = 0;
            break;
          case SDLK_s:
            dir.down = 0;
            break;
          case SDLK_q:
            dir.left = 0;
            break;
          case SDLK_d:
            dir.right = 0;
            break;
          case SDLK_i:
            iPressed = false; // Marquer la touche comme relâchée
            break;
        }
        break;
    }
  

  // Appelle de fonction move
  move(dir, &destRect);
  

  // Effacer l'écran
  SDL_RenderClear(renderer);

  // Copier la texture sur le rendu
  SDL_RenderCopy(renderer, skin, &srcRect, &destRect);

  if (showInventaire) { // Si l'inventaire doit être affiché
    SDL_Rect invRect = {0, 0, 640, 480};
    SDL_RenderCopy(renderer, inventaire, NULL, &invRect); 
  }

  // Afficher le rendu
  SDL_RenderPresent(renderer);
  }

quit:
  //Libéré la texture
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  //Fermer la fenetre
  return 0;
}