#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* image = NULL;
    SDL_Event event;
    bool showImage = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Affichage d'image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur lors de la création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    image = IMG_LoadTexture(renderer, "ressources/Inventaire/UI/container/with_slots_variation_1.png");
    if (!image) {
        printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    while (true) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                SDL_DestroyTexture(image);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return EXIT_SUCCESS;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_i) {
                    showImage = !showImage;
                }
                break;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (showImage) {
            SDL_Rect imageRect = { 0, 0, 640, 480 };
            SDL_RenderCopy(renderer, image, NULL, &imageRect);
        }

        SDL_RenderPresent(renderer);
    }

    return EXIT_SUCCESS;
}
//Ce code charge une image à partir du fichier "image.png" situé dans un répertoire spécifié par "chemin/vers/" (à remplacer par le chemin réel). L'image est affichée lorsque la touche "i" est pressée et est masquée lorsque la touche est pressée à nouveau. L'exemple suppose que la bibliothèque SDL2 et SDL2_image sont correctement installées et configurées sur le système.




