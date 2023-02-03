#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int speed = 30;


int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Texture *texture = NULL;
  SDL_Event event;
  SDL_Rect srcRect, destRect;
  int quit = 0;

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

  // Créer le rendu
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  // Charger l'image
  texture = IMG_LoadTexture(renderer, "darickdsgn.png");
  if (!texture) {
    printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }

  // Définir la source et la destination du rendu
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = 96;
  srcRect.h = destRect.h = 96;
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

  if (up) {
    destRect.y -= 1;
  }
  if (down) {
    destRect.y += 1;
  }
  if (left) {
    destRect.x -= 1;
  }
  if (right) {
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
  SDL_DestroyWindow(window);

  // Quitter SDL
  SDL_Quit();

  return 0;
}


