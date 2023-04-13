
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "environnement.h"

/**
 * @brief Permet de fixer la caméra sur le joueur
 * @author Lucas
 * @param loaded_map 
 * @param sp 
 * @return int 
 */

int FocusScrollBox(Map_t * loaded_map, Sprite * sp)
{
    loaded_map->player = sp;
    return 0;
}

/**
 * @brief Bloque la caméra aux limites de la map
 * @author Lucas
 * @param loaded_map 
 */

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

/**
 * @brief Actualise la position de la caméra en fonction de celle du joueur
 * @author Lucas
 * @param loaded_map 
 * @return int 
 */

int UpdateScroll(Map_t * loaded_map)
{
    // Ajout de cxmob et cymob afin d'avoir la meme vitesse que le joueur
    int cxperso, cyperso, cxmob, cymob;
    
    cxperso = loaded_map->player->position.x + loaded_map->player->position.w/2;
    cyperso = loaded_map->player->position.y + loaded_map->player->position.h/2;
/*
    cxmob = loaded_map->player->position.x + loaded_map->player->position.w/2;
    cymob = loaded_map->player->position.y + loaded_map->player->position.h/2;
*/
    loaded_map->xscroll = cxperso - (loaded_map->largeur_fenetre/2);
    loaded_map->yscroll = cyperso - (loaded_map->hauteur_fenetre/2);
/*
    loaded_map->xscroll = cxmob - (loaded_map->largeur_fenetre/2);
    loaded_map->yscroll = cymob - (loaded_map->hauteur_fenetre/2);
*/
    ClampScroll(loaded_map);
    return 0;
}

