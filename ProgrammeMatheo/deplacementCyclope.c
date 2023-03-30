#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "deplacementCyclope.h"
#include "action.h"
#define NB_DEP 15
#define NB_PARTIE 5

void cyclopeAff(SDL_Renderer *renderer, partboss_t *corps) {
    int running = 1;
    SDL_Event event;
    // initialisation des variables
    int x = 0; // position horizontale
    int y = 0; // position verticale
    int direction_x = 1; // direction de déplacement horizontal (1 pour droite, -1 pour gauche)
    int direction_y = 1; // direction de déplacement vertical (1 pour bas, -1 pour haut)
    int speed_x = 5; // vitesse de déplacement horizontal
    int speed_y = 2; // vitesse de déplacement vertical
    printf("Debug 1");

    printf("boss_rect->x --> %d `\n", corps->boss_rect->x);
    printf("boss_rect->y --> %d `\n", corps->boss_rect->y);
    printf("boss_rect->h --> %d `\n", corps->boss_rect->h);
    printf("boss_rect->w --> %d `\n", corps->boss_rect->w);
    
    // boucle de déplacement
   
    while (running) { // Boucle principale
        while (SDL_PollEvent(&event)) { // On récupère les évènements
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }
        // vérification des collisions avec les bords de l'écran
        if (x < 0 || x > SCREEN_WIDTH - corps->boss_rect->w) {
            direction_x = -direction_x;
        }
        if (y < 0 || y > SCREEN_HEIGHT - corps->boss_rect->h) {
            direction_y = -direction_y;
        } 
        // déplacement du cyclope
        corps->boss_rect->x += direction_x;
        corps->boss_rect->y += direction_y;
        x = corps->boss_rect->x;
        y = corps->boss_rect->y;
        SDL_RenderFillRect(renderer, corps->boss_rect);
        SDL_RenderCopy(renderer, corps->texture, NULL, corps->boss_rect);
       
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(15);
        printf("Debug 1 \n");        
        }          
 } 
extern void deplacementCyclope(SDL_Window *window) 
{
   
    SDL_Renderer *renderer = NULL;
    int quit = 0;  
    /* -------------------------------------------------------------------------- */
    /*                             Allocation mémoire                             */
    /* -------------------------------------------------------------------------- */
    partboss_t *cyclope = malloc(sizeof(partboss_t));
    cyclope->boss_rect = malloc(sizeof(SDL_Rect));
    printf("Debug 1.1");
    // Créer le rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      exit(0);
    }
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    /* -------------------------------------------------------------------------- */
    /*                           CHARGEMENT DES TEXTURES                          */
    /* -------------------------------------------------------------------------- */
     cyclope->texture = IMG_LoadTexture(renderer,"boss/OEUIL.png");
     if (cyclope->texture == NULL) {
        printf("Failed to load texture! SDL_Image Error: %s\n", IMG_GetError());
        exit(0);
    }
     printf("Debug 2.1");
     cyclope->boss_rect->x = 250;
      printf("Debug 2.1");
     cyclope->boss_rect->y = 250;
      printf("Debug 2.1");
     cyclope->boss_rect->w = SCREEN_WIDTH / 4;
      printf("Debug 2.1");
     cyclope->boss_rect->h = SCREEN_HEIGHT / 4;
     printf("Debug 2.2");
     printf("chargement fini \n");
    /* ---------------------------------- ---------------------------------------- */
    /*                     DEFINITION DES CORPS AdVEC LEUR RECT                   */
    /* -------------------------------------------------------------------------- */
    
    
    cyclopeAff(renderer, cyclope);
    quit:
    // Nettoyer les ressources
    SDL_DestroyTexture(cyclope->texture);
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    free(cyclope);
}