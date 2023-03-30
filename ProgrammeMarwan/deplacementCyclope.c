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


int aggroCy(SDL_Rect jRect, SDL_Rect bRect) {
    return jRect.y + bRect.h < bRect.y;
}

void animCy(SDL_Renderer *renderer, SDL_Rect destRect) {
    // Chargement des 6 images en tant que surfaces
    SDL_Surface* surfaces[17];
    for (int i = 0; i < 17; i++) {
        char filename[50];
        sprintf(filename, "boss/OEUIL/OEUIL%d.png", i+1);
        surfaces[i] = IMG_Load(filename);
    }



    // Création des textures à partir des surfaces
    SDL_Texture* textures[17];
    for (int i = 0; i < 17; i++) {
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
    }

    // Libération des surfaces
    for (int i = 0; i < 17; i++) {
        SDL_FreeSurface(surfaces[i]);
    }

    // Boucle principale
    int running = 1;
    int current_image = 0;
    int temp = 0;
    SDL_Event event;
    while (temp < 17) {
        // Affichage de l'image courante
        SDL_RenderCopy(renderer, textures[current_image], NULL, &destRect);

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);

        // Attente de 100 millisecondes
        SDL_Delay(50);

        // Clear l'image précedente 
        SDL_RenderClear(renderer);

        // Passage à l'image suivante
        current_image = (current_image + 1) % 17;
        temp++;
    }

    // Libération des textures
    for (int i = 0; i < 17; i++) {
        SDL_DestroyTexture(textures[i]);
    }
}








void cyclopeAff(SDL_Renderer *renderer, texture_t *corps, SDL_Rect jRect) {
    int running = 1;
    SDL_Event event;
    // initialisation des variables
    int x = 0; // position horizontale
    int y = 0; // position verticale
    int direction_x = 1; // direction de déplacement horizontal (1 pour droite, -1 pour gauche)
    int direction_y = 1; // direction de déplacement vertical (1 pour bas, -1 pour haut)
    int speed_x = 5; // vitesse de déplacement horizontal
    int speed_y = 2; // vitesse de déplacement vertical
    int alea = 0;
    srand(time(NULL)); 
    
    printf("Debug 1");


    
    // boucle de déplacement
   
    while (running) { // Boucle principale
        while (SDL_PollEvent(&event)) { // On récupère les évènements
            switch (event.type) {
                case SDL_QUIT:
                    running = 0;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        animCy(renderer,corps->rect);
                }
            }
        }
        
        // vérification des collisions avec les bords de l'écran
        if (x < 0 || x > SCREEN_WIDTH - corps->rect.w) {
            direction_x = -direction_x;
        }
        if (y < 0 || y > SCREEN_HEIGHT - corps->rect.h) {
            direction_y = -direction_y;
        } 
        // déplacement du cyclope
        corps->rect.x += direction_x;
        corps->rect.y += direction_y;
        x = corps->rect.x;
        y = corps->rect.y;
        alea = rand() % 300 + 1;

        SDL_RenderCopy(renderer, corps->texture, NULL, &corps->rect);
        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
        SDL_Delay(5);
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
    texture_t *cyclope = malloc(sizeof(texture_t));
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
     cyclope->texture = IMG_LoadTexture(renderer,"boss/OEUIL/OEUIL1.png");
     if (cyclope->texture == NULL) {
        printf("Failed to load texture! SDL_Image Error: %s\n", IMG_GetError());
        exit(0);
    }
    printf("Debug 2.1");
    cyclope->rect.x = 250;
    printf("Debug 2.1");
    cyclope->rect.y = 250;
    printf("Debug 2.1");
    cyclope->rect.w = SCREEN_WIDTH / 2;
    printf("Debug 2.1");
    cyclope->rect.h = SCREEN_HEIGHT / 2;
    printf("Debug 2.2");
    printf("chargement fini \n");
    /* ---------------------------------- ---------------------------------------- */
    /*                     DEFINITION DES CORPS AdVEC LEUR RECT                   */
    /* -------------------------------------------------------------------------- */
    
    
    cyclopeAff(renderer, cyclope, cyclope->rect); // Mettre a jour avc coord du joueur
    quit:
    // Nettoyer les ressources
    SDL_DestroyTexture(cyclope->texture);
    SDL_RenderClear(renderer);
    SDL_DestroyRenderer(renderer);
    free(cyclope);
}