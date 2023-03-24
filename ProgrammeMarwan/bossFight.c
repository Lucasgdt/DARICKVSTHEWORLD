#include <stdlib.h>
#include <stdio.h>
#include "bossFight.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#define NB_DEP 15
 int i = 0;

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
