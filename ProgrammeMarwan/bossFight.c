#include <stdlib.h>
#include <stdio.h>
#include "bossFight.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#define NB_DEP 15
 int i = 0;

/*SDL_bool prog = SDL_TRUE;
int i = 0;*/
/*void animation(SDL_Renderer *renderer, SDL_Rect boss_rect,SDL_Texture * texture ){
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,texture, NULL, &boss_rect); // Affiche le rectangle du boss
    SDL_RenderPresent(renderer);
}*/

/*void deplacementSerpent(){
    SDL_Event event;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    SDL_Texture *texture = NULL;
    SDL_Rect boss_rect;
    int textureHauteur, textureLargeur;

    window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        goto quit;
    }
    else{
        printf("Window well created ! \n");
    }
    // Créer le rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      goto quit;
    }
    if(renderer == NULL){
        printf("Renderer badly created ! SDL Error : %s\n", SDL_GetError());
    }
    else{
        printf("Rendu bien chargé \n");
    }


    texture = IMG_LoadTexture(renderer,"boss/boss.png");

    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        exit(0);
    }
    else{
        printf("La texture est bien initialisé\n");
    }
    SDL_QueryTexture(texture, NULL, NULL,&textureHauteur, &textureLargeur);
    boss_rect.x = (SCREEN_WIDTH - textureLargeur) / 2;
    boss_rect.y = (SCREEN_HEIGHT - textureHauteur) / 2;

    boss_rect.h = textureHauteur;
    boss_rect.y = textureLargeur;
    bool quit = false;
    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
            for(i = 0; i < NB_DEP; i++){
                printf("Rendu image %i\n",i);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, &boss_rect);
                SDL_RenderPresent(renderer);
                boss_rect.x += 1;
                boss_rect.y += 1;
                SDL_Delay(1000 / (speed * 10));
            }
            break;
    }
    quit:
    // Nettoyer les ressources
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
} */

void deplacementSerpent(SDL_Window *window)
{
    SDL_Event event;
    /*SDL_Window *window = NULL;*/
    SDL_Renderer *renderer = NULL;
    SDL_Rect boss_rect;
    int quit = 0;
    SDL_Texture * texture; // Couleur Rouge
    /*window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);*/

    // Créer le rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      exit(0);
    }
    
    texture = IMG_LoadTexture(renderer,"boss/boss.png");
    
    // Configurez le rectangle du boss
    boss_rect.x = SCREEN_WIDTH / 2;
    boss_rect.y = SCREEN_HEIGHT / 2;
    boss_rect.h = 100;
    boss_rect.w = 100;
    printf("Salut");
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
                break; 
            }
        }
        for( i = 0; i < 5; i++){
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,texture, NULL, &boss_rect); // Affiche le rectangle du boss
                SDL_RenderPresent(renderer);
                boss_rect.x += 2;
                boss_rect.y += 2;
                SDL_Delay(50);
        }
    
       for( i = 0; i < 5; i++){
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,texture, NULL, &boss_rect); // Affiche le rectangle du boss
                SDL_RenderPresent(renderer);
                boss_rect.x += 2;
             
                SDL_Delay(50);
        }
    }
    quit:
    // Nettoyer les ressources
    SDL_DestroyRenderer(renderer);
    /*SDL_DestroyWindow(window);*/
}
