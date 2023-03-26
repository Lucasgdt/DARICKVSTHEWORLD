#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "inventaire.h"
#include "outil.h"
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


objet_t * create_objet(){
    objet_t * objet = malloc(sizeof(objet_t));
    objet->as = 0;
    objet->armure = 0;
    objet->degats = 0;
    objet->mana = 0;
    objet->pv = 0;
    objet->regen = 0;
    objet->categorie = NULL;
    return objet;
}

/* Nombre d'elements */

extern 
int inventaire_nb_lire( inventaire_t * const inventaire )
{
  return(inventaire->taille);
} 

/* -- Acces individuel a un element */

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

inventaire_t * create_inventaire() {
    int i;
    inventaire_t * inventaire = malloc(sizeof(inventaire_t)*TAILLE_INV);
    inventaire->taille = TAILLE_INV;

    inventaire->liste = malloc(inventaire->taille * sizeof(inv_objet_t *));
    memset(inventaire->liste, 0, inventaire->taille * sizeof(inv_objet_t *));
    for (i = 0; i < TAILLE_INV; i++) {
        inventaire->liste[i] = malloc(sizeof(inv_objet_t));
        inventaire->liste[i]->id = -1;
    }
    // Initialisez les autres membres de inventaire_t ici
    return inventaire;
}

void loot(inventaire_t * joueur, objet_t * obj){
    int i;
    int temp;

    for (i = 0; i < TAILLE_INV; i++){
        if (joueur->liste[i]->id == -1){
            joueur->liste[i]->id = obj->id;
            joueur->liste[i]->nb = 1;
            temp = i;
            break;
        }
        else if(joueur->liste[i]->id != -1){
            if(joueur->liste[i]->id == obj->id){
                joueur->liste[i]->nb += 1;
            }
        }
        else if (i == TAILLE_INV - 1){
            printf("Inventaire pleins \n");
            exit(0);
        }
    }
    printf("Vous avez ramassez l'item suivant : %s à la case suivante : %d \n",liste_objets[joueur->liste[temp]->id-1].nom, temp);
}

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

void supprimer_objet_inv(inventaire_t * joueur, objet_t * obj){
    int i;
    int temp;
    for (i = 0; i<TAILLE_INV; i++){
        if (joueur->liste[i]->id != -1){ // Quelque chose à cette emplacement la ?
            if(joueur->liste[i]->id == obj->id){ // Est ce que l'id de l'objet qui est la à la meme que l'objet que l'on veut supprimer ?
                if (joueur->liste[i]->nb > 1){ // Si il y a plusieurs objets du meme type
                    joueur->liste[i]->nb -= 1;
                }
                else{
                    printf("Objet supprimer : %s \n",liste_objets[obj->id-1].nom);
                    joueur->liste[i]->id = -1;
                    joueur->liste[i]->nb = 0;
                    

                }
            }
        }
    }

}

int recherche_emplacement_item(inventaire_t * personnage, objet_t * obj){
    int i;
    for (i = 0; i<TAILLE_INV; i++){
        if(personnage->liste[i] != -1){
            if(personnage->liste[i]->id == obj->id){
                return i;
            }
        }
    }
}

void afficher_inv_SDL(SDL_Renderer * renderer, SDL_Texture * inventaire, SDL_Rect inv, inventaire_t * joueur, SDL_Surface * screenSurface, SDL_Window *window, personnage_t * perso){
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
            case SDL_BUTTON_RIGHT:
                SDL_GetMouseState(&x, &y);
                for (int i = 0;i <TAILLE_INV; i++){
                    if (x >= case_inv[i]->rect.x && x <= case_inv[i]->rect.x + case_inv[i]->rect.w && y >= case_inv[i]->rect.y && y <= case_inv[i]->rect.y + case_inv[i]->rect.h) {
                        if(joueur->liste[i]->id!=-1){
                            if(liste_objets[joueur->liste[i]->id-1].categorie == 0){
                                if(perso->arme_obj == NULL){
                                    SDL_RenderCopy(renderer,liste_objets[joueur->liste[i]->id-1].texture, NULL, &case_texture_HAUT);
                                    equiper(perso, joueur->liste[i], joueur);
                                }
                            }
                            if(liste_objets[joueur->liste[i]->id-1].categorie == 1){
                                if(perso->armure_obj == NULL){
                                    case_texture_BAS = IMG_LoadTexture(renderer, liste_objets[joueur->liste[i]->id-1].texture);
                                    equiper(perso, joueur->liste[i], joueur);
                                }
                            }
                        }
                    }
                }
                if (x >= case_HAUT.x && x <= case_HAUT.x + case_HAUT.w && y >= case_HAUT.y && y <= case_HAUT.y + case_HAUT.h) {
                    if(perso->arme_obj != NULL){
                        case_texture_HAUT = default_texture;
                        retirer(perso, perso->arme_obj, joueur);
                        afficher_inventaire(joueur);
                    }
                }
                if (x >= case_BAS.x && x <= case_BAS.x + case_BAS.w && y >= case_BAS.y && y <= case_BAS.y + case_BAS.h) {
                    if(perso->armure_obj != NULL){
                        case_texture_BAS = default_texture;
                        retirer(perso, perso->armure_obj, joueur);
                        afficher_inventaire(joueur);
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
        free(case_inv[i]);
    }
}