#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "move.h"
#include "inventaire.h"
#include "personnage.h"
#include "joueur.h"
#include "environnement.h"
#include "joueur.h"
#include "map.h"
//#include "fight.h"




int joueur(SDL_Window *window){

  SDL_Renderer *renderer = NULL;
  SDL_Texture *skin = NULL;
  SDL_Texture *textureright = NULL;
  SDL_Texture *textureleft = NULL;
  SDL_Texture *inventaire = NULL;
  SDL_Texture *tile_texture = NULL;
  SDL_Event event;
  SDL_Rect srcRect, player;
  SDL_Rect select_tile[NB_TILES];
  TILE_MAP map[TILES_X][TILES_Y];
  //MOUSE_COORD mouse;
  coord_t dir = {0, 0, 0, 0};
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


  SDL_Surface * tile_map_surface = IMG_Load("ressources/map/tiles_map.png");
  tile_texture = SDL_CreateTextureFromSurface(renderer, tile_map_surface);
  SDL_FreeSurface(tile_map_surface);

  //menu();



  // Définir la source et la destination du rendu
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = player.w = DARICK_SIZE;
  srcRect.h = player.h = DARICK_SIZE;
  player.x = 200;
  player.y = 200;
  SDL_Rect camera = { (player.x + SCREEN_WIDTH/2)/SIZE_TILES, (player.y + SCREEN_HEIGHT/2)/SIZE_TILES, SCREEN_WIDTH, SCREEN_HEIGHT };

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



  // Fonction d'initialisation des outils de map
  INIT_MAP(map, select_tile);

  // Boucle de récupération des events

  while (!quit) {
    SDL_PollEvent(&event);
    switch (event.type) {
      case SDL_QUIT:
        quit = 1;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_z:
            dir.up = 1;
            break;
          case SDLK_s:
            dir.down = 1;
            break;
          case SDLK_q:
            skin = textureleft;
            dir.left = 1;
            break;
          case SDLK_d:
            skin = textureright;
            dir.right = 1;
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
            dir.up = 0;
            break;
          case SDLK_s:
            dir.down = 0;
            break;
          case SDLK_q:
            dir.left = 0;
            break;
          case SDLK_d:
            dir.right = 0;
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

  //Deplacement
  move(dir, &player, map);
  
  //centerCam(player, &viewOffset, dir);

  camera = moveCam(camera, &player);
  // Chargement de la map
  LOAD_MAP(renderer, tile_texture, select_tile, map, map1, camera);

  // Copier la texture du perso sur le rendu
  SDL_RenderCopy(renderer, skin, &srcRect, &player);
  // Afficher le rendu

  SDL_RenderPresent(renderer);


  }

quit:
  //Libéré la texture
  SDL_DestroyTexture(textureright);
  SDL_DestroyTexture(textureleft);
  SDL_DestroyTexture(tile_texture);
  //Libéré le rendu
  SDL_DestroyRenderer(renderer);
  //Fermer la fenetre
  return 0;
}