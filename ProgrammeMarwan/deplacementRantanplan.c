#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "deplacementRantanplan.h"
#include "action.h"
#define NB_DEP 15
#define NB_PARTIE 20



void deplacementMobV2(texture_t * mob[NB_PARTIE], int i){
    int deplacement;
    deplacement = rand()%5;
    if (deplacement == 1 && mob[i]->rect.y > 0) {
        mob[i]->rect.y -= 15;
    }
    if (deplacement == 2 && mob[i]->rect.y < (SCREEN_HEIGHT - DARICK_SIZE)) {
        mob[i]->rect.y += 15;
    }
    if (deplacement == 3 && mob[i]->rect.x > 0) {
        mob[i]->rect.x -= 15;
    }
    if (deplacement == 4 && mob[i]->rect.x < (SCREEN_WIDTH - DARICK_SIZE)) {
        mob[i]->rect.x += 15;
    }
}
















void rantanplanAff(SDL_Renderer *renderer, texture_t **corps) {
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
       

        /* -------------------------------------------------------------------------- */
        /*                       Affichage combat du RANTANPLAN                       */
        /*                                                                            */
        /*                                                                            */
        
    
        
        /*                                                                            */
        /*                                                                            */
        /*                                                                            */
        /*                                                                            */
        /*                                                                            */
        /*                                                                            */
        /*                                                                            */
        /* -------------------------------------------------------------------------- */

        // déplacement des rantanplans mini
        
          
            for(int i = NB_PARTIE-1; i > 0; i--){
                printf("rect->x --> %d `\n", corps[i]->rect.x);
                printf("rect->y --> %d `\n", corps[i]->rect.y);
                printf("rect->h --> %d `\n", corps[i]->rect.h);
                printf("rect->w --> %d `\n", corps[i]->rect.w);



                if (x < 0 || x > SCREEN_WIDTH - corps->rect.w) {
                direction_x = -direction_x;
                }
                if (y < 0 || y > SCREEN_HEIGHT - corps->rect.h) {
                    direction_y = -direction_y;
                } 
             
              
                corps[i]->rect.x += direction_x;
                corps[i]->rect.y += direction_y;
                x = corps[i]->rect.x;
                y = corps[i]->rect.y;
                
                deplacementMobV2(corps, i);
                SDL_RenderCopy(renderer, corps[i]->texture, NULL, (&corps[i]->rect));
            }
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(5);                                                                                                                   
        }          
 } 
extern void deplacementRan(SDL_Window *window) 
{
   
    int quit = 0;  
    /* -------------------------------------------------------------------------- */
    /*                             Allocation mémoire                             */
    /* -------------------------------------------------------------------------- */
     texture_t *ran[NB_PARTIE];
    /* Ran = Rantanplan au cas où*/
    for(int i = 0; i < NB_PARTIE; i++){
        ran[i] = malloc(sizeof(texture_t));
    }

   
    SDL_Renderer *renderer = NULL;
     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      exit(0);
    }

    printf("Debug 1.1");
    // Créer le rendu
    if (!renderer) {
      printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      exit(0);
    }
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    /* -------------------------------------------------------------------------- */
    /*                           CHARGEMENT DES TEXTURES                          */
    /* -------------------------------------------------------------------------- */
     ran[0]->texture = IMG_LoadTexture(renderer,"boss/Rantanplan/RanMax.png");
     for(int i = 1; i < NB_PARTIE; i++){
        ran[i]->texture = IMG_LoadTexture(renderer, "boss/Rantanplan/RanMin.png");
     }
  
    for(int i = 0; i < NB_PARTIE; i++){
        printf("Debug 2.1");
        ran[i]->rect.x = 250 + ( i * 80);
        printf("Debug 2.1");
        ran[i]->rect.y = 250;
        printf("Debug 2.1");
        ran[i]->rect.w = BOSS_SIZE;

        printf("Debug 2.1");
        ran[i]->rect.h = BOSS_SIZE;

        printf("Debug 2.2");
        printf("chargement fini \n");
    }
    /* ---------------------------------- ---------------------------------------- */
    /*                     DEFINITION DES CORPS AdVEC LEUR RECT                   */
    /* -------------------------------------------------------------------------- */
    
    
    rantanplanAff(renderer, *&ran);
    quit:
    // Nettoyer les ressources

  
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    for(int i = 0; i < NB_PARTIE; i++){
        SDL_DestroyTexture(ran[i]->texture);
        free(ran[i]);
    }
}