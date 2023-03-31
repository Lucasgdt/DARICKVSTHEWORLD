#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "move.h"
#include "joueur.h"
#include "environnement.h"
#include "joueur.h"
#include "map.h"
#include "camera.h"
#include "mapstruct.h"
//#include "fight.h"
const int FPS = 24;

int joueur(SDL_Window *window){

  SDL_Renderer *renderer = NULL;
  SDL_Texture *skin = NULL;
  SDL_Texture *textureright = NULL;
  SDL_Texture *textureleft = NULL;
  SDL_Texture *inventaire = NULL;

  mob_liste_t * mob_liste = create_liste_mob();
  mob_t * mob = create_mob();
  mob->id = 1;
  ajuste(mob);
  ajouter_mob(mob_liste, mob);
  ajouter_mob(mob_liste, mob);
  Sprite * mob_sdl[TAILLE_LISTE_MOB];

  // Calcule de période
  double period = 1.0 / (double)FPS;
  period = period * 100;
  int milliPeriod = (int)period;
  int sleep;



  SDL_Event event;
  Map_t * loaded_map = NULL;
  Sprite * joueur = NULL;
  //TILE_MAP map[TILES_X][TILES_Y];
  //MOUSE_COORD mouse;
  int vx = 0, vy = 0;
  bool showInventaire = false;
  bool iPressed = false;
  int quit = 0;
  int click;
  
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
  // Créer la texture de Darick
  skin = textureright;


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

  init_mob(loaded_map, renderer, mob_liste, mob_sdl);

  //menu();


  //Initialisation de la camera

  FocusScrollBox(loaded_map, joueur, 200, 150, 400, 300);
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
  //Ticks
  Uint32 lastTick;
  Uint32 currentTick;

  // Boucle de récupération des events

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
          case SDLK_i:
            iPressed = false; // Marquer la touche comme relâchée
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
  

  
  // Effacer l'écran
  SDL_SetRenderDrawColor(renderer, 0x3C, 0x1F, 0x1F, 0xFF);
  SDL_RenderClear(renderer);
  
  // Chargement de la map
  ShowMap(loaded_map, renderer);

  //Deplacement
  DeplaceSprite(joueur, vx, vy);
  AfficherSprite(joueur, renderer, skin);
  
  srand(time(NULL));
  for (int i = 0; i<TAILLE_LISTE_MOB; i++){
    deplacement_mobV2(mob_sdl, i);
    SDL_RenderCopy(renderer, mob_sdl[i]->texture, NULL, &mob_sdl[i]->position);
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
  free_mob_sdl(mob_sdl);
  FreeMap(loaded_map);
  LibereSprite(joueur);
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  //Fermer la fenetre
  return 0;
}