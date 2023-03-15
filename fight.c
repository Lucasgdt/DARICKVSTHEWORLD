#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "joueur.h"

#define ATTSPD 30







void fight(SDL_Renderer* renderer, SDL_Texture* characterTexture, SDL_Rect destRect, MOUSE_COORD mouse, coord_t dir) {
    // Charger la texture d'animation de combat
    if( dir.left )
      SDL_Surface* fightSurface = SDL_LoadBMP("fight_animation_left.bmp");
    else
      SDL_Surface* fightSurface = SDL_LoadBMP("fight_animation_right.bmp");
    
    SDL_Texture* fightTexture = SDL_CreateTextureFromSurface(renderer, fightSurface);
    SDL_FreeSurface(fightSurface);

    // Afficher la texture d'animation de combat
    SDL_RenderCopy(renderer, fightTexture, NULL, &destRect);
    SDL_RenderPresent(renderer);

    // Créer une hitbox dans la direction de la souris
    SDL_Rect hitbox;
    hitbox.w = 50;
    hitbox.h = 50;
    hitbox.x = mouse.x - hitbox.w/2;
    hitbox.y = mouse.y - hitbox.h/2;

    // Attendre un certain temps pour afficher l'animation de combat
    SDL_Delay(1000 / (ATTSPD * 15));

    // Afficher à nouveau la texture du personnage
    SDL_RenderCopy(renderer, characterTexture, NULL, &destRect);
    //SDL_RenderPresent(renderer);

    // Détruire la texture d'animation de combat
    SDL_DestroyTexture(fightTexture);
}
