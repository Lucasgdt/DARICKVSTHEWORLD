
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#ifndef MAP_STRUCT
#define MAP_STRUCT

typedef struct
{
	struct MAP_S* m;
	SDL_Rect position;
} Sprite;

typedef struct coord_s{
    int up;
    int down;
    int left;
    int right;
}coord_t;

typedef struct TILE_S{
    SDL_Rect R;
    int mur;
}Tile_t;

typedef struct MAP_S{
    int LARGEUR_TILE, HAUTEUR_TILE;
    int nbtilesX, nbtilesY;
    Tile_t ** props;
    SDL_Surface * surfacetile;
    SDL_Rect * tile;
    int ** schema;
    int nb_tiles_larg, nb_tiles_long;
    int largeur_fenetre, hauteur_fenetre;
    //scroll
    int xscroll, yscroll;
    Sprite* player;
    SDL_Rect rectlimitscroll;
}Map_t;

typedef struct TILE_INDEX{
    int intmap[40][40];
    int tileX, tileY;
}Index_t;


#endif