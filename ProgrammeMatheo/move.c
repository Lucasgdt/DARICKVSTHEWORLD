#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "move.h"

#include "inventaire.h"
#include "action.h"

#define INPUT_TEXT_SIZE 256

int move(personnage_t * joueur, inventaire_t * inventaire_joueur) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *skin = NULL;
    SDL_Texture *textureright = NULL;
    SDL_Texture *textureleft = NULL;
    SDL_Texture *inventaire = NULL;
    SDL_Event event;
    SDL_Rect srcRect, destRect;
    bool showInventaire = false;
    bool iPressed = false;
    int quit = 0;

    mob_liste_t * mob_liste = create_liste_mob();
    mob_t * mob = create_mob();
    objet_t * obj = create_objet();
    obj->id = 2;
    mob->id = 2;
    ajuste(mob);
    ajouter_mob(mob_liste,mob);
    mob_t * mob2 = create_mob();
    mob2->id = 3;
    ajuste(mob2);
    ajouter_mob(mob_liste,mob2);

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

    inventaire = IMG_LoadTexture(renderer, "ressources/Inventaire/UI/container/with_slots_variation_1.png");
    if (!inventaire) {
      printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
      goto quit;
    }

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
                        objet_t * obj2 = create_objet();
                        obj2->id = 1;
                        loot(inventaire_joueur,obj2);
                        afficher_inventaire(inventaire_joueur);
                        supprimer_objet_inv(inventaire_joueur, obj);
                        afficher_inventaire(inventaire_joueur);
                        break;
                    case SDLK_i:
                        if (!iPressed) { // Si la touche i n'a pas déjà été pressée
                            iPressed = true; // Marquer la touche comme pressée
                            showInventaire = !showInventaire; // Inverser l'état d'affichage de l'inventaire
                        }
                        break;
                }
                break;

            case SDL_MOUSEBUTTONDOWN:

                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (mob->pv > 0){
                        joueur_attaque(joueur,mob);
                        mob_attaque(joueur, mob);
                    }
                    else{
                        afficher_liste_mob(mob_liste);
                        delete_mob(mob_liste,mob);
                        loot(inventaire_joueur, obj);
                        afficher_liste_mob(mob_liste);
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
                    case SDLK_i:
                        iPressed = false; // Marquer la touche comme relâchée
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
        SDL_RenderCopy(renderer, skin, &srcRect, &destRect);

        if (showInventaire) { // Si l'inventaire doit être affiché
            SDL_Rect invRect = {0, 0, 640, 480};
            SDL_RenderCopy(renderer, inventaire, NULL, &invRect);
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


