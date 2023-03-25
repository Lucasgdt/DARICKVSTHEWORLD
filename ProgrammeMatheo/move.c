#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <math.h>
#include "move.h"
#include "inventaire.h"
#include "action.h"

extern mob_t liste_mobs[];
#define INPUT_TEXT_SIZE 256

void anim(SDL_Renderer *renderer, SDL_Rect destRect){
// Chargement des 6 images en tant que surfaces
    SDL_Surface* surfaces[6];
    for (int i = 0; i < 6; i++) {
        char filename[50];
        sprintf(filename, "ressources/perso/Anim/darickdsgn%d.png", i+1);
        surfaces[i] = IMG_Load(filename);

    }

    // Création des textures à partir des surfaces
    SDL_Texture* textures[6];
    for (int i = 0; i < 6; i++) {
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
    }

    // Libération des surfaces
    for (int i = 0; i < 6; i++) {
        SDL_FreeSurface(surfaces[i]);
    }

    // Boucle principale
    int running = 1;
    int current_image = 0;
    int temp = 0;
    SDL_Event event;
    while (temp < 6) {
        // Affichage de l'image courante
        SDL_RenderCopy(renderer, textures[current_image], NULL, &destRect);

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);

        // Attente de 100 millisecondes
        SDL_Delay(100);

        // Passage à l'image suivante
        current_image = (current_image + 1) % 6;
        temp++;

    }
    // Libération des textures et du renderer
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(textures[i]);
    }
}

int move(personnage_t * joueur, inventaire_t * inventaire_joueur) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *skin = NULL;
    SDL_Surface * screenSurface = NULL;
    SDL_Texture *textureright = NULL;
    SDL_Texture *textureleft = NULL;
    SDL_Texture *inventaire = NULL;
    SDL_Event event;
    SDL_Rect srcRect, destRect;
    SDL_Rect inv;

    bool showInventaire = false;
    bool iPressed = false;
    int quit = 0;
    int pause = 0;
    int calcul = 0;

    texture_t * mob_sdl[TAILLE_LISTE_MOB];
    mob_liste_t * mob_liste = create_liste_mob();
    SDL_Texture * surface = NULL;
    mob_t * mob = create_mob();
    mob->id = 1;
    ajuste(mob);
    int i;
    for(i = 0; i<TAILLE_LISTE_MOB; i++){
        ajouter_mob(mob_liste, mob);
    }
    int deplacement;

    window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

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

    surface = IMG_LoadTexture(renderer,"ressources/Mobs/Mob.png");
    if (!surface) {
      printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
      goto quit;
    }

    for (i = 0; i<TAILLE_LISTE_MOB; i++){
        mob_sdl[i] = malloc(sizeof(texture_t));
        mob_sdl[i]->rect.x = 300;
        mob_sdl[i]->rect.y = 300;
        mob_sdl[i]->rect.h = DARICK_SIZE;
        mob_sdl[i]->rect.w = DARICK_SIZE;
        mob_sdl[i]->texture = surface;
    }

    objet_t * obj = create_objet();
    objet_t * obj2 = create_objet();
    objet_t * obj3 = create_objet();
    objet_t * obj4 = create_objet();
    objet_t * obj5 = create_objet();
    objet_t * obj6 = create_objet();

    obj->id = 1;
    obj2->id = 2;
    obj2->id = 2;
    obj3->id = 2;
    obj4->id = 2;
    obj5->id = 2;
    obj6->id = 2;

    inv.x = 0;
    inv.y = -100;
    inv.w = 1280;
    inv.h = 720;

    // Perso de depart a l'initialisation (il est du côté droit)
    skin = textureright;

    // Définir la source et la destination du rendu
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = destRect.w = DARICK_SIZE;
    srcRect.h = destRect.h = DARICK_SIZE;
    destRect.x = 600;
    destRect.y = 624;
    int up = 0, down = 0, left = 0, right = 0;


    screenSurface = SDL_GetWindowSurface(window);
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
                        skin = textureleft;
                        left = 1;
                        break;
                    case SDLK_d:
                        skin = textureright;
                        right = 1;
                        break;
                    case SDLK_m:
                        loot(inventaire_joueur,obj);
                        loot(inventaire_joueur,obj2);
                        loot(inventaire_joueur,obj3);
                        loot(inventaire_joueur,obj4);
                        loot(inventaire_joueur,obj5);
                        loot(inventaire_joueur,obj6);
                        break;
                    case SDLK_i:
                        afficher_inv_SDL(renderer,inventaire, inv, inventaire_joueur, screenSurface, window, joueur);
                        break;
                    case SDLK_k:
                        afficher_inventaire(inventaire_joueur);
                        break;
                    case SDLK_x:
                        retirer(joueur, joueur->arme_obj, inventaire_joueur);
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:

                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (mob_liste->liste[0]->pv > 0){
                        if(calcul <= 300){
                            afficher_stat_mob(mob_liste->liste[0]);
                            anim(renderer, destRect);
                            joueur_attaque(joueur,mob);
                            mob_attaque(joueur, mob);
                        }
                        
                        else{
                            anim(renderer, destRect);
                            printf("Pas à porter \n");
                        }
                    }
                    else{
                        delete_mob(mob_liste,mob_liste->liste[0]);
                        loot(inventaire_joueur, obj);
                        afficher_liste_mob(mob_liste);
                        mob_sdl[0]->texture = NULL;
                    }
                    printf("Clic gauche\n"); // Ajout de l'action lors du clic gauche
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

        calcul = sqrt(pow(destRect.x - mob_sdl[0]->rect.x, 2) + pow(destRect.y - mob_sdl[0]->rect.y, 2));

        srand(time(NULL));
        deplacement = rand()%5;

        if (deplacement == 1 && mob_sdl[0]->rect.y > 0) {
            mob_sdl[0]->rect.y -= 1;
        }
        if (deplacement == 2 && mob_sdl[0]->rect.y < (SCREEN_HEIGHT - DARICK_SIZE)) {
            mob_sdl[0]->rect.y += 1;
        }
        if (deplacement == 3 && mob_sdl[0]->rect.x > 0) {
            mob_sdl[0]->rect.x -= 1;
        }
        if (deplacement == 4 && mob_sdl[0]->rect.x < (SCREEN_WIDTH - DARICK_SIZE)) {
            mob_sdl[0]->rect.x += 1;
        }

        if(joueur->arme_obj != NULL){
            
        }

        // Effacer l'écran
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        // Copier la texture sur le rendu
        SDL_RenderCopy(renderer, skin, &srcRect, &destRect);
        SDL_RenderCopy(renderer, mob_sdl[0]->texture, NULL, &mob_sdl[0]->rect);

        if (showInventaire) { // Si l'inventaire doit être affiché
            SDL_Rect invRect = {0, 0, 640, 480};
            SDL_RenderCopy(renderer,inventaire, NULL, &inv);
            while(pause);
        }

        // Afficher le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / (speed * 10));
    }   

quit:
  // Nettoyer les ressources
  SDL_DestroyTexture(skin);
  SDL_DestroyRenderer(renderer);

  return 0;
}


