#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "mapstruct.h"
#include "environnement.h"
#include "mob.h"
#include "camera.h"
#include <math.h>
#include "move.h"

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))
#define AGGRO_DISTANCE 300 // distance d'aggro en pixels


Sprite* InitialiserSprite(int x,int y,int w,int h, Map_t* map)
{
	Sprite* sp = malloc(sizeof(Sprite));
	sp->position.x = x;
	sp->position.y = y;
	sp->position.w = w;
	sp->position.h = h;
  sp->m = map;
	return sp;
}

void LibereSprite(Sprite* sp)
{
	free(sp);
}

void AfficherSprite(Sprite* perso,SDL_Renderer* renderer, SDL_Texture * skin)
{
	SDL_Rect R;
	R.x = perso->position.x - perso->m->xscroll;
	R.y = perso->position.y - perso->m->yscroll;
	R.w = perso->position.w;
	R.h = perso->position.h;
	SDL_RenderCopy(renderer, skin, NULL, &R);
}

int CollisionDecor(Sprite* perso, SDL_Rect test)
{
	int xmin,xmax,ymin,ymax,i,j;
	Map_t* m = perso->m;
	if (perso->position.x<0 || (perso->position.x + perso->position.w -1)>=m->nb_tiles_larg*ZOOM
	 || perso->position.y<0 || (perso->position.y + perso->position.h -1)>=m->nb_tiles_long*ZOOM)
		return 1;
	xmin = test.x / ZOOM;
	ymin = test.y / ZOOM;
	xmax = (test.x + test.w -1) / ZOOM;
	ymax = (test.y + test.h -1) / ZOOM;
	for(i=xmin;i<=xmax;i++)
	{
		for(j=ymin;j<=ymax;j++)
		{
			if (m->props[i][j].mur == 1)
				return 1;
            else if(m->props[i][j].mur == -1)
                return(-1);
		}
	}
	return 0;
}



int EssaiDeplacement(Sprite* perso,int vx,int vy)
{
	SDL_Rect test;
	test = perso->position;
	test.x+=vx;
	test.y+=vy;
	if (CollisionDecor(perso, test)==0)
	{
		perso->position = test;
		return 1;
	}
    if ( CollisionDecor(perso, test) == -1 ){
        perso->position = test;
        return -1;
    }
	return 0;
}

void Affine(Sprite* perso,int vx,int vy)
{
	int i;	
	for(i=0;i<ABS(vx);i++)
	{
		if (EssaiDeplacement(perso,SGN(vx),0)==0)
			break;
	}
	for(i=0;i<ABS(vy);i++)
	{
		if (EssaiDeplacement(perso,0,SGN(vy))==0)
			break;			
	}
}

int DeplaceSprite(Sprite* perso,int vx, int vy)
{
  
	if ( vx>=ZOOM || vy>=ZOOM )
	{
		DeplaceSprite(perso,vx/2,vy/2);
		DeplaceSprite(perso,vx-vx/2,vy-vy/2);
		return 3;
	}
	if (EssaiDeplacement(perso,vx,vy)==1)
		return 1;
    
    if (EssaiDeplacement(perso,vx,vy)==-1)
        return(-1);
	Affine(perso,vx,vy);
	return 2;
}

/**
 * @brief Fonction permettant de placer les mobs sur la carte, plus particulièrement dans la zone de jeu
 * 
 * @param mob 
 * @return SDL_Point 
 */

SDL_Point placement(Sprite * mob){
    int i, j;
    SDL_Point temp;

    do{
        temp.x = rand() % mob->m->nb_tiles_larg;
        temp.y = rand() % mob->m->nb_tiles_long;
    }while(mob->m->schema[temp.x][temp.y] != 1);
    return temp;
}

/**
 * @brief Fonction permettant d'initialiser chaque mob dans une liste, en mettant leurs tailles, leurs placements sur la carte, la carte, ainsi que leurs textures.
 * 
 * @param map 
 * @param renderer 
 * @param mob_liste 
 * @param mob_sdl 
 */

void init_mob(Map_t * map, SDL_Renderer * renderer, mob_liste_t * mob_liste, Sprite * mob_sdl[TAILLE_LISTE_MOB]){
	int i, j;
    int indice;
    int mobx, moby;
    SDL_Point MobPose;
	for (i = 0; i<TAILLE_LISTE_MOB; i++){
        mob_sdl[i] = malloc(sizeof(Sprite));
        mob_sdl[i]->position.h = DARICK_SIZE;
        mob_sdl[i]->position.w = DARICK_SIZE;
        mob_sdl[i]->texture = IMG_LoadTexture(renderer, liste_mobs[mob_liste->liste[i]->id-1].texture);
		mob_sdl[i]->m = map;
        mob_sdl[i]->position.x = 100;
        mob_sdl[i]->position.y = 100;
    }
}

/**
 * @brief Fonction permettant de supprimer complètement un mob dans une liste de Sprite
 * 
 * @param mob_sdl 
 */

void free_mob_sdl(Sprite * mob_sdl[TAILLE_LISTE_MOB]){
	for (int i = 0; i<TAILLE_LISTE_MOB; i++){
		free(mob_sdl[i]);
		mob_sdl[i] = NULL;
	}
}

/**
 * @brief Fonction permettant de faire déplacer un mob aléatoirement
 * 
 * @param mob 
 * @param i 
 */

void deplacement_mobV2(Sprite * mob[TAILLE_LISTE_MOB], int i){
    int deplacement;
    deplacement = rand()%5;

    if (deplacement == 1) {
		mob[i]->position.x +=1;
    }
    if (deplacement == 2) {
        mob[i]->position.x -=1;
    }
    if (deplacement == 3) {
        mob[i]->position.y +=1;
    }
    if (deplacement == 4) {
        mob[i]->position.y -=1;
    }
}


/**
 * @brief Fonction permettant de faire suivre un mob vers un joueur si le mob est assez proche du joueur
 * 
 * @param mob 
 * @param i 
 * @param destRect 
 */

void mob_aggro(Sprite *mob[TAILLE_LISTE_MOB], int i, SDL_Rect destRect) {
    int distance_x = abs(destRect.x - mob[i]->position.x);
    int distance_y = abs(destRect.y - mob[i]->position.y);
    int distance = sqrt(distance_x * distance_x + distance_y * distance_y);

    if (distance < AGGRO_DISTANCE) {
        // Si le joueur est à portée, le mob suit le joueur
        if (destRect.x < mob[i]->position.x) {
            mob[i]->position.x -= 1;
        }
        if (destRect.x > mob[i]->position.x) {
            mob[i]->position.x += 1;
        }
        if (destRect.y < mob[i]->position.y) {
            mob[i]->position.y -= 1;
        }
        if (destRect.y > mob[i]->position.y) {
            mob[i]->position.y += 1;
        }
    }
}

/**
 * @brief Fonction permettant de gérer la réaction d'un mob en vers en joueur à l'aide d'un calcul qui défini la distance entre un mob et un joueur. Soit le mob à un déplacement aléatoire, soit il suit le joueur
 * 
 * @param destRect 
 * @param mob_sdl 
 * @param mob_liste 
 * @param i 
 * @return int 
 */

int fonction_calcul(SDL_Rect destRect, Sprite * mob_sdl[TAILLE_LISTE_MOB], mob_liste_t * mob_liste, int i){
    int calcul;
    if(mob_liste->liste[i] != NULL){
        calcul = sqrt(pow(destRect.x - mob_sdl[i]->position.x, 2) + pow(destRect.y - mob_sdl[i]->position.y, 2));
    }

    if(calcul > 300){
        deplacement_mobV2(mob_sdl, i); // a utilisé uniquement quand le mob n'est pas à porter du joueur
    }
    else{
        mob_aggro(mob_sdl, i, destRect);
    }
    return calcul;
    }