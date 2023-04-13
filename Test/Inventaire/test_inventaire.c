#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "inventaire.h"
#include "personnage.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main(int argc, char * argv[]){

    objet_t * potion = create_objet();
    objet_t * epee = create_objet();
    objet_t * armure = create_objet();
    objet_t * trop = create_objet();
    potion->id = 6;
    epee->id = 17;
    armure->id = 12;
    trop->id = 1;


    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *window = NULL;
    window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Surface *screenSurface = NULL;

    SDL_Rect inv;
    SDL_Texture *inventaire = NULL;
    inventaire_t *inventaire_joueur = create_inventaire();
    personnage_t *joueur_stat = create_personnage();

    loot(inventaire_joueur, potion);
    loot(inventaire_joueur, epee);
    loot(inventaire_joueur, armure);
    for (int i = 0; i<TAILLE_INV; i++){
        loot(inventaire_joueur, trop);
    }

    inventaire = IMG_LoadTexture(renderer, "ressources/Inventaire/Inventaire.png");
    if (!inventaire) {
        printf("Texture could not be loaded! SDL Error: %s\n", SDL_GetError());
        return 0;
    }

    inv.x = 0;
    inv.y = -100;
    inv.w = 1280;
    inv.h = 720;
    screenSurface = SDL_GetWindowSurface(window);

    afficher_inv_SDL(renderer, inventaire, inv, inventaire_joueur, screenSurface, window, joueur_stat);
    SDL_DestroyTexture(inventaire);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
