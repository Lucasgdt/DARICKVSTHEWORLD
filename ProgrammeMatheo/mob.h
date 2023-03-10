#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TAILLE_MAX 256
#define TAILLE_LISTE_MOB 100

typedef struct mob_s{
    int id;
    char nom[TAILLE_MAX];
    char texture[TAILLE_MAX];
    int degats;
    int armure;
    int regen;
    int as;
    int pv;
    int mana;
}mob_t;

typedef struct mob_liste_s{
    int taille;
    mob_t ** liste;
}mob_liste_t;

// Liste total des objects du jeu
static mob_t liste_mobs[] = {
    {1, "Gobelin", "gobelin.png", 1, 0, 0, 1, 20, 0},
    {2, "Gnome", "daricksword.png", 1, 10, 0, 1, 20, 300},
    {3, "Azir", "daricksword.png", 1, 20, 0, 1, 200, 0}
};

mob_t * create_mob();
void afficher_stat_mob(mob_t * mob);
void delete_mob(mob_liste_t * liste_des_mobs, mob_t * mob);
int mob_existe(mob_t * mob);
mob_liste_t * create_liste_mob();
mob_liste_t * ajouter_mob(mob_liste_t * liste_des_mobs, mob_t * mob);
mob_t * ajuste(mob_t * mob);
void afficher_liste_mob(mob_liste_t * liste);