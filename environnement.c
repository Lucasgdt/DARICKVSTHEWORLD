
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"
#include "move.h"




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

    loaded_map->LARGEUR_TILE = loaded_map->HAUTEUR_TILE = 16;

    loaded_map->tile = malloc(loaded_map->nbtilesX*loaded_map->nbtilesY*sizeof(Tile_t));

    for(j=0,numtile=0; j < loaded_map->nbtilesY; j++ )
    {
        for(i = 0; i < loaded_map->nbtilesX; i++, numtile++ )
        {
            loaded_map->tile[numtile].R.w = loaded_map->LARGEUR_TILE;
            loaded_map->tile[numtile].R.h = loaded_map->HAUTEUR_TILE;
            loaded_map->tile[numtile].R.x = i*loaded_map->LARGEUR_TILE;
            loaded_map->tile[numtile].R.y = j*loaded_map->HAUTEUR_TILE;
            loaded_map->tile[numtile].mur = 0;
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
    loaded_map->nb_tiles_larg = map.tileX;
    loaded_map->nb_tiles_long = map.tileY;
    loaded_map->schema = map.intmap;
}

Map_t * LoadMap(Index_t map)
{
    Map_t * loaded_map;

    loaded_map = malloc(sizeof(Map_t));

    LoadMap_tileset(loaded_map);
    LoadMap_level(map, loaded_map);

    return(loaded_map);

}

int ShowMap(Map_t * loaded_map, SDL_Renderer* renderer)
{
    int i, j;
    SDL_Rect Rect_dest;
    SDL_Texture * tile_texture = NULL;
    tile_texture = SDL_CreateTextureFromSurface(renderer, loaded_map->surfacetile);

    for( i = 0 ; i < loaded_map->nb_tiles_larg ; i++ )
        for( j = 0 ; j < loaded_map->nb_tiles_long ; j++ )
            {   
                Rect_dest.x = i * loaded_map->LARGEUR_TILE;
                Rect_dest.y = j * loaded_map->HAUTEUR_TILE;
                Rect_dest.w = 16;
                Rect_dest.h = 16;
                switch(loaded_map->schema[i][j])
                {
                    case 1:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[0].R), &Rect_dest);
                        break;
                    case 2:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[1].R), &Rect_dest);
                        break;
                    case 3:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[2].R), &Rect_dest);
                        break;
                    case 4:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[3].R), &Rect_dest);
                        break;
                    case 5:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[4].R), &Rect_dest);
                        break;
                    case 6:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[5].R), &Rect_dest);
                        break;
                    case 7:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[6].R), &Rect_dest);
                        break;
                    case 8:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[7].R), &Rect_dest);
                        break;
                    case 9:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[8].R), &Rect_dest);
                        break;
                    case 10:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[9].R), &Rect_dest);
                        break;
                    case 11:
                        SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[10].R), &Rect_dest);
                        break;

                }
                
            }
    return 0;
    SDL_DestroyTexture(tile_texture);

}

int FreeMap(Map_t* loaded_map)
{
    int i;
    SDL_FreeSurface(loaded_map->surfacetile);
    for( i = 0 ; i < loaded_map->nb_tiles_long ; i++)
        free(loaded_map->schema[i]);
    //free(loaded_map->schema);
    free(loaded_map->tile);
    free(loaded_map);
    return 0;
}