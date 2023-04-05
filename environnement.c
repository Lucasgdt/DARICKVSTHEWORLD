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
            loaded_map->schema[i][j] = map.intmap[i][j];
        }
    }

}
void LoadMapRect(Map_t * loaded_map)
{
    loaded_map->props = (Tile_t **) malloc(loaded_map->nb_tiles_larg*sizeof(Tile_t*));
    for(int i = 0 ; i < loaded_map->nb_tiles_larg ; i++ ){
        loaded_map->props[i] = (Tile_t *) malloc(loaded_map->nb_tiles_long*sizeof(Tile_t));
        }
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
                
                loaded_map->props[i][j].R.x = i * ZOOM - loaded_map->xscroll;
                loaded_map->props[i][j].R.y = j * ZOOM - loaded_map->yscroll;
                loaded_map->props[i][j].R.w = ZOOM;
                loaded_map->props[i][j].R.h = ZOOM;
                
                if(i < 0 || i >= loaded_map->nb_tiles_larg || j < 0 || j >= loaded_map->nb_tiles_long)
                    SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[11]), &(loaded_map->props[i][j].R));
                else{
                    
                    switch(loaded_map->schema[i][j])
                    {
                        case 1:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[0]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 0;
                            break;
                        case 2:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[1]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 3:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[2]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 4:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[3]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 5:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[4]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 6:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[5]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 7:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[6]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 8:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[7]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 9:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[8]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 0;
                            break;
                        case 10:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[9]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;
                        case 11:
                            SDL_RenderCopy(renderer, tile_texture, &(loaded_map->tile[10]), &(loaded_map->props[i][j].R));
                            loaded_map->props[i][j].mur = 1;
                            break;

                    }   
                }
            }
    return 0;
    SDL_DestroyTexture(tile_texture);

}


/*  Initialisation du map remplis de vide  */
Index_t initialize_map() {
    Index_t map;
    int i, j;

    map.tileX = (rand() % 40 ) + 50 ;
    map.tileY = map.tileX ;

    map.num_room = map.tileX / 15;


    map.intmap = (int **) malloc(map.tileX*sizeof(int*));
    for(int i = 0 ; i < map.tileX ; i++ ){
        map.intmap[i] = (int *) malloc(map.tileY*sizeof(int));
    }

    for(i = 0; i < map.tileX; i++){
        for(j = 0; j < map.tileY; j++){
            map.intmap[i][j] = 0;
        }
    }

    return map;
}

/*  Créations de "pièces" de taille et position aléatoire */
void add_rooms(Index_t map) {

    room * salles = malloc(sizeof(room) * map.num_room);

    salles[0].room_width = (rand() % 10 ) + 5;
    salles[0].room_height = (rand() % 10 ) + 5;
    salles[0].x = 3;
    salles[0].y = 3;
    for (int j = salles[0].x; j < salles[0].x + salles[0].room_width; j++) {
        for (int k = salles[0].y; k < salles[0].y + salles[0].room_height; k++) {
            map.intmap[j][k] = 1;
        }
    }

    for (int i = 1; i < map.num_room; i++) {
        salles[i].room_width = (rand() % 5 ) + 10;
        salles[i].room_height = (rand() % 5 ) + 10;


        salles[i].x = salles[i-1].x + rand() % salles[i-1].room_width ;
        salles[i].y = salles[i-1].y + rand() % salles[i-1].room_height  ;

        for (int j = salles[i].x; j < salles[i].x + salles[i].room_width; j++) {
            for (int k = salles[i].y; k < salles[i].y + salles[i].room_height; k++) {
                map.intmap[j][k] = 1;
            }
        }
    }


    free(salles);
}



/* Création des murs */
void add_wall(Index_t map){

        for(int i = 1 ; i < map.tileX - 1 ; i++){
            for(int j = 1 ; j < map.tileY - 1 ; j++){
            
                if(map.intmap[i][j] == 0){
                    if( ( map.intmap[i][j+1] == 1 ) && ( map.intmap[i][j-1] != 1 ) )
                        map.intmap[i][j] = 2;
                    else if( map.intmap[i][j-1] == 1 )
                        map.intmap[i][j] = 3;
                    
                    else if( ( ( map.intmap[i-1][j] == 1 ) || ( map.intmap[i-1][j] == 2 ) ) && ( ( map.intmap[i][j-1] == 0 ) || ( map.intmap[i][j-1] == 5 ) || ( map.intmap[i][j-1] == 3 ) ) ){
                        if(map.intmap[i+1][j] != 1)
                            map.intmap[i][j] = 5;
                        else
                            map.intmap[i][j] = 2;
                    }
                    else if( ( ( map.intmap[i+1][j] == 1 ) || ( map.intmap[i+1][j] == 2 ) ) && ( ( map.intmap[i][j-1] == 0 ) || ( map.intmap[i][j-1] == 4 ) || ( map.intmap[i][j-1] == 3 ) ) ){
                        if(map.intmap[i-1][j] != 1)
                            map.intmap[i][j] = 4;
                        else
                            map.intmap[i][j] = 2;
                    }
                }
            }
        }

        for(int i = 1 ; i < map.tileX - 1 ; i++){
            for(int j = 1 ; j < map.tileY - 1 ; j++){
                if( map.intmap[i][j] == 0 ){

                    if( ( map.intmap[i+1][j+1] == 1 ) && ( map.intmap[i+1][j] == 8 ) && ( map.intmap[i][j+1] == 4 ) )
                            map.intmap[i][j] = 6;
                    else if( ( map.intmap[i-1][j+1] == 1 ) && ( map.intmap[i-1][j] == 8 ) && ( map.intmap[i][j+1] == 5 ) )
                        map.intmap[i][j] = 7;
                    else if( map.intmap[i][j+1] == 2 )
                        map.intmap[i][j] = 8;
                    else if( ( map.intmap[i-1][j-1] == 1 ) && ( map.intmap[i-1][j] == 3 ) && ( map.intmap[i][j-1] == 4 ) )
                        map.intmap[i][j] = 10;
                    else if( ( map.intmap[i+1][j-1] == 1 ) && ( map.intmap[i+1][j] == 3 ) && ( map.intmap[i][j-1] == 5 ) )
                        map.intmap[i][j] = 11;
                }
            }
        }
}

/* Création de la case de fin */
void add_end( Index_t map ){
    int x = map.tileX - 1; 
    int y = map.tileY - 1;
    int i;

    for(i = map.tileY; map.intmap[x][y] != 1; i--){
        x = rand() % (map.tileX - 2) + 2;
        y = i - rand() % 3 ;
    }
    
    map.intmap[x][y] = 9;
}
void UpdateMap(Index_t map){
    add_rooms(map);
    add_wall(map);
    add_end(map);
}

int FreeMap(Map_t * loaded_map)
{
    int i;
    SDL_FreeSurface(loaded_map->surfacetile);
    for( i = 0 ; i < loaded_map->nb_tiles_long ; i++)
        free(loaded_map->schema[i]);
    free(loaded_map->schema);
    free(loaded_map->tile);
    free(loaded_map);
    for( i = 0 ; i < loaded_map->nb_tiles_long ; i++)
        free(loaded_map->props[i]);
    free(loaded_map->props);

    return 0;
}