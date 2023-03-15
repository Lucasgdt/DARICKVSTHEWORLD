#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef ENV_H
#define ENV_H


#define TILES_X 40
#define TILES_Y 40
#define NB_TILES 12
#define SIZE_TILES 48

typedef struct TILE_MAP_S{
    SDL_Rect tile;
    int mur;
}TILE_MAP;





void INIT_MAP(TILE_MAP map[TILES_X][TILES_Y], SDL_Rect select_tile[NB_TILES]);
void LOAD_MAP(SDL_Renderer * renderer, SDL_Texture * tile_texture, SDL_Rect select_tile[NB_TILES], TILE_MAP map[TILES_X][TILES_Y], int tilemap[TILES_X][TILES_Y], SDL_Rect camera);






#endif