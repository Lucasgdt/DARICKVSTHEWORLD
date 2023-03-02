#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "move.h"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 50

int menu() {
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Surface *background = NULL;
    SDL_Surface *quitButtonTexture = NULL;
	SDL_Surface *playButtonTexture = NULL;
	SDL_Surface *optionButtonTexture = NULL;
    SDL_Event event;
    int quit = 0;
    int w, h;
    SDL_Rect quitButton = {WINDOW_WIDTH - BUTTON_WIDTH - 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
	SDL_Rect playButton = {WINDOW_WIDTH - BUTTON_WIDTH - 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT};
	SDL_Rect optionButton = {WINDOW_WIDTH - BUTTON_WIDTH - 10, 10, BUTTON_WIDTH, BUTTON_HEIGHT};



    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        goto quit;
    }

    window = SDL_CreateWindow("Window with Background and Quit Button", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        goto quit;
    }

    screenSurface = SDL_GetWindowSurface(window);

    background = IMG_Load("ressources/Menu/Background.png");
    if (background == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Background.png", SDL_GetError());
        goto quit;
    }
	
	// Bouton quitter
    quitButtonTexture = IMG_Load("ressources/Menu/Menu_principal/Bouton/Quitter.png");
	// Taille
	quitButton.w = 150;
	quitButton.h = 75;
	// Position
	quitButton.x -= 600;
	quitButton.y += 550;
    if (quitButtonTexture == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Menu_principal/Bouton/Quitter.png", SDL_GetError());
        goto quit;
    }

	// Bouton jouer

    playButtonTexture = IMG_Load("ressources/Menu/Menu_principal/Bouton/Jouer.png");
	// Taille
	playButton.w = 150;
	playButton.h = 75;
	// Position
	playButton.x -= 600;
	playButton.y += 350;
    if (playButtonTexture == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Menu_principal/Bouton/Jouer.png", SDL_GetError());
        goto quit;
    }

	// Bouton option

    optionButtonTexture = IMG_Load("ressources/Menu/Menu_principal/Bouton/Option.png");
	// Taille
	optionButton.w = 150;
	optionButton.h = 75;
	// Position
	optionButton.x -= 600;
	optionButton.y += 450;
    if (optionButtonTexture == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "ressources/Menu/Menu_principal/Bouton/Option.png", SDL_GetError());
        goto quit;
    }


    SDL_GetWindowSize(window, &w, &h);

    SDL_Rect dest = {0, 0, w, h};
    SDL_BlitScaled(background, NULL, screenSurface, &dest);
    SDL_BlitScaled(quitButtonTexture, NULL, screenSurface, &quitButton);
	SDL_BlitScaled(playButtonTexture, NULL, screenSurface, &playButton);
	SDL_BlitScaled(optionButtonTexture, NULL, screenSurface, &optionButton);
    SDL_UpdateWindowSurface(window);

    while (!quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    goto quit;
                }
                else if (event.type == SDL_MOUSEBUTTONUP) {
                    int x, y;
                    SDL_GetMouseState(&x, &y);
                    if (x >= quitButton.x && x  && y >= quitButton.y && y <= quitButton.y + quitButton.h) {
    					goto quit;
                    }
    				if (x >= playButton.x && x  && y >= playButton.y && y <= playButton.y + playButton.h){
    					goto play;
    				}
    				if (x >= optionButton.x && x  && y >= optionButton.y && y <= optionButton.y + optionButton.h){
    					goto option;
    				}
                }
        }
    }

quit:
    SDL_FreeSurface(background);
    SDL_FreeSurface(quitButtonTexture);
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(playButtonTexture);
    SDL_FreeSurface(optionButtonTexture);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 0;

play:
    SDL_FreeSurface(background);
    SDL_FreeSurface(quitButtonTexture);
    SDL_FreeSurface(screenSurface);
    SDL_FreeSurface(playButtonTexture);
    SDL_FreeSurface(optionButtonTexture);
    SDL_DestroyWindow(window);
    SDL_Quit();
    move();

    

option:
	SDL_FreeSurface(background);
    SDL_FreeSurface(quitButtonTexture);
    SDL_DestroyWindow(window);
    SDL_Quit();
	return 2;
}