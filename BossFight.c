#include <stdlib.h>
#include <stdio.h>
#include "boss.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define TAILLE_MAX 20


typedef struct boss_s{
    int id;
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int armure;
    int regen;
    int as;
    int pv;
    int mana;
}boss_t;

boss_t boss[] = {
    {0,"","",0,0,0,0,0,0},
    {1,"Gabil'baraz","",1,2,0.5,30},
    {2,"Bund'zigl","",2,4,2,20},
    {3,"Uzn'gor","",1,},
    {4,"Ayoub, le nain dechu","",0,0,0,0}
};

void deplacementSerpent(){
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    SDL_Rect boss_rect;
    int textureHauteur, textureLargeur;
    tmp = IMG_LOAD("boss/boss.png");
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return 0;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp); /* On libère la surface, on n’en a plus besoin */
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return 0;
    }
    SDL_QueryTexture(texture, NULL, NULL,&textureHauteur, &textureLargeur);
    boss_rect.x = 100;
    boss_rect.y = 100;
    boss_rect.h = textureHauteur;
    boss_rect.y = textureLargeur;
  
    for(int i = 0; i < TAILLE_MAX: i++)
        for(int j = 0; j<TAILLE_MAX)
        SDL_Renderclear(render);
        SDL_Rendercopy(render, texture, NULL, &boss_rect);
        SDL_RenderPresent(renderer);
        boss_rect.x += 1;
        boss_rect.y += 1;
    }
    
}

int main(){
    deplacementSerpent();
}