#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef ENV_H
#define ENV_H


#define TILES_X 40
#define TILES_Y 40
#define NB_TILES 12
#define ZOOM 64

typedef struct TILE_S{
    SDL_Rect R;
    int mur;
}Tile_t;

typedef struct MAP_S{
    int LARGEUR_TILE, HAUTEUR_TILE;
    int nbtilesX, nbtilesY;
    SDL_Surface * surfacetile;
    SDL_Rect * tile;
    int ** schema;
    int nb_tiles_larg, nb_tiles_long;
    int largeur_fenetre, hauteur_fenetre;
    //scroll
    int xscroll, yscroll;
    SDL_Rect * player;
    SDL_Rect rectlimitscroll;
}Map_t;

typedef struct TILE_INDEX{
    int intmap[40][40];
    int tileX, tileY;
}Index_t;


SDL_Surface* LoadImage16(const char* img);
void LoadMap_tileset(Map_t* loaded_map);
void ErrorQuit(const char* ERROR);
void LoadMap_level(Index_t map, Map_t * loaded_map);
Tile_t ** LoadMapRect(Map_t * loaded_map);
Map_t * LoadMap(Index_t map);
int ShowMap(Map_t * loaded_map, SDL_Renderer* renderer, Tile_t ** Map_Rect);
int FreeMap(Map_t* loaded_map, Tile_t ** Map_Rect);


#endif