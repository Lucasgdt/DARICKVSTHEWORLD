#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>


int fight(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect destRect){
    
    SDL_Event event;
    int quit = 0;
    int mouseX, mouseY;

    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

  while (!quit) {
    mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    SDL_PollEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_:
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


    // Effacer l'écran
    SDL_RenderClear(renderer);

    // Copier la texture sur le rendu
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

    // Afficher le rendu
    SDL_RenderPresent(renderer);


    SDL_Delay(1000/(speed*10));
  }


quit:

  return 0;


}
