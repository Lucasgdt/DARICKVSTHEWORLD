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
int running = 1;
void serpentAff(SDL_Renderer *renderer, partboss_t **corps) {    
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
        centerX[i] = corps[i]->boss_rect->x + corps[i]->boss_rect->h / 2;
        centerY[i] = corps[i]->boss_rect->y + corps[i]->boss_rect->w / 2;
        printf("\n TRANSITION \n\n");
        printf("boss_rect->x --> %d `\n", corps[i]->boss_rect->x);
        printf("boss_rect->y --> %d `\n", corps[i]->boss_rect->y);
        printf("boss_rect->h --> %d `\n", corps[i]->boss_rect->h);
        printf("boss_rect->w --> %d `\n", corps[i]->boss_rect->w);
    }
 
  
    bool etat = true;
    
        /* -------------------------------------------------------------------------- */
        /*                   Parcours en forme de cercle du serpent                   */
        /* -------------------------------------------------------------------------- */
    while(etat == true){
        for (int i = 0; i < 360; i++) {
            angle = i;
            if (i >= 180) {
                angle = 360 + i;  // Changement de direction après la moitié du cercle
            }
            for(int j = NB_PARTIE-1; j >= 0; j--){    
                x = centerX[j] + radiusX * cos(angle * M_PI / 180);
                y = centerY[j] + radiusY * sin(angle * M_PI / 180);

                corps[j]->boss_rect->x = x - corps[j]->boss_rect->w/2 ;
                corps[j]->boss_rect->y = y - corps[j]->boss_rect->h/2 ;

            
                SDL_RenderFillRect(renderer, *(&corps[j]->boss_rect));
                SDL_RenderCopy(renderer, *(&corps[j]->texture), NULL, *(&corps[j]->boss_rect));
                
                
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

  
    SDL_Event event;
    /*SDL_Window *window = NULL;*/
    SDL_Renderer *renderer = NULL;
    int quit = 0;
    int partie = 0; // Init de partie 0, on part de la partie 0 pour la tete puis aller jusqu'à la partie 8 du corps
    partboss_t *serpent[NB_PARTIE];
    

    /* -------------------------------------------------------------------------- */
    /*                             Allocation mémoire                             */
    /* -------------------------------------------------------------------------- */

    
    for(int i = 0; i<NB_PARTIE; i++){
        serpent[i] = malloc(sizeof(partboss_t));
        serpent[i]->boss_rect = malloc(sizeof(SDL_Rect));
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
        serpent[i]->boss_rect->x = 250 -  (i * 80);
        serpent[i]->boss_rect->y = 250 -  (i * 80);
        serpent[i]->boss_rect->w = SCREEN_WIDTH / 4;
        serpent[i]->boss_rect->h = SCREEN_HEIGHT / 4;
        printf("boss_rect->x --> %d `\n", serpent[i]->boss_rect->x);
        printf("boss_rect->y --> %d `\n", serpent[i]->boss_rect->y);
        printf("boss_rect->h --> %d `\n", serpent[i]->boss_rect->h);
        printf("boss_rect->w --> %d `\n", serpent[i]->boss_rect->w);
    }

    // Configurez le rectangle du boss
   

        // Afficher tête du serpent
        /*serpentAff(corps->tete, renderer, corps, partie);*/
    
        
  
   

    while (running) { // Boucle principale
        while (SDL_PollEvent(&event)) { // On récupère les évènements
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
            }
        }
        serpentAff(renderer, *&serpent);
    } 
  

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







