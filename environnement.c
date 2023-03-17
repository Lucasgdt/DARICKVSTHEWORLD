#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"
#include "move.h"
#include "camera.h"



SDL_Surface* LoadImage16(const char* img)
{

    SDL_Surface* image_ram = IMG_Load(img); // Charge l'image
    return image_ram;
}

void LoadMap_tileset(Map_t* loaded_map){
    int numtile, i, j;

    loaded_map->surfacetile = LoadImage16("ressources/map/tiles_map.png");
    loaded_map->nbtilesX = 4;
    loaded_map->nbtilesY = 3;
    loaded_map->largeur_fenetre = SCREEN_WIDTH;
    loaded_map->hauteur_fenetre = SCREEN_HEIGHT;
    loaded_map->xscroll = 0;
    loaded_map->yscroll = 0;

    loaded_map->LARGEUR_TILE = loaded_map->HAUTEUR_TILE = 16;

    loaded_map->tile = malloc(loaded_map->nbtilesX*loaded_map->nbtilesY*sizeof(Tile_t));

    for(j=0,numtile=0; j < loaded_map->nbtilesY; j++ )
    {
        for(i = 0; i < loaded_map->nbtilesX; i++, numtile++ )
        {
            loaded_map->tile[numtile].w = loaded_map->LARGEUR_TILE;
            loaded_map->tile[numtile].h = loaded_map->HAUTEUR_TILE;
            loaded_map->tile[numtile].x = i*loaded_map->LARGEUR_TILE;
            loaded_map->tile[numtile].y = j*loaded_map->HAUTEUR_TILE;
        }
    }
}

void ErrorQuit(const char* ERROR)
{
    puts(ERROR);
    SDL_Quit();
    system("pause");
    exit(-1);
}


void LoadMap_level(Index_t map, Map_t * loaded_map)
{
    int i, j;
    loaded_map->nb_tiles_larg = map.tileX;
    loaded_map->nb_tiles_long = map.tileY;
    loaded_map->schema = (int **) malloc(loaded_map->nb_tiles_larg*sizeof(int*));
    for(i = 0; i < loaded_map->nb_tiles_larg; i++)
        loaded_map->schema[i] = (int *) malloc(loaded_map->nb_tiles_long*sizeof(int));
    
    for ( i = 0 ; i < loaded_map->nb_tiles_larg ; i++ ){
        for( j = 0 ; j < loaded_map->nb_tiles_long ; j++ ){
            loaded_map->schema[j][i] = map.intmap[i][j];
        }
    }

}
Tile_t ** LoadMapRect(Map_t * loaded_map)
{
    Tile_t ** Map_Rect = NULL;
    Map_Rect = (Tile_t **) malloc(loaded_map->nb_tiles_larg*sizeof(Tile_t*));
    for(int i = 0 ; i < loaded_map->nb_tiles_larg ; i++ ){
        Map_Rect[i] = (Tile_t *) malloc(loaded_map->nb_tiles_long*sizeof(Tile_t));
        }
    return(Map_Rect);
}

Map_t * LoadMap(Index_t map)
{
    Map_t * loaded_map;

    loaded_map = malloc(sizeof(Map_t));

    LoadMap_tileset(loaded_map);
    LoadMap_level(map, loaded_map);

    return(loaded_map);

}


int ShowMap(Map_t * loaded_map, SDL_Renderer* renderer, Tile_t ** Map_Rect)
{
    int i, j;
    int minx = 0,maxx,miny = 0,maxy;
    SDL_Texture * tile_texture = NULL;
    tile_texture = SDL_CreateTextureFromSurface(renderer, loaded_map->surfacetile);

    UpdateScroll(loaded_map);


    minx = ( loaded_map->xscroll / ZOOM ) - (minx > 0);
    miny = ( loaded_map->yscroll / ZOOM ) - (miny > 0);
    maxx = ((loaded_map->xscroll + loaded_map->largeur_fenetre)/ZOOM) + 1;
    maxy = ((loaded_map->yscroll + loaded_map->hauteur_fenetre)/ZOOM) + 1;

    for( i = minx ; i < maxx ; i++ )
        for( j = miny ; j < maxy ; j++ )
            {   
                
                Map_Rect[i][j].R.x = i * ZOOM - loaded_map->xscroll;
                Map_Rect[i][j].R.y = j * ZOOM - loaded_map->yscroll;
                Map_Rect[i][j].R.w = ZOOM;
                Map_Rect[i][j].R.h = ZOOM;

                if(i < 0 || i >= loaded_map->nb_tiles_larg || j < 0 || j >= loaded_map->nb_tiles_long)
                    SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[11]), &(Map_Rect[i][j].R));
                else{
                    
                    switch(loaded_map->schema[i][j])
                    {
                        case 1:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[0]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 0;
                            break;
                        case 2:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[1]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 3:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[2]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 4:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[3]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 5:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[4]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 6:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[5]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 7:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[6]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 8:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[7]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 9:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[8]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 0;
                            break;
                        case 10:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[9]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;
                        case 11:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[10]), &(Map_Rect[i][j].R));
                            Map_Rect[i][j].mur = 1;
                            break;

                    }   
                }
            }
    return 0;
    SDL_DestroyTexture(tile_texture);

}

int FreeMap(Map_t * loaded_map, Tile_t ** Map_Rect)
{
    int i;
    SDL_FreeSurface(loaded_map->surfacetile);
    for( i = 0 ; i < loaded_map->nb_tiles_long ; i++)
        free(loaded_map->schema[i]);
    free(loaded_map->schema);
    free(loaded_map->tile);
    free(loaded_map);
    for( i = 0 ; i < loaded_map->nb_tiles_long ; i++)
        free(Map_Rect[i]);
    free(Map_Rect);

    return 0;
}

