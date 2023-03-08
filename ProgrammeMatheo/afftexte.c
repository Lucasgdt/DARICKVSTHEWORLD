#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main (int argc, char** argv)
{

    SDL_Window *ecran = NULL;
    SDL_Surface *texte = NULL; 
    SDL_Rect position;
    SDL_Event event;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0};
    int continuer = 1;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    //    SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);
    char * text = "MXSTIK";
    ecran = SDL_CreateWindow("test", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *pSurf = SDL_GetWindowSurface(ecran);
    


    /* Chargement de la police */
    police = TTF_OpenFont("ressources/Font/font.otf", 65);
    /* Écriture du texte dans la SDL_Surface texte en mode Blended (optimal) */
    texte = TTF_RenderText_Blended(police, text, couleurNoire);

    while (continuer)
    {
    SDL_WaitEvent(&event);
    switch(event.type)
    {
        case SDL_QUIT:
        continuer = 0;
        break;
    }
        SDL_FillRect(pSurf, NULL, SDL_MapRGB(pSurf->format, 255, 255, 255));
        position.x = 0;
        position.y = 0;
        SDL_BlitSurface(texte, NULL, pSurf, &position); /* Blit du texte */
        SDL_UpdateWindowSurface(ecran);
        }
    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(texte);
    SDL_Quit();

    return EXIT_SUCCESS;
}