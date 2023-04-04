#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>
#include "joueur.h"
#include "mapstruct.h"
#include "environnement.h"
#include "mob.h"
#include "camera.h"
#include <math.h>

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
        mob_sdl[i]->position.x = 640 + 100 * i;
        mob_sdl[i]->position.y = 360 + 100 * i;
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

void anim(SDL_Renderer *renderer, Sprite * skin, personnage_t * joueur, Sprite * mob_sdl[TAILLE_LISTE_MOB], Map_t * map) {
    // Chargement des 6 images en tant que surfaces
	
    SDL_Surface* surfaces[6];
    if(joueur->arme_obj == NULL){
        return;
    }
    if(liste_objets[joueur->arme_obj->id-1].type == 0){
        for (int i = 0; i < 6; i++) {
            char filename[50];
            sprintf(filename, "ressources/perso/Anim/darickg%d.png", i+1);
            surfaces[i] = IMG_Load(filename);
        }
    }

    else if(liste_objets[joueur->arme_obj->id-1].type == 1){
        for (int i = 0; i < 6; i++) {
            char filename[50];
            sprintf(filename, "ressources/perso/Anim/darickdague%d.png", i+1);
            surfaces[i] = IMG_Load(filename);
        }
    } 

    else if(liste_objets[joueur->arme_obj->id-1].type == 4){
        for (int i = 0; i < 6; i++) {
            char filename[50];
            sprintf(filename, "ressources/perso/Anim/darickbaton%d.png", i+1);
            surfaces[i] = IMG_Load(filename);
        }
    }

    // Création des textures à partir des surfaces
    SDL_Texture* textures[6];
    for (int i = 0; i < 6; i++) {
        textures[i] = SDL_CreateTextureFromSurface(renderer, surfaces[i]);
    }

    // Libération des surfaces
    for (int i = 0; i < 6; i++) {
        SDL_FreeSurface(surfaces[i]);
    }

    // Boucle principale
    int running = 1;
    int current_image = 0;
    int temp = 0;
    SDL_Event event;
    while (temp < 6) {
        SDL_RenderClear(renderer);
		ShowMap(map, renderer);
        // Affichage de l'image courante
        skin->texture = textures[current_image];
        AfficherSprite(skin, renderer, skin->texture);

        for (int i = 0; i<TAILLE_LISTE_MOB; i++){
            AfficherSprite(mob_sdl[i], renderer, mob_sdl[i]->texture);
        }

        // Mise à jour de l'affichage
        SDL_RenderPresent(renderer);

        // Attente de 100 millisecondes
        SDL_Delay(100);

        // Passage à l'image suivante
        current_image = (current_image + 1) % 6;
        temp++;
    }

    // Libération des textures
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(textures[i]);
    }
}