
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"


int FocusScrollBox(Map_t * loaded_map, Sprite * sp)
{
    loaded_map->player = sp;
    return 0;
}

void ClampScroll(Map_t * loaded_map)
{
    if (loaded_map->xscroll < 0)
        loaded_map->xscroll = 0;
    if(loaded_map->yscroll < 0)
        loaded_map->yscroll = 0;
    if(loaded_map->xscroll > loaded_map->nb_tiles_larg * ZOOM - loaded_map->largeur_fenetre-1)
        loaded_map->xscroll = loaded_map->nb_tiles_larg * ZOOM - loaded_map->largeur_fenetre-1;
    if(loaded_map->yscroll > loaded_map->nb_tiles_long * ZOOM - loaded_map->hauteur_fenetre-1)
        loaded_map->yscroll = loaded_map->nb_tiles_long * ZOOM - loaded_map->hauteur_fenetre-1;
    

}

int UpdateScroll(Map_t * loaded_map)
{
    int cxperso, cyperso;
    
    cxperso = loaded_map->player->position.x + loaded_map->player->position.w/2;
    cyperso = loaded_map->player->position.y + loaded_map->player->position.h/2;


    loaded_map->xscroll = cxperso - (loaded_map->largeur_fenetre/2);
    loaded_map->yscroll = cyperso - (loaded_map->hauteur_fenetre/2);

    ClampScroll(loaded_map);
    return 0;
}

