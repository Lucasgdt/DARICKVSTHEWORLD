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
#include "action.h"



/**
 * @brief Fonction permettant de gérer tout le jeu, c'est à dire, initialisation du joueur + mob + changement de salle etc ...
 * 
 * @param window 
 * @return int 
 */


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
  Sprite * player = NULL;
  //TILE_MAP map[TILES_X][TILES_Y];
  //MOUSE_COORD mouse;
  int vx = 0, vy = 0;
  int quit = 0;
  int click;
  int compteur = 24;
  int kill = 0;
  int nbsalle = 1;


  inventaire_t * inventaire_joueur = create_inventaire();
  personnage_t * joueur_stat = create_personnage();

  mob_liste_t * mob_liste = create_liste_mob();
  for (int i = 0; i<TAILLE_LISTE_MOB; i++){
    mob_t * mob = create_mob();
    mob->id = 1;
    ajuste(mob);
    ajouter_mob(mob_liste, mob);
  }




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
  map = initialize_map();
  UpdateMap(map);
  loaded_map = LoadMap(map);
  LoadMapRect(loaded_map);

  //Initialiser Darick
  player = InitialiserSprite(300, 300, DARICK_SIZE, DARICK_SIZE, loaded_map);




  //Initialisation de la camera

  FocusScrollBox(loaded_map, player);

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
            afficher_stat_joueur(joueur_stat);
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
        if (event.button.button == SDL_BUTTON_LEFT) {
          
            for (int i = 0; i<TAILLE_LISTE_MOB; i++){
                if(mob_liste->liste[i] != NULL){
                    if (mob_liste->liste[i]->pv > 0){ 
                        if(joueur_stat->arme_obj != NULL){
                            if(calcul[i] <= liste_objets[joueur_stat->arme_obj->id-1].distance){
                              joueur_attaque(joueur_stat,mob_liste->liste[i]);
                            }
                        }
                        else{
                            if(calcul[i] <= joueur_stat->distance){
                              joueur_attaque(joueur_stat,mob_liste->liste[i]);
                            }
                        }
                    }
                    if (mob_liste->liste[i]->pv <= 0){
                        kill++;
                        loot_mob(inventaire_joueur, joueur_stat);
                        delete_mob(mob_liste, i, mob_sdl);
                        free(mob_liste->liste[i]);
                        mob_liste->liste[i] = NULL;
                    }
                }
            }
            anim(renderer, player, joueur_stat, mob_sdl, loaded_map);
        }
        break;
    }

    srand(time(NULL)); // Reinitialise les valeurs généré aléatoirement afin de ne pas avoir le meme deplacement pour chaque mob + enleve un bug de tremblement des mobs
    for (int i = 0; i<TAILLE_LISTE_MOB; i++){
      if(mob_liste->liste[i] != NULL){
        calcul[i] = fonction_calcul(player->position, mob_sdl, mob_liste, i);
        if(calcul[i] <= 10){
          compteur = mob_attaque(joueur_stat, mob_liste->liste[i], compteur);
        }
      }
    }
    if(joueur_stat->pv <= 0){
      printf("Vous êtes mort ! \n");
      printf("Vous avez tuer : %d monstres ! \n",kill);
      printf("Vous êtes arriver à la salle : %d \n",nbsalle);
      goto quit;
    }
  
  // Effacer l'écran
  SDL_SetRenderDrawColor(renderer, 0x3C, 0x1F, 0x1F, 0xFF);
  SDL_RenderClear(renderer);
  
  // Chargement de la map
  ShowMap(loaded_map, renderer);

  //Deplacement
  if(DeplaceSprite(player, vx, vy) == -1){
    for(int i = 0; i < map.tileX; i++){
        for(int j = 0; j < map.tileY; j++){
            map.intmap[i][j] = 0;
        }
    }
    nbsalle++;
    vider_liste_mob(mob_liste, mob_sdl);
    for (int i = 0; i<TAILLE_LISTE_MOB; i++){
      mob_t * mob = create_mob();
      mob->id = 1;
      ajuste(mob);
      mob->pv = mob->pv*nbsalle;
      ajouter_mob(mob_liste, mob);
    }
    UpdateMap(map);
    loaded_map = LoadMap(map);
    LoadMapRect(loaded_map);
    player = InitialiserSprite(300, 300, DARICK_SIZE, DARICK_SIZE, loaded_map);
    init_mob(loaded_map, renderer, mob_liste, mob_sdl);
    FocusScrollBox(loaded_map, player);
  }

  AfficherSprite(player, renderer, skin);

  for (int i = 0; i < TAILLE_LISTE_MOB; i++) {
    AfficherSprite(mob_sdl[i], renderer, mob_sdl[i]->texture);
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
  FreeMap(loaded_map);
  LibereSprite(player);
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  //Fermer la fenetre
  return 0;


}