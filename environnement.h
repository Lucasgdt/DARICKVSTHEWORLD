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

typedef struct TILE_S{
    SDL_Rect R;
    int mur;
}Tile_t;

typedef struct MAP_S{
    int LARGEUR_TILE, HAUTEUR_TILE;
    int nbtilesX, nbtilesY;
    SDL_Surface * surfacetile;
    Tile_t * tile;
    int ** schema;
    int nb_tiles_larg, nb_tiles_long;
    
}Map_t;

typedef struct TILE_INDEX{
    int ** intmap;
    int tileX, tileY;
}Index_t;


SDL_Surface* LoadImage16(const char* img);
void LoadMap_tileset(Map_t* loaded_map);
void ErrorQuit(const char* ERROR);
void LoadMap_level(Index_t map, Map_t * loaded_map);
Map_t * LoadMap(Index_t map);
int ShowMap(Map_t * loaded_map, SDL_Renderer* renderer);
int FreeMap(Map_t* loaded_map);


#endif