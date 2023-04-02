#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mapstruct.h"

#ifndef ENV_H
#define ENV_H


#define TILES_X 50
#define TILES_Y 50
#define NB_TILES 12
#define ZOOM 64



SDL_Surface* LoadImage16(const char* img);
void LoadMap_tileset(Map_t* loaded_map);
void ErrorQuit(const char* ERROR);
void LoadMap_level(Index_t map, Map_t * loaded_map);
void LoadMapRect(Map_t * loaded_map);
Map_t * LoadMap(Index_t map);
int ShowMap(Map_t * loaded_map, SDL_Renderer* renderer);
int FreeMap(Map_t* loaded_map);


/* Généation de map aléatoire */
int min(int a, int b);
Index_t initialize_map();
void add_rooms(Index_t map);
void add_wall(Index_t map);
void add_end( Index_t map );
Index_t CreateMap();

#endif