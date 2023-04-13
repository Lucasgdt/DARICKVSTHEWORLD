#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <time.h>
#include "move.h"
#include "inventaire.h"
#include "personnage.h"
#include "environnement.h"
#include "joueur.h"
#include "map.h"
#include "camera.h"
#include "mapstruct.h"
#include "outil.h"
#include "mob.h"
#include "action.h"
#include "menu.h"

/**
 * @brief Permet de mettre en pause le jeu, afin de soit reprendre le jeu, soit sauvegarder, soit quitter le jeu
 * 
 * @param renderer 
 * @return int 
 */

int pause(SDL_Renderer * renderer){
  printf("Pause \n");
  int pressed = 1;
  int x, y;
  SDL_Event event;
  SDL_Texture * EchapTexture = IMG_LoadTexture(renderer, "ressources/Menu/echapback.png");
  SDL_Rect Echap;
  SDL_Texture * playtexture = IMG_LoadTexture(renderer, "ressources/Menu/Menu_principal/Bouton/Jouer.png");
  SDL_Rect play;
  SDL_Texture * quittexture = IMG_LoadTexture(renderer, "ressources/Menu/Menu_principal/Bouton/Quitter.png");
  SDL_Rect quit;
  SDL_Texture * savetexture = IMG_LoadTexture(renderer, "ressources/Menu/Menu_principal/Bouton/Save.png");
  SDL_Rect save;

  EchapTexture = IMG_LoadTexture(renderer, "ressources/Menu/echapback.png");
  if (!EchapTexture) {
    printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
    return 0;
  }
  Echap.h = 720;
  Echap.w = 400;
  Echap.x = 400;
  Echap.y = 0;

  play.h = 150;
  play.w = 350;
  play.x = 425;
  play.y = 100;

  save.h = 150;
  save.w = 350;
  save.x = 425;
  save.y = 300;

  quit.h = 150;
  quit.w = 350;
  quit.x = 425;
  quit.y = 500;

  while(pressed){
    SDL_PollEvent(&event);
    switch (event.type){
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_ESCAPE:
                pressed = 0;
                break;
          default:
                break;
        }
      case SDL_MOUSEBUTTONUP:
         if (event.button.button == SDL_BUTTON_LEFT){
                SDL_GetMouseState(&x, &y);
                if (x >= play.x && x  && y >= play.y && y <= play.y + play.h){
                  return 1;
                }
                if (x >= save.x && x  && y >= save.y && y <= save.y + save.h){
                  printf("Normalement ça save \n");
                  return 2;
                }
                if (x >= quit.x && x  && y >= quit.y && y <= quit.y + quit.h){
                  return 0;
                }
        break;
        }

    }
    SDL_RenderCopy(renderer, EchapTexture, NULL, &Echap);
    SDL_RenderCopy(renderer, playtexture, NULL, &play);
    SDL_RenderCopy(renderer, savetexture, NULL, &save);
    SDL_RenderCopy(renderer, quittexture, NULL, &quit);
    SDL_RenderPresent(renderer);
  }
  SDL_DestroyTexture(EchapTexture);
  SDL_DestroyTexture(playtexture);
  SDL_DestroyTexture(savetexture);
  SDL_DestroyTexture(quittexture);
}

/**
 * @brief Fonction permettant de gérer tout le jeu, c'est à dire, initialisation du joueur + mob + changement de salle etc ...
 * 
 * @param window 
 * @return int 
 */


int joueur(SDL_Window *window, int * nbsalle, int * kill){
  // Initialisation de SDL_ttf
  TTF_Init();
  TTF_Font * font = TTF_OpenFont("ressources/Font/font.ttf",24);
  SDL_Color color = {255, 255, 255, 255}; // Définir la couleur du texte

  SDL_Surface* surface = NULL;
  SDL_Texture* texture = NULL;
  char str[256];
  SDL_Renderer *renderer = NULL;
  SDL_Surface *screenSurface = NULL;
  SDL_Texture *skin = NULL;
  SDL_Texture *textureright = NULL;
  SDL_Texture *textureleft = NULL;
  SDL_Rect inv;
  SDL_Texture * inventaire = NULL;
  SDL_Texture * pdvtexture = NULL;
  SDL_Rect pdv;


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
  *kill = 0;
  *nbsalle = 1;


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

/* -------------------------------------------------------------------------- */
/*                   Initialisation de l'image point de vie                   */
/* -------------------------------------------------------------------------- */

  pdvtexture = IMG_LoadTexture(renderer, "ressources/perso/coeur.png");

  if (!pdvtexture) {
      printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
      goto quit;
  }

  pdv.h = 50;
  pdv.w = 50;
  pdv.x = 10;
  pdv.y = 650;

  /* -------------------------------------------------------------------------- */
  /*                           Initialisation des mobs                          */
  /* -------------------------------------------------------------------------- */

  Sprite * mob_sdl[TAILLE_LISTE_MOB];
  init_mob(loaded_map, renderer, mob_liste, mob_sdl);

  Sprite * shop_sdl = malloc(sizeof(Sprite));
  mob_t * shop = create_mob();
  shop->id = 5;
  ajuste(shop);
  shop_sdl->texture = IMG_LoadTexture(renderer, "ressources/Mobs/Mob2.png");


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
            printf("Placement X : %d Y : %d \n",player->position.x, player->position.y);
            printf("Placement2 X : %d Y : %d", shop_sdl->position.x, shop_sdl->position.y);
            break;
          case SDLK_i:
            afficher_inv_SDL(renderer,inventaire,inv , inventaire_joueur, screenSurface, window, joueur_stat);
            break;
          case SDLK_ESCAPE:
            if(pause(renderer) == 0){
              goto quit;
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
                      if(mob_liste->liste[i]->id == 4){
                        printf("BOSS MORT \n");
                        (*kill)++;
                        loot_mob(inventaire_joueur, joueur_stat);
                        delete_mob(mob_liste, i, mob_sdl);
                        free(mob_liste->liste[i]);
                        mob_liste->liste[i] = NULL;
                      }
                      else{
                        (*kill)++;
                        loot_mob(inventaire_joueur, joueur_stat);
                        delete_mob(mob_liste, i, mob_sdl);
                        free(mob_liste->liste[i]);
                        mob_liste->liste[i] = NULL;
                      }

                    }
                }
            }
            anim(renderer, player, joueur_stat, mob_sdl, loaded_map, pdvtexture, pdv);
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
      printf("Vous avez tuer : %d monstres ! \n",*kill);
      printf("Vous êtes arriver à la salle : %d \n",*nbsalle);
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
    (*nbsalle)++;
    vider_liste_mob(mob_liste, mob_sdl); 
    
    if((*nbsalle)%5==0){
      // Delete sprite shop
      mob_t * boss = create_mob();
      boss->id = 4;
      ajuste(boss);
      ajouter_mob(mob_liste, boss);
      for (int i = 1; i<TAILLE_LISTE_MOB; i++){
        mob_t * mob = create_mob();
        mob->id = 1;
        ajuste(mob);
        mob->pv = mob->pv*(*nbsalle);
        ajouter_mob(mob_liste, mob);
      }
    }
    else{
      for (int i = 0; i<TAILLE_LISTE_MOB; i++){
        mob_t * mob = create_mob();
        mob->id = 1;
        ajuste(mob);
        mob->pv = mob->pv*(*nbsalle);
        ajouter_mob(mob_liste, mob);
      }
    }
    UpdateMap(map);

    loaded_map = LoadMap(map);
    LoadMapRect(loaded_map);

    if((*nbsalle)%5==4){

      int endX = 0;
      int endY = 0;
      find_end(map, &endX, &endY);

      printf("X : %d Y : %d \n",endX, endY);
      SDL_Point end;
      end.x = endX;
      end.y = endY;

      int mobx, moby;
      SDL_Point MobPose;

      shop_sdl->position.h = DARICK_SIZE;
      shop_sdl->position.w = DARICK_SIZE;

      shop_sdl->m = loaded_map;

      MobPose = placement_shop(shop_sdl, end);

      mobx = MobPose.x;
      moby = MobPose.y;
      shop_sdl->position.x = mobx * ZOOM;
      shop_sdl->position.y = moby * ZOOM;
    }
    player = InitialiserSprite(300, 300, DARICK_SIZE, DARICK_SIZE, loaded_map);
    init_mob(loaded_map, renderer, mob_liste, mob_sdl);
    FocusScrollBox(loaded_map, player);
  }

  AfficherSprite(player, renderer, skin);

  for (int i = 0; i < TAILLE_LISTE_MOB; i++) {
    AfficherSprite(mob_sdl[i], renderer, mob_sdl[i]->texture);
  }
  if((*nbsalle)%5==4){
    AfficherSprite(shop_sdl, renderer, shop_sdl->texture);
  }


  sprintf(str,"PV : %d/%d",joueur_stat->pv, joueur_stat->pv_max);
  surface = TTF_RenderText_Solid(font, str, color); // Créer une surface contenant le texte
  texture = SDL_CreateTextureFromSurface(renderer, surface); // Créer une texture à partir de la surface
  SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){80, 660, surface->w, surface->h}); // Afficher la texture sur le rendu

  SDL_RenderCopy(renderer, pdvtexture, NULL, &pdv);


  // Afficher le rendu

  currentTick = SDL_GetTicks();
  sleep = milliPeriod - (currentTick - lastTick);
  if(sleep < 0)
    sleep = 0;
  SDL_Delay(sleep);
  SDL_RenderPresent(renderer);
  }


quit:
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  SDL_DestroyTexture(pdvtexture);
  //Libéré la texture
  FreeMap(loaded_map);
  LibereSprite(player);
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  TTF_CloseFont(font);
  TTF_Quit();
  return 0;
}

int ecran_fin(SDL_Window * window, int * nbsalle, int * kill){
  // Initialisation de SDL_ttf
  TTF_Init();
  SDL_Renderer * renderer = NULL;
  SDL_Texture *screenSurface = NULL;
  SDL_Texture *quitButtonTexture = NULL;
	SDL_Texture *playButtonTexture = NULL;
  SDL_Rect quitButton = {WINDOW_WIDTH - BUTTON_WIDTH - 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
	SDL_Rect playButton = {WINDOW_WIDTH - BUTTON_WIDTH - 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
  SDL_Texture * background = NULL;
  SDL_Rect back;
  SDL_Event event;
  int quit = 0;
  int w, h;

  back.x = 0;
  back.y = 0;
  back.w = 1280;
  back.h = 720;

  // Créer le rendu
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
    goto quit;
  }
  screenSurface = SDL_GetWindowSurface(window);
  background = IMG_LoadTexture(renderer,"ressources/Menu/Menu_Fin/backgroundfin.png");
    if (background == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Menu_Fin/backgroundfin.png", SDL_GetError());
        goto quit;
    }

	// Bouton quitter
  quitButtonTexture = IMG_LoadTexture(renderer,"ressources/Menu/Menu_Fin/QuitterFin.png");
	// Taille
	quitButton.w = 150;
	quitButton.h = 75;
	// Position
	quitButton.x -= 600;
	quitButton.y += 550;
  if (quitButtonTexture == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Menu_Fin/QuitterFin.png", SDL_GetError());
        goto quit;
  }
	// Bouton jouer

  playButtonTexture = IMG_LoadTexture(renderer,"ressources/Menu/Menu_Fin/JouerFin.png");
	// Taille
	playButton.w = 150;
	playButton.h = 75;
	// Position
	playButton.x -= 600;
	playButton.y += 350;
  if (playButtonTexture == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Menu_principal/Bouton/Jouer.png", SDL_GetError());
        goto quit;
  }
  SDL_UpdateWindowSurface(window);


  TTF_Font * font = TTF_OpenFont("ressources/Font/font.ttf",24);
  SDL_Color color = {255, 255, 255, 255}; // Définir la couleur du texte
  char str[256];
  sprintf(str,"Vous etes mort a la salle %d et vous avez tuer %d monstres",*nbsalle, *kill);
  SDL_Surface* surface = TTF_RenderText_Solid(font, str, color); // Créer une surface contenant le texte
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // Créer une texture à partir de la surface
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
          goto quit;
      }
      else if (event.type == SDL_MOUSEBUTTONUP) {
          int x, y;
          SDL_GetMouseState(&x, &y);
          if (x >= quitButton.x && x  && y >= quitButton.y && y <= quitButton.y + quitButton.h) {
    	        goto quit;
          }
    	    if (x >= playButton.x && x  && y >= playButton.y && y <= playButton.y + playButton.h){
    	      goto play;
    	    }
      }
    }
    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0x3C, 0x1F, 0x1F, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background, NULL, &back);
    SDL_RenderCopy(renderer, playButtonTexture, NULL, &playButton);
    SDL_RenderCopy(renderer, quitButtonTexture, NULL, &quitButton);
    SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){250, 500, surface->w, surface->h}); // Afficher la texture sur le rendu
    SDL_RenderPresent(renderer);
  }

quit:
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(quitButtonTexture);
    SDL_DestroyTexture(screenSurface);
    SDL_DestroyTexture(playButtonTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);

	  return 0;

play:
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(quitButtonTexture);
    SDL_DestroyTexture(screenSurface);
    SDL_DestroyTexture(playButtonTexture);
    //Libéré le rendu
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);

    return 1;
}