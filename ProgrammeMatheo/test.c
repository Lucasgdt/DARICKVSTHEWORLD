#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

// Constantes de la fenêtre
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]) {
    // Initialisation de SDL et de SDL_image
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur d'initialisation de SDL_image : %s\n", IMG_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre et du renderer
    SDL_Window* window = SDL_CreateWindow("Animation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement des 6 images en tant que surfaces
    SDL_Surface* surfaces[6];
    for (int i = 0; i < 6; i++) {
        char filename[32];
        sprintf(filename, "ressources/perso/Anim/darickdsgn%d.bmp", i+1);
        surfaces[i] = IMG_Load(filename);
        if (!surfaces[i]) {
            printf("Erreur de chargement de l'image %d : %s\n", i+1, IMG_GetError());
            for (int j = 0; j < i; j++) {
                SDL_FreeSurface(surfaces[j]);
            }
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // Création des textures à partir des surfaces
    SDL_Texture* textures[6];
    for (int i = 0; i < 6; i++) {
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
        if (!textures[i]) {
            printf("Erreur de création de la texture %d : %s\n", i+1, SDL_GetError());
            for (int j = 0; j <= i; j++) {
                SDL_DestroyTexture(textures[j]);
                SDL_FreeSurface(surfaces[j]);
            }
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            IMG_Quit();
            SDL_Quit();
            return 1;
        }
    }

    // Libération des surfaces
    for (int i = 0; i < 6; i++) {
        SDL_FreeSurface(surfaces[i]);
    }

    // Boucle principale
    int running = 1;
    int current_image = 0;
    SDL_Event event;
    while (running) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }

    // Effacement de l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    // Affichage de l'image courante
    SDL_RenderCopy(renderer, textures[current_image], NULL, NULL);

    // Mise à jour de l'affichage
    SDL_RenderPresent(renderer);

    // Attente de 100 millisecondes
    SDL_Delay(100);

    // Passage à l'image suivante
    current_image = (current_image + 1) % 6;
}

// Libération des textures et du renderer
for (int i = 0; i < 6; i++) {
    SDL_DestroyTexture(textures[i]);
}
SDL_DestroyRenderer(renderer);

// Fermeture de la fenêtre, de SDL_image et de SDL
SDL_DestroyWindow(window);
IMG_Quit();
SDL_Quit();

return 0;
}