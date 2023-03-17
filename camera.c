
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"


int FocusScrollBox(Map_t * loaded_map, SDL_Rect * player, int x, int y, int w, int h)
{
    loaded_map->player = player;
    loaded_map->rectlimitscroll.x = x;
    loaded_map->rectlimitscroll.y = y;
    loaded_map->rectlimitscroll.w = w;
    loaded_map->rectlimitscroll.h = h;
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
    int cxperso, cyperso, xlimmin, xlimmax, ylimmin, ylimmax;
    
    cxperso = loaded_map->player->x + loaded_map->player->w/2;
    cyperso = loaded_map->player->y + loaded_map->player->h/2;
    xlimmin = loaded_map->xscroll + loaded_map->rectlimitscroll.x;
    ylimmin = loaded_map->yscroll + loaded_map->rectlimitscroll.y;
    xlimmax = xlimmin + loaded_map->rectlimitscroll.w;
    ylimmax = xlimmin + loaded_map->rectlimitscroll.h;

    if( cxperso < xlimmin )
        loaded_map->xscroll -= (xlimmin-cxperso);
    if( cxperso < ylimmin )
        loaded_map->yscroll -= (ylimmin-cyperso);
    if( cxperso > xlimmax )
        loaded_map->xscroll += (cxperso-xlimmax);
    if(cyperso > ylimmax )
        loaded_map->yscroll += (cyperso-ylimmax);
    ClampScroll(loaded_map);
    return 0;
}
