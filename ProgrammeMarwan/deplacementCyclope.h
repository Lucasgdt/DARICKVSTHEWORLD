#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#ifndef CYCLOPE_H
#define CYCLOPE_H

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define speed 30

typedef struct partboss_s{
    SDL_Texture * texture;
    SDL_Rect *boss_rect;
}partboss_t;



extern void deplacementCyclope(SDL_Window *window);


#endif