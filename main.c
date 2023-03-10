#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "move.h"
#include "inventaire.h"
#include "personnage.h"
#include "joueur.h"
#include "menu.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720



int main(){
    SDL_Window *window = NULL;
    int status;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        goto quit;
    }


    status = menu();

    if(status == 1){
        window = SDL_CreateWindow("DARICK VS THE WORLD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
            if (window == NULL) {
                printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        goto quit;
    }
        joueur(window);
        goto quit;
    }
    else
        goto quit;

    

quit:
    SDL_DestroyWindow(window);
    SDL_Quit();
}