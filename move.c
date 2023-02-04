#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "move.h"

int move(SDL_Window *window) {

  SDL_Renderer *renderer = NULL;
  SDL_Texture *texture = NULL;
  SDL_Event event;
  SDL_Rect srcRect, destRect;
  int quit = 0;

  // Créer le rendu
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  // Charger l'image
  texture = IMG_LoadTexture(renderer, "ressources/perso/darickdsgn.png");
  if (!texture) {
    printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  // Définir la source et la destination du rendu
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = DARICK_SIZE;
  srcRect.h = destRect.h = DARICK_SIZE;
  destRect.x = 600;
  destRect.y = 624;
  int up = 0, down = 0, left = 0, right = 0;

  while (!quit) {
    SDL_PollEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            up = 1;
            break;
          case SDLK_s:
            down = 1;
            break;
          case SDLK_q:
            left = 1;
            break;
          case SDLK_d:
            right = 1;
            break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            up = 0;
            break;
          case SDLK_s:
            down = 0;
            break;
          case SDLK_q:
            left = 0;
            break;
          case SDLK_d:
            right = 0;
            break;
        }
        break;
    }

    if (up && destRect.y > 0) {
      destRect.y -= 1;
    }
    if (down && destRect.y < (SCREEN_HEIGHT - DARICK_SIZE)) {
      destRect.y += 1;
    }
    if (left && destRect.x > 0) {
      destRect.x -= 1;
    }
    if (right && destRect.x < (SCREEN_WIDTH - DARICK_SIZE)) {
      destRect.x += 1;
    }

    // Effacer l'écran
    SDL_RenderClear(renderer);

    // Copier la texture sur le rendu
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

    // Afficher le rendu
    SDL_RenderPresent(renderer);


    SDL_Delay(1000/(speed*10));
  }


quit:
  // Nettoyer les ressources
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);

  return 0;
}


