#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <time.h>
#include "move.h"
#include "inventaire.h"
#include "personnage.h"
#include "joueur.h"
#include "environnement.h"
#include "joueur.h"
#include "map.h"
#include "camera.h"
#include "mapstruct.h"
#include "inventaire.h"
#include "personnage.h"
#include "outil.h"
#include "mob.h"
//#include "fight.h"


const int FPS = 24;

int joueur(SDL_Window *window){
  SDL_Renderer *renderer = NULL;
  SDL_Surface *screenSurface = NULL;
  SDL_Texture *skin = NULL;
  SDL_Texture *textureright = NULL;
  SDL_Texture *textureleft = NULL;
  SDL_Rect inv;
  SDL_Texture * inventaire = NULL;


  // Calcule de période
  double period = 1.0 / (double)FPS;
  period = period * 50;
  int milliPeriod = (int)period;
  int sleep;
  int calcul[TAILLE_LISTE_MOB];



  SDL_Event event;
  Map_t * loaded_map = NULL;
  Sprite * joueur = NULL;
  //TILE_MAP map[TILES_X][TILES_Y];
  //MOUSE_COORD mouse;
  int vx = 0, vy = 0;
  int quit = 0;
  int click;



  inventaire_t * inventaire_joueur = create_inventaire();
  objet_t * obj = create_objet();
  obj->id = 1;
  loot(inventaire_joueur, obj);
  personnage_t * joueur_stat = create_personnage();

  mob_liste_t * mob_liste = create_liste_mob();
  mob_t * mob = create_mob();
  mob->id = 1;
  ajuste(mob);
  ajouter_mob(mob_liste, mob);
  ajouter_mob(mob_liste, mob);



  //SDL_Point viewOffset;


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

  inventaire = IMG_LoadTexture(renderer, "ressources/Inventaire/Inventaire.png");
    if (!inventaire) {
      printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
      goto quit;
    }
  // Créer la texture de Darick
  skin = textureright;

  inv.x = 0;
  inv.y = -100;
  inv.w = 1280;
  inv.h = 720;



  // Créer la map
  Index_t map;
  map.tileX = 40;
  map.tileY = 40;
  for (int i = 0 ; i < map.tileY ; i++ ){
    for(int j = 0 ; j < map.tileX ; j++ ){
      map.intmap[i][j] = map1[i][j];
    }
  }
  loaded_map = LoadMap(map);
  LoadMapRect(loaded_map);

  //Initialiser Darick
  joueur = InitialiserSprite(640, 360, DARICK_SIZE, DARICK_SIZE, loaded_map);


  //menu();


  //Initialisation de la camera

  FocusScrollBox(loaded_map, joueur);

  //Ticks
  Uint32 lastTick;
  Uint32 currentTick;

  Sprite * mob_sdl[TAILLE_LISTE_MOB];
  //init_mob(loaded_map, renderer, mob_liste, mob_sdl);
  mob_sdl[0] = InitialiserSprite(650, 380, DARICK_SIZE, DARICK_SIZE, loaded_map);
  mob_sdl[0]->texture = IMG_LoadTexture(renderer, liste_mobs[mob_liste->liste[0]->id-1].texture);
  mob_sdl[1] = InitialiserSprite(650, 380, DARICK_SIZE, DARICK_SIZE, loaded_map);
  mob_sdl[1]->texture = IMG_LoadTexture(renderer, liste_mobs[mob_liste->liste[1]->id-1].texture);

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
          case SDLK_i:
            afficher_inv_SDL(renderer,inventaire,inv , inventaire_joueur, screenSurface, window, joueur_stat);
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
        if( event.button.button == SDL_BUTTON_LEFT ){
          //mouse.x = event.button.x; // Position de la souris
          //mouse.y = event.button.y;
          //fight(renderer, skin, player, mouse, dir);
        }
        break;


    }
  
    srand(time(NULL)); // Reinitialise les valeurs généré aléatoirement afin de ne pas avoir le meme deplacement pour chaque mob + enleve un bug de tremblement des mobs
    for (int i = 0; i<TAILLE_LISTE_MOB; i++){
      deplacement_mobV2(mob_sdl, i);
      SDL_RenderCopy(renderer, mob_sdl[i]->texture, NULL, &mob_sdl[i]->position);
    }
  
  // Effacer l'écran
  SDL_SetRenderDrawColor(renderer, 0x3C, 0x1F, 0x1F, 0xFF);
  SDL_RenderClear(renderer);
  
  // Chargement de la map
  ShowMap(loaded_map, renderer);

  //Deplacement
  DeplaceSprite(joueur, vx, vy);
  AfficherSprite(joueur, renderer, skin);

  SDL_Rect dest_rect;
  for (int i = 0; i < TAILLE_LISTE_MOB; i++) {
    dest_rect.x = mob_sdl[i]->position.x - loaded_map->xscroll;
    dest_rect.y = mob_sdl[i]->position.y - loaded_map->yscroll;
    dest_rect.w = DARICK_SIZE;
    dest_rect.h = DARICK_SIZE;
    SDL_RenderCopy(renderer, mob_sdl[i]->texture, NULL, &dest_rect);
  }
  // Copier la texture du perso sur le rendu
  //SDL_RenderCopy(renderer, skin, &srcRect, &loaded_map->player);
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
  FreeMap(loaded_map);
  LibereSprite(joueur);
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  //Fermer la fenetre
  return 0;
}