#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#include "main.h"

int main(int argc, char * argv[]){

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
  return 0;
}