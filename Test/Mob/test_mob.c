#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <time.h>
#include "outil.h"
#include "mob.h"
#include "move.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(int argc, char * argv[]){
  SDL_Renderer *renderer = NULL;
  SDL_Surface *screenSurface = NULL;
  SDL_Texture *skin = NULL;
  SDL_Texture *textureright = NULL;
  SDL_Texture *textureleft = NULL;
  SDL_Window *window = NULL;


  // Calcule de période
  double period = 1.0 / (double)FPS;
  period = period * 50;
  int milliPeriod = (int)period;
  int sleep;
  int calcul[TAILLE_LISTE_MOB];



  SDL_Event event;
  Map_t * loaded_map = NULL;
  Sprite * player = NULL;
  //TILE_MAP map[TILES_X][TILES_Y];
  //MOUSE_COORD mouse;
  int vx = 0, vy = 0;
  int quit = 0;
  int click;

  mob_liste_t * mob_liste = create_liste_mob();
  for (int i = 0; i<TAILLE_LISTE_MOB; i++){
    mob_t * mob = create_mob();
    mob->id = 1;
    ajuste(mob);
    ajouter_mob(mob_liste, mob);
  }

  window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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




  //Initialiser Darick
  player = InitialiserSprite(400, 300, DARICK_SIZE, DARICK_SIZE, loaded_map);

  //Ticks
  Uint32 lastTick;
  Uint32 currentTick;

  Sprite * mob_sdl[TAILLE_LISTE_MOB];
  init_mob(loaded_map, renderer, mob_liste, mob_sdl);

  // Boucle de récupération des events
  screenSurface = SDL_GetWindowSurface(window);
  while (!quit) {
    SDL_PollEvent(&event);
    lastTick = SDL_GetTicks();
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            vy = -speed;
            break;
          case SDLK_s:
            vy = speed;
            break;
          case SDLK_q:
            skin = textureleft;
            vx = -speed;
            break;
          case SDLK_d:
            skin = textureright;
            vx = speed;
            break;
          case SDLK_x:
            break;
          case SDLK_i:
            break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            vy = 0;
            break;
          case SDLK_s:
            vy = 0;
            break;
          case SDLK_q:
            vx = 0;
            break;
          case SDLK_d:
            vx = 0;
            break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) {
        }
        break;
    }

    srand(time(NULL)); // Reinitialise les valeurs généré aléatoirement afin de ne pas avoir le meme deplacement pour chaque mob + enleve un bug de tremblement des mobs
    for (int i = 0; i<TAILLE_LISTE_MOB; i++){
      if(mob_liste->liste[i] != NULL){
        deplacement_mobV2(mob_sdl, i);
      }
    }
  // Effacer l'écran
  SDL_SetRenderDrawColor(renderer, 0x3C, 0x1F, 0x1F, 0xFF);
  SDL_RenderClear(renderer);

  SDL_RenderCopy(renderer, skin, NULL, &player->position);

  for (int i = 0; i < TAILLE_LISTE_MOB; i++) {
    
    SDL_RenderCopy(renderer, mob_sdl[i]->texture, NULL, &mob_sdl[i]->position);
  }

  // Afficher le rendu

  currentTick = SDL_GetTicks();
  sleep = milliPeriod - (currentTick - lastTick);
  if(sleep < 0)
    sleep = 0;
  SDL_Delay(sleep);
  SDL_RenderPresent(renderer);


  }
quit:
  //Libéré la texture
  LibereSprite(player);
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  //Fermer la fenetre
  return 0;

}

