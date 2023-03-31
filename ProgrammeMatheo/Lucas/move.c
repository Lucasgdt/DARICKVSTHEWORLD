#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "move.h"
#include "outil.h"
#include "joueur.h"
#include "mapstruct.h"
#include "environnement.h"
#include "mob.h"

#define SGN(X) (((X)==0)?(0):(((X)<0)?(-1):(1)))
#define ABS(X) ((((X)<0)?(-(X)):(X)))

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
	int xmin,xmax,ymin,ymax,i,j,indicetile;
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
			if (m->props[i][j].mur)
				return 1;
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
	Affine(perso,vx,vy);
	return 2;
}

void init_mob(Map_t * map, SDL_Renderer * renderer, mob_liste_t * mob_liste, Sprite * mob_sdl[TAILLE_LISTE_MOB]){
	int i;
	for (i = 0; i<TAILLE_LISTE_MOB; i++){
        mob_sdl[i] = malloc(sizeof(Sprite));
        mob_sdl[i]->position.x = 640 + 10 * i;
        mob_sdl[i]->position.y = 360 + 10 * i;
        mob_sdl[i]->position.h = DARICK_SIZE;
        mob_sdl[i]->position.w = DARICK_SIZE;
        mob_sdl[i]->texture = IMG_LoadTexture(renderer, liste_mobs[mob_liste->liste[i]->id-1].texture);
		mob_sdl[i]->m = map;
    }
}

void free_mob_sdl(Sprite * mob_sdl[TAILLE_LISTE_MOB]){
	for (int i = 0; i<TAILLE_LISTE_MOB; i++){
		free(mob_sdl[i]);
		mob_sdl[i] = NULL;
	}
}

void deplacement_mobV2(Sprite * mob[TAILLE_LISTE_MOB], int i){
    int deplacement;
    deplacement = rand()%5;

    if (deplacement == 1) {
		DeplaceSprite(mob[i], 0, -1);
    }
    if (deplacement == 2) {
        DeplaceSprite(mob[i], 0, +1);
    }
    if (deplacement == 3) {
        DeplaceSprite(mob[i], -1, 0);
    }
    if (deplacement == 4) {
        DeplaceSprite(mob[i], 1, 0);
    }
}