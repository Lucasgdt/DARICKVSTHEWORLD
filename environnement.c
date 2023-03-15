
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"
#include "move.h"


void INIT_MAP(TILE_MAP map[TILES_X][TILES_Y], SDL_Rect select_tile[NB_TILES]){
    
    for(int x = 0; x<TILES_X; x++){
        for(int y = 0; y<TILES_Y; y++){
            map[x][y].tile.x = x*SIZE_TILES;
            map[x][y].tile.y = y*SIZE_TILES;
            map[x][y].tile.w = SIZE_TILES;
            map[x][y].tile.h = SIZE_TILES;
            map[x][y].mur = 0;
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







void LOAD_MAP(SDL_Renderer * renderer, SDL_Texture * tile_texture, SDL_Rect select_tile[NB_TILES], TILE_MAP map[TILES_X][TILES_Y], int tilemap[TILES_X][TILES_Y], SDL_Rect camera){
    int transpose[TILES_X][TILES_Y];
    // computing the transpose
    for (int i = 0; i < TILES_X; ++i)
        for (int j = 0; j < TILES_Y; ++j) {
            transpose[j][i] = tilemap[i][j];
    }
    tilemap = transpose;

    for(int x = 0; x < TILES_X; x++){
            for( int y = 0; y < TILES_Y; y++){

                switch( tilemap[x + camera.x][y + camera.y] )
                {
                    case 1:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[0], &map[x][y].tile);
                        map[x][y].mur = 0;
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[1], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[2], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[3], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 5:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[4], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 6:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[5], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 7:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[6], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 8:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[7], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 9:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[8], &map[x][y].tile);
                        map[x][y].mur = 0;
                        break;
                    case 10:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[9], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 11:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[10], &map[x][y].tile);
                        map[x][y].mur = 1;
                        break;
                    case 12:
                        SDL_RenderCopy(renderer, tile_texture, &select_tile[11], &map[x][y].tile);
                        map[x][y].mur = 1;
                }

            }
        }

}