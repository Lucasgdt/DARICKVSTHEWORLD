#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "personnage.h"
#include "inventaire.h"

#define INPUT_TEXT_SIZE 256

int name()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window* window = SDL_CreateWindow("SDL2 Keyboard Input", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Font* font = TTF_OpenFont("ressources/Font/font.otf", 24);

    personnage_t * joueur = create_personnage();
    inventaire_t * inventaire = create_inventaire();

    char inputText[INPUT_TEXT_SIZE] = ""; // Initialize input text to an empty string
    SDL_StartTextInput();

    SDL_Event event;
    int quit = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = 1;
            else if (event.type == SDL_TEXTINPUT)
            {
                strcat(inputText, event.text.text); // Concatenate the new text to the input text
                SDL_Surface* surface = TTF_RenderText_Solid(font, inputText, (SDL_Color){255, 255, 255, 255});
                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){0, 0, surface->w, surface->h});
                SDL_RenderPresent(renderer);
                SDL_DestroyTexture(texture);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0)
                {
                    inputText[strlen(inputText) - 1] = '\0'; // Remove the last character from the input text
                    SDL_Surface* surface = TTF_RenderText_Solid(font, inputText, (SDL_Color){255, 255, 255, 255});
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_FreeSurface(surface);

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){0, 0, surface->w, surface->h});
                    SDL_RenderPresent(renderer);
                    SDL_DestroyTexture(texture);
                }
                else if (event.key.keysym.sym == SDLK_RETURN && strlen(inputText) > 0)
                {
                    
                    strcpy(joueur->nom, inputText);
                    printf("Votre pseudo est : %s \n",joueur->nom);
                    SDL_RenderClear(renderer); // Clear the renderer
                    SDL_RenderPresent(renderer);

                    // Systeme ou quand j'appuis sur entrée ça stop le fait d'écrire
                    SDL_StopTextInput();
                    TTF_CloseFont(font);
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    TTF_Quit();
                    SDL_Quit();
                    goto play;
                }
            }
        }
    }
    /*
    SDL_StopTextInput();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    On met ça ici quand on veut continuer d'écrire meme en appuyant sur entrée */
    play:
    move(joueur, inventaire);
    return 0;
}

