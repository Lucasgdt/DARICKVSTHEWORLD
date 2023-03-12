
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"


void INIT_MAP(SDL_Renderer * renderer, SDL_Rect tile[TILES_X][TILES_Y], SDL_Rect select_tile[NB_TILES]){


    
    for(int x = 0; x<TILES_X; x++){
        for(int y = 0; y<TILES_Y; y++){
            tile[x][y].x = x*32;
            tile[x][y].y = y*32;
            tile[x][y].w = 32;
            tile[x][y].h = 32;
        }
    }

    // Sol
    select_tile[0].x = 0;
    select_tile[0].y = 0;
    select_tile[0].w = 16;
    select_tile[0].h = 16;

    //Mur arriere
    select_tile[1].x = 16;
    select_tile[1].y = 0;
    select_tile[1].w = 16;
    select_tile[1].h = 16;

    //Mur devant
    select_tile[2].x = 32;
    select_tile[2].y = 0;
    select_tile[2].w = 16;
    select_tile[2].h = 16;

    //Mur gauche
    select_tile[3].x = 48;
    select_tile[3].y = 0;
    select_tile[3].w = 16;
    select_tile[3].h = 16;

    //Mur droit
    select_tile[4].x = 0;
    select_tile[4].y = 16;
    select_tile[4].w = 16;
    select_tile[4].h = 16;

    //Coin haut gauche
    select_tile[5].x = 16;
    select_tile[5].y = 16;
    select_tile[5].w = 16;
    select_tile[5].h = 16;

    //Coin haut droit
    select_tile[6].x = 32;
    select_tile[6].y = 16;
    select_tile[6].w = 16;
    select_tile[6].h = 16;

    //Mur haut arrete
    select_tile[7].x = 48;
    select_tile[7].y = 16;
    select_tile[7].w = 16;
    select_tile[7].h = 16;

    //Echelle
    select_tile[8].x = 0;
    select_tile[8].y = 32;
    select_tile[8].w = 16;
    select_tile[8].h = 16;

    //Coin bas gauche
    select_tile[9].x = 16;
    select_tile[9].y = 32;
    select_tile[9].w = 16;
    select_tile[9].h = 16;

    //Coin bas droit
    select_tile[10].x = 32;
    select_tile[10].y = 32;
    select_tile[10].w = 16;
    select_tile[10].h = 16;

}







void LOAD_MAP(SDL_Renderer * renderer, SDL_Texture * tile_texture, SDL_Rect select_tile[NB_TILES], SDL_Rect tile[TILES_X][TILES_Y], int tilemap[TILES_X][TILES_Y]){
    
    for(int x = 0; x < TILES_X; x++){
            for( int y = 0; y < TILES_Y; y++){
                switch( tilemap[x][y] )
                {
                    case 1:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[0], &tile[x][y]);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[1], &tile[x][y]);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[2], &tile[x][y]);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[3], &tile[x][y]);
                        break;
                    case 5:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[4], &tile[x][y]);
                        break;
                    case 6:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[5], &tile[x][y]);
                        break;
                    case 7:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[6], &tile[x][y]);
                        break;
                    case 8:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[7], &tile[x][y]);
                        break;
                    case 9:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[8], &tile[x][y]);
                        break;
                    case 10:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[9], &tile[x][y]);
                        break;
                    case 11:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[10], &tile[x][y]);
                        break;
                    case 12:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[11], &tile[x][y]);
                }
            }
        }

}