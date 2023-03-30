#include <stdlib.h>
#include <stdio.h>
#include "bossFight.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "action.h"
#define NB_DEP 15
#define NB_PARTIE 5

void serpentAff(SDL_Renderer *renderer, texture_t **corps) {   
     int running = 1;
    SDL_Event event;
    int centerX[NB_PARTIE];
    int centerY[NB_PARTIE];
    int angle = 0;
    int radiusX = SCREEN_WIDTH / 4;
    int radiusY = SCREEN_HEIGHT / 4;
    double x;
    double y;

    /* -------------------------------------------------------------------------- */
    /*                          Tableau coordonnée X et Y                         */
    /* -------------------------------------------------------------------------- */

    for(int i = 0; i < NB_PARTIE; i++){
        centerX[i] = corps[i]->rect.x + corps[i]->rect.h / 2;
        centerY[i] = corps[i]->rect.y + corps[i]->rect.w / 2;
        printf("\n TRANSITION \n\n");
        printf("rect->x --> %d `\n", corps[i]->rect.x);
        printf("rect->y --> %d `\n", corps[i]->rect.y);
        printf("rect->h --> %d `\n", corps[i]->rect.h);
        printf("rect->w --> %d `\n", corps[i]->rect.w);
    }
 
  
    bool etat = true;
    
        /* -------------------------------------------------------------------------- */
        /*                   Parcours en forme de cercle du serpent                   */
        /* -------------------------------------------------------------------------- */
    while (running) { // Boucle principale
        while (SDL_PollEvent(&event)) { // On récupère les évènements
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }
        for (int i = 0; i < 360; i++) {
            angle = i;
            if (i >= 180) {
                angle = 360 + i;  // Changement de direction après la moitié du cercle
            }
            for(int j = NB_PARTIE-1; j >= 0; j--){    
                x = centerX[j] + radiusX * cos(angle * M_PI / 180);
                y = centerY[j] + radiusY * sin(angle * M_PI / 180);

                corps[j]->rect.x = x - corps[j]->rect.w/2 ;
                corps[j]->rect.y = y - corps[j]->rect.h/2 ;
                SDL_RenderCopy(renderer, *(&corps[j]->texture), NULL, (&corps[j]->rect));
            }
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer); // Nettoie l'écran avant de continuer
            SDL_Delay(15);
            
        }  
  
        printf("Affichage du corps");
    }   
}

extern void deplacementSerpent(SDL_Window *window)
{

  
  
    /*SDL_Window *window = NULL;*/
    SDL_Renderer *renderer = NULL;
    int quit = 0;
    int partie = 0; // Init de partie 0, on part de la partie 0 pour la tete puis aller jusqu'à la partie 8 du corps
    texture_t *serpent[NB_PARTIE];
    

    /* -------------------------------------------------------------------------- */
    /*                             Allocation mémoire                             */
    /* -------------------------------------------------------------------------- */

    
    for(int i = 0; i<NB_PARTIE; i++){
        serpent[i] = malloc(sizeof(texture_t));
    }
    
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

    serpent[0]->texture = IMG_LoadTexture(renderer,"boss/Tete.png");
    for(int i = 1; i < NB_PARTIE; i++){
        serpent[i]->texture = IMG_LoadTexture(renderer,"boss/Corps.png");
        printf("chargement text \n");
    }
     printf("chargement fini \n");
    /* -------------------------------------------------------------------------- */
    /*                     DEFINITION DES CORPS AdVEC LEUR RECT                   */
    /* -------------------------------------------------------------------------- */
    
    for(int i = 0; i < NB_PARTIE; i++){
        serpent[i]->rect.x = 250 -  (i * 80);
        serpent[i]->rect.y = 250 -  (i * 80);
        serpent[i]->rect.w = SCREEN_WIDTH / 4;
        serpent[i]->rect.h = SCREEN_HEIGHT / 4;
        printf("rect->x --> %d `\n", serpent[i]->rect.x);
        printf("rect->y --> %d `\n", serpent[i]->rect.y);
        printf("rect->h --> %d `\n", serpent[i]->rect.h);
        printf("rect->w --> %d `\n", serpent[i]->rect.w);
    }

    // Configurez le rectangle du boss
   

        // Afficher tête du serpent
        /*serpentAff(corps->tete, renderer, corps, partie);*/
    
        
  
   

   
    serpentAff(renderer, *&serpent);

  

    quit:
    // Nettoyer les ressources
    for(int i = 0; i < NB_PARTIE; i++){
        SDL_DestroyTexture(serpent[i]->texture);
    }
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    for(int i = 0; i < NB_PARTIE; i++){
        free(serpent[i]);
    }
}







