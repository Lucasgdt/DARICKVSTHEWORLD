#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "inventaire.h"
#include "outil.h"
#include "mob.h"

extern objet_t liste_objets[];

/*
    TEST EFFECTUER : - Limite de la taille de l'inventaire, exemple : Si nous avez 20 items dans l'inventaire, et que je rajoute un 21 eme item, ça me met comme quoi l'inventaire est full
                     - Si on a 19 items, et que j'en rajoute un, tout fonctionne
                     - Le nom est bien print quand on demande, aucun soucis d'id ou quoi que ce soit
*/

/* for (i = 0; i < TAILLE_INV; i++){
        free(joueur->liste[i]);
    }
    free(joueur->liste);
    free(joueur);
    
    Au cas ou si jamais il faut libéré toute la mémoire de l'inventaire

    */


/**
 * @brief Fonction permettant d'initialiser la création d'un objet n'ayant aucune statistique
 * 
 * @return objet_t* 
 */

objet_t * create_objet(){
    objet_t * objet = malloc(sizeof(objet_t));
    objet->id = NULL;
    objet->as = 0;
    objet->degats = 0;
    objet->pv = 0;
    objet->categorie = NULL;
    objet->type = NULL;
    objet->distance = NULL;
    objet->taux = NULL;
    return objet;
}

/* Nombre d'elements */

/**
 * @brief Fonction uniquement pour aider, sert uniquement à lire la taille d'un inventaire
 * 
 * @param inventaire 
 * @return int 
 */

extern 
int inventaire_nb_lire( inventaire_t * const inventaire )
{
  return(inventaire->taille);
} 

/* -- Acces individuel a un element */

/**
 * @brief Fonction permettant de lire la case d'un inventaire, sert uniquement pour aider également
 * 
 * @param inventaire 
 * @param ind 
 * @return void* 
 */

extern 
void * inventaire_elem_lire( inventaire_t * const inventaire  , const int ind )
{
  if( (ind < 0) || (ind > inventaire_nb_lire(inventaire)-1 ) )
    {
      fprintf( stderr , "liste_elem_lire: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind , 0 , inventaire_nb_lire(inventaire)-1 );
      return(NULL);
    }

  return( inventaire->liste[ind] ) ;
}

/**
 * @brief Fonction permettant de créer un inventaire, d'initialiser un inventaire
 * 
 * @return inventaire_t* 
 */

inventaire_t * create_inventaire() {
    int i;
    inventaire_t * inventaire = malloc(sizeof(inventaire_t)*TAILLE_INV);
    inventaire->taille = TAILLE_INV;

    inventaire->liste = malloc(inventaire->taille * sizeof(inv_objet_t *));
    memset(inventaire->liste, 0, inventaire->taille * sizeof(inv_objet_t *));
    for (i = 0; i < TAILLE_INV; i++) {
        inventaire->liste[i] = malloc(sizeof(inv_objet_t));
        inventaire->liste[i]->id = -1;
        inventaire->liste[i]->nb = 0;
    }
    // Initialisez les autres membres de inventaire_t ici
    return inventaire;
}

/**
 * @brief Fonction permettant de vérifier si un inventaire est rempli 
 * 
 * @param personnage 
 * @return int 
 */

int inv_full(inventaire_t * personnage){
    int i, temp = 0;
    for (i = 0; i<TAILLE_INV; i++){
        if(personnage->liste[i]->id != -1){
            temp++;
        }
    }
    if (temp == TAILLE_INV){
        return 0;
    }
    else{
        return 1;
    }
}

/**
 * @brief Fonction permettant de donner un objet à un joueur en le placant dans son inventaire
 * 
 * @param joueur 
 * @param obj 
 */

void loot(inventaire_t * joueur, objet_t * obj){
    int i;
    int temp;

    for (i = 0; i < TAILLE_INV+1; i++){
        if(inv_full(joueur)==1){
            if (joueur->liste[i]->id == -1){
                joueur->liste[i]->id = obj->id;
                joueur->liste[i]->nb = 1;
                temp = i;
                break;
            }
            else if(joueur->liste[i]->id != -1){
                if(joueur->liste[i]->id == obj->id){
                    if(liste_objets[joueur->liste[i]->id-1].categorie == 2){
                        joueur->liste[i]->nb += 1;
                        temp = i;
                        break;
                    }
                }
            }
        }
        else{
            printf("Inventaire plein ! \n");
            return;
        }
    }
    printf("Vous avez ramassez l'item suivant : %s à la case suivante : %d \n",liste_objets[joueur->liste[temp]->id-1].nom, temp);
}

/**
 * @brief Fonction permettant d'afficher la liste complète du contenu de l'inventaire, uniquement dans la console
 * 
 * @param joueur 
 */

void afficher_inventaire(inventaire_t * joueur){
    int i;
    int temp = 0;
    printf("Votre inventaire : \n");
    for (i = 0; i<TAILLE_INV; i++){
        if (joueur->liste[i]->id != -1){
            printf("- %s \n",liste_objets[joueur->liste[i]->id-1].nom);
            temp++;
        }
    }
    if(temp == 0){
        printf("Vous n'avez rien dans votre inventaire \n");
    }
}

/**
 * @brief Fonction permettant de supprimer un objet en mémoire
 * 
 * @param obj 
 * @param obj_sdl 
 */

void free_objet(objet_t * obj, texture_t * obj_sdl){
    //free(obj);
    //obj = NULL;
    SDL_DestroyTexture(obj_sdl);
    obj_sdl = NULL;

}

/**
 * @brief Fonction permettant de supprimer un objet de l'inventaire du joueur à une case précise grâce à l'indice i
 * 
 * @param joueur 
 * @param obj 
 * @param i 
 * @param obj_sdl 
 */

void supprimer_objet_inv(inventaire_t * joueur, objet_t * obj, int i, texture_t * obj_sdl){
    int temp;
        if (joueur->liste[i]->id != -1){ // Quelque chose à cette emplacement la ?
            if(liste_objets[joueur->liste[i]->id-1].categorie == 2){ // Si obj = potion
                if(joueur->liste[i]->id == obj->id){ // Est ce que l'id de l'objet qui est la à la meme que l'objet que l'on veut supprimer ?
                    if (joueur->liste[i]->nb > 1){ // Si il y a plusieurs objets du meme type
                        joueur->liste[i]->nb -= 1;
                        printf("Objet supprimer : %s quantité restante : %d \n",liste_objets[obj->id-1].nom, joueur->liste[i]->nb);
                    }
                    else{
                        printf("Objet supprimer : %s \n",liste_objets[obj->id-1].nom);
                        joueur->liste[i]->id = -1;
                        joueur->liste[i]->nb = 0;
                        free_objet(obj, obj_sdl);
                    }
                }
            }
            else{ // Si obj = epee ou armure
                printf("Objet supprimer : %s \n",liste_objets[obj->id-1].nom);
                joueur->liste[i]->id = -1;
                joueur->liste[i]->nb = 0;
                free_objet(obj, obj_sdl);
            }
        }
}

/**
 * @brief Fonction permettant de donnée aléatoirement un objet provenant de la liste des objets de la base de donnée ayant en plus, le calcul en prenant compte le pourcentage de chance d'obtenir un objet
 * 
 * @param inventaire 
 */

void loot_mob(inventaire_t * inventaire, personnage_t * personnage){
    int choix;
    int argent;
    objet_t * obj = create_objet();
    int somme_taux = 0;
    // Calcule la somme des taux de chaque objet dans la liste
    for (int i = 1; i < 15; i++) {
        somme_taux += liste_objets[i].taux;
    }
    // Génère un nombre aléatoire entre 1 et la somme des taux
    choix = rand()%somme_taux + 1;
    argent = rand()%4;

    // Parcourt la liste des objets jusqu'à atteindre le taux correspondant au nombre aléatoire
    for (int i = 1; i < 16; i++) {
        choix -= liste_objets[i].taux;
        if (choix <= 0) {
            obj->id = liste_objets[i].id;
            break;
        }
    }

    if(argent == 1){
        printf("Pas d'argent \n");
    }
    if(argent == 2){
        printf("1 piece d'argent obtenu ! \n");
        personnage->argent += 1;
    }
    if(argent == 3){
        printf("2 piece d'argent obtenu ! \n");
        personnage->argent += 2;
    }
    if(argent == 4){
        printf("3 piece d'argent obtenu ! \n");
        personnage->argent += 3;
    }
    loot(inventaire, obj);
}

/**
 * @brief Fonction permettant d'afficher tout l'inventaire et d'agir avec tout en SDL, donc en liant visuel, et statistique.
 * 
 * @param renderer 
 * @param inventaire 
 * @param inv 
 * @param joueur 
 * @param screenSurface 
 * @param window 
 * @param perso 
 * @return int 
 */

int afficher_inv_SDL(SDL_Renderer * renderer, SDL_Texture * inventaire, SDL_Rect inv, inventaire_t * joueur, SDL_Surface * screenSurface, SDL_Window *window, personnage_t * perso){
    // Initialisation de SDL_ttf
    TTF_Init();
    TTF_Font * font = TTF_OpenFont("ressources/Font/font.ttf",24);
    SDL_Color color = {255, 255, 255, 255}; // Définir la couleur du texte
    char str[32];
    sprintf(str,"Piece : %d",perso->argent);
    SDL_Surface* surface = TTF_RenderText_Solid(font, str, color); // Créer une surface contenant le texte
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface); // Créer une texture à partir de la surface



    int pressed = 1;
    int x, y;
    SDL_Event event;

    SDL_Texture *default_texture = IMG_LoadTexture(renderer, "ressources/Inventaire/Inventory_Slot.png");
    SDL_Texture *default_texture_select = IMG_LoadTexture(renderer, "ressources/Inventaire/Inventory_select.png");

    int hauteur_case = 152;
    int largeur_case = 123; 

   texture_t * case_inv[TAILLE_INV];
    int temp_colonne = 0;
    int temp_ligne = 0;
    for (int i = 0; i<TAILLE_INV; i++){
        if(temp_colonne == 6){
            temp_colonne = 0;
            temp_ligne++;
        }
        case_inv[i] = malloc(sizeof(texture_t));
        case_inv[i]->rect.h = hauteur_case;
        case_inv[i]->rect.w = largeur_case;
        case_inv[i]->rect.x = 520 + 120 * temp_colonne;
        case_inv[i]->rect.y = 152 + 138 * temp_ligne;
        case_inv[i]->texture = NULL;
        case_inv[i]->surface = NULL;
        temp_colonne++;
    }

    SDL_Surface *case_texture_HAUT = NULL;
    SDL_Surface *case_texture_BAS = NULL;
    SDL_Surface *case_texture_HAUT_select = NULL;
    SDL_Surface *case_texture_BAS_select = NULL;

    SDL_Rect case_HAUT;
    SDL_Rect case_BAS;
    SDL_Rect case_HAUT_select;
    SDL_Rect case_BAS_select;






    case_HAUT_select.x = 36, case_HAUT_select.y = 150;
    case_HAUT.x = case_HAUT_select.x, case_HAUT.y = case_HAUT_select.y;

    case_BAS_select.x = 36, case_BAS_select.y = 290;
    case_BAS.x = case_BAS_select.x, case_BAS.y = case_BAS_select.y;
    
    case_HAUT_select.h = hauteur_case;
    case_HAUT.h = hauteur_case;
    case_BAS_select.h = hauteur_case;
    case_BAS.h = hauteur_case;

    case_HAUT_select.w = largeur_case;
    case_HAUT.w = largeur_case;
    case_BAS_select.w = largeur_case;
    case_BAS.w = largeur_case;

    SDL_UpdateWindowSurface(window);

    while (pressed){
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_i:
                pressed = 0;
                break;

            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_RIGHT){
                SDL_GetMouseState(&x, &y);
                for (int i = 0;i <TAILLE_INV; i++){
                    if (x >= case_inv[i]->rect.x && x <= case_inv[i]->rect.x + case_inv[i]->rect.w && y >= case_inv[i]->rect.y && y <= case_inv[i]->rect.y + case_inv[i]->rect.h) {
                        if(joueur->liste[i]->id!=-1){
                            if(liste_objets[joueur->liste[i]->id-1].categorie == 0){
                                if(perso->arme_obj == NULL){
                                    SDL_RenderCopy(renderer,liste_objets[joueur->liste[i]->id-1].texture, NULL, &case_texture_HAUT);
                                    equiper(perso, joueur->liste[i], joueur, i, case_inv[i]->texture);
                                    case_inv[i]->texture = NULL;
                                }
                            }
                            if(liste_objets[joueur->liste[i]->id-1].categorie == 1){
                                if(perso->armure_obj == NULL){
                                    SDL_RenderCopy(renderer,liste_objets[joueur->liste[i]->id-1].texture, NULL, &case_texture_BAS);
                                    equiper(perso, joueur->liste[i], joueur, i, case_inv[i]->texture);
                                    case_inv[i]->texture = NULL;
                                }
                            }
                            if(liste_objets[joueur->liste[i]->id-1].categorie == 2){
                                SDL_RenderCopy(renderer,liste_objets[joueur->liste[i]->id-1].texture, NULL, &case_texture_BAS);
                                equiper(perso, joueur->liste[i], joueur, i, case_inv[i]->texture);
                                case_inv[i]->texture = NULL;
                            }
                        }
                    }
                }
                if (x >= case_HAUT.x && x <= case_HAUT.x + case_HAUT.w && y >= case_HAUT.y && y <= case_HAUT.y + case_HAUT.h) {
                    if(perso->arme_obj != NULL){
                        if(inv_full(joueur)==0){
                            printf("Inventaire plein, veillez supprimer un objet de votre inventaire cliquant gauche sur l'objet \n");
                            return 0;
                        }
                        case_texture_HAUT = default_texture;
                        retirer(perso, perso->arme_obj, joueur);
                        afficher_inventaire(joueur);
                    }
                }
                if (x >= case_BAS.x && x <= case_BAS.x + case_BAS.w && y >= case_BAS.y && y <= case_BAS.y + case_BAS.h) {
                    if(perso->armure_obj != NULL){
                        if(inv_full(joueur)==0){
                            printf("Inventaire plein, veillez supprimer un objet de votre inventaire cliquant gauche sur l'objet \n");
                            return 0;
                        }
                        case_texture_BAS = default_texture;
                        retirer(perso, perso->armure_obj, joueur);
                        afficher_inventaire(joueur);
                    }
                }
            }
        else if (event.button.button == SDL_BUTTON_LEFT){
                SDL_GetMouseState(&x, &y);
                for (int i = 0;i <TAILLE_INV; i++){
                    if (x >= case_inv[i]->rect.x && x <= case_inv[i]->rect.x + case_inv[i]->rect.w && y >= case_inv[i]->rect.y && y <= case_inv[i]->rect.y + case_inv[i]->rect.h) {
                        if(joueur->liste[i]->id!=-1){
                            supprimer_objet_inv(joueur, joueur->liste[i], i, case_inv[i]->texture);
                        }
                    }
                }
        }

        case SDL_MOUSEMOTION:
        
            SDL_GetMouseState(&x, &y);
            for (int i = 0; i < TAILLE_INV; i++) {
                if (x >= case_inv[i]->rect.x && x <= case_inv[i]->rect.x + case_inv[i]->rect.w && y >= case_inv[i]->rect.y && y <= case_inv[i]->rect.y + case_inv[i]->rect.h) {
                    case_inv[i]->surface = default_texture_select;
                }
                else{
                    case_inv[i]->surface = NULL;
                }
            }
            if (x >= case_HAUT.x && x <= case_HAUT.x + case_HAUT.w && y >= case_HAUT.y && y <= case_HAUT.y + case_HAUT.h) {
                case_texture_HAUT_select = default_texture_select;
            }
            else{
                case_texture_HAUT_select = NULL;
            }

            if (x >= case_BAS.x && x <= case_BAS.x + case_BAS.w && y >= case_BAS.y && y <= case_BAS.y + case_BAS.h) {
                case_texture_BAS_select = default_texture_select;
            }
            else{
                case_texture_BAS_select = NULL;
            }

        default:
            break;
        }
        SDL_RenderClear(renderer);

        if(perso->arme_obj != NULL){
            case_texture_HAUT = IMG_LoadTexture(renderer, liste_objets[perso->arme_obj->id-1].texture);
        }
        if(perso->armure_obj != NULL){
            case_texture_BAS = IMG_LoadTexture(renderer, liste_objets[perso->armure_obj->id-1].texture);
        }



        SDL_SetRenderDrawColor(renderer, 0x4c, 0x30, 0x24, 0xFF);

        SDL_RenderCopy(renderer,inventaire, NULL, &inv);

        SDL_RenderCopy(renderer, case_texture_HAUT, NULL, &case_HAUT);
        SDL_RenderCopy(renderer, case_texture_HAUT_select, NULL, &case_HAUT_select);

        SDL_RenderCopy(renderer, case_texture_BAS, NULL, &case_BAS);
        SDL_RenderCopy(renderer, case_texture_BAS_select, NULL, &case_BAS_select);

        SDL_RenderCopy(renderer, texture, NULL, &(SDL_Rect){250, 500, surface->w, surface->h}); // Afficher la texture sur le rendu

        for(int i = 0; i<TAILLE_INV; i++){
            // Il rentre bien dedans aucun soucis
            if(joueur->liste[i]->id != -1){
                case_inv[i]->texture = IMG_LoadTexture(renderer, liste_objets[joueur->liste[i]->id-1].texture);
                SDL_RenderCopy(renderer, case_inv[i]->texture, NULL, &case_inv[i]->rect);
            }
        }
        for(int i = 0; i<TAILLE_INV; i++){
            SDL_RenderCopy(renderer, case_inv[i]->surface, NULL, &case_inv[i]->rect);
        }

        SDL_RenderPresent(renderer);

    }

    for (int i = 0; i<TAILLE_INV; i++){
        SDL_DestroyTexture(case_inv[i]->texture);
        free(case_inv[i]);
        case_inv[i] = NULL;
    }
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(case_texture_HAUT);
    case_texture_HAUT = NULL;
    SDL_DestroyTexture(case_texture_BAS);
    case_texture_BAS = NULL;
    TTF_CloseFont(font);
    TTF_Quit();
}