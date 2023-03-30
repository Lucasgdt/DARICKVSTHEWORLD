#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "move.h"
#include "inventaire.h"
#include "personnage.h"
#include "mob.h"
#include "name.h"
#include "bossFight.h"
#include "deplacementCyclope.h"

/**
 * @brief Fonction main, cette fonction a pour but de lancer le programme, c'est à dire le menu principal
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */

int main(int argc, char *argv[]){

    SDL_Window *window = NULL;

  int running = 1;

// Initialiser SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    //goto quit;
  }

  // Créer la fenêtre
  window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (!window) {
    printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
    //goto quit;
  }

  menu();
  

  //Fermer la fenetre
  SDL_DestroyWindow(window);
  // Quitter SDL
  SDL_Quit();

  return 0;
}