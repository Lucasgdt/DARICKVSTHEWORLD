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

SDL_Point placement(Sprite * mob){
    int i, j;
    SDL_Point temp;

    do{
        temp.x = rand() % mob->m->nb_tiles_larg;
        temp.y = rand() % mob->m->nb_tiles_long;
    }while(mob->m->schema[temp.x][temp.y] != 1);
    return temp;
}

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
        MobPose = placement(mob_sdl[i]);
        mobx = MobPose.x;
        moby = MobPose.y;
        mob_sdl[i]->position.x = mobx * ZOOM;
        mob_sdl[i]->position.y = moby * ZOOM;
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
    int NB_TYPES_ARMES = 6;
    int MAX_IMAGES_ARMES = 11;
    int epee_baton = 6;
    int arc = 11;
    int dague = 7;
    int shuriken = 9;
    int poings = 8;
    int max_images = 0;
    // Tableau de textures pour chaque type d'arme
    SDL_Texture* animations[NB_TYPES_ARMES][MAX_IMAGES_ARMES];
    // Chargement des textures pour chaque type d'arme
    for (int i = 0; i < NB_TYPES_ARMES; i++) {
        if(joueur->arme_obj != NULL) {
            if(joueur->arme_obj->categorie == 0) max_images = epee_baton;
            if(joueur->arme_obj->categorie == 1) max_images = dague;
            if(joueur->arme_obj->categorie == 2) max_images = shuriken;
            if(joueur->arme_obj->categorie == 3) max_images = arc;
            if(joueur->arme_obj->categorie == 4) max_images = epee_baton;
        } else {
            if (i == 5) {
                max_images = poings;
            }
        }
        for (int j = 0; j < MAX_IMAGES_ARMES; j++) {
            if (j < max_images) {
                char filename[50];
                sprintf(filename, "ressources/perso/Anim/arme%d (%d).png", i, j+1);
                SDL_Surface* surface = IMG_Load(filename);
                animations[i][j] = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);
            } else {
                animations[i][j] = NULL;
            }
        }
    }

    // Boucle principale
    int running = 1;
    int current_image = 0;
    int temp = 0;
    SDL_Event event;
    SDL_Texture* texture;
    while (temp < 6) {
        
        SDL_RenderClear(renderer);
		ShowMap(map, renderer);
        // Affichage de l'image courante
        if(joueur->arme_obj == NULL){
            texture = animations[5][current_image];
        }
        else{
            texture = animations[liste_objets[joueur->arme_obj->id-1].type][current_image];
        }

        skin->texture = texture;
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
    SDL_DestroyTexture(texture);
}