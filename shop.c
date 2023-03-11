#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define NB_OBJET 15



typedef struct objet_boutique_s{
	int id;
	float pourcent_boutique;
	char * nom;
	int prix;
}objet_boutique_t;

static objet_boutique_t boutique_s[] = {
	{0, 0, "", 0},
	{1, 35, "Potion de vie", 8},
	{2, 12, "Potion de force", 12},
	{3, 12, "Potion d'agilité", 12},
	{4, 5, "Armure en cotte de maille", 20},
	{5, 5, "Armure de cuir renforcé", 25},
	{6, 10, "Armure de cuir", 18},
	{7, 10, "Renforcement de tissu", 15},
	{8, 3, "Cuirasse de sanglier", 30},
	{9, 0.5,"Panoplie de l'aventurier", 50},
	{10, 15, "Blindage abîmé", 10},
	{11, 20, "Protection du village", 5},
	{12, 100, "Plastron de guerrier", 18},
	{13, 15, "Epée du nain amélioré", 12},
	{14, 10, "Lame enragée de rantanplan", 25} 
};

int achat(int *po, int prixObj){
	int finalPo = *po - prixObj;
	return finalPo; 
}
int vendre(int *po, int id){ 
	int prix = boutique_s[id].prix / 10;
	int finalPo = *po + prix;
	return finalPo;
}


void apparition(objet_boutique_t *obj1, objet_boutique_t *obj2, objet_boutique_t *obj3, objet_boutique_t *obj4) {
    objet_boutique_t *tabObj = malloc(sizeof(objet_boutique_t) * 4);
    int i, k;
   /* Variable compObj à laquelle on va lui générer un id aléatoire en 1 et      15, la variable pourcentObj quant à elle récupèrera dans un tableau un pourcentages d'un des id générés aléatoirement, que l'on stockera dnas le tableau ci dessous "tab_pourcent"*/                                          
    int compObj;
    int pourcentObj;
  /* La variable cumul va accumuler chaque pourcentage de chaque id que l'on     va pour le nombre d'objets disponible, ajouter au tableau au fur et à        mesure */  
    int cumul;
    int cumulative_pourcent[NB_OBJET]; /* tableau des pourcentages cumulés */
    int tab_pourcent[NB_OBJET];
    int tabId[NB_OBJET];
  /*tabId est un tableau de tous id de chaque objet qui va être utiliser pour interdire l'apparition d'un meme objet, car chaque objet dans la boutique ne pas apparaitre en 1 seul exemplaire*/  

  /* Boucle for qui permet de remplir chaque tableau que l'on utilisera pour l'apparition des objets */ 
  srand(time(NULL));
    for (k = 1; k < NB_OBJET; k++) {
        tab_pourcent[k] = boutique_s[k].pourcent_boutique;
        tabId[k] = boutique_s[k].id;
        cumul += tab_pourcent[k];
        cumulative_pourcent[k] += cumul;
    }

    /* Première boucle pour chaque objet disponible, on lui génère aléatoirement un id, tant que l'id ne figure pas dans les id disponibles, alors on en regénère un tant que la condition n'est plus respecté.
Ainsi on récupère le pourcentage de l'objet selon son id, puis on vérifie si il est pas inférieur au pourcentage cumulé de celui ci, sinon on recommence*/

  /* une fois l'objet généré il faut attribuer pour chaque objet leurs valeurs, sleon l'itération de i*/
    for (i = 0; i < 4; i++) {
        
      do{
        compObj = rand() % NB_OBJET;
        compObj += 1;
        while(compObj != tabId[compObj]){
            compObj = rand() % NB_OBJET;
            compObj += 1;
        }
        pourcentObj = tab_pourcent[compObj];
      }while( pourcentObj < cumulative_pourcent[compObj] / cumul);
      pourcentObj = tab_pourcent[compObj];
      tabObj[i] = boutique_s[compObj];
        tabId[compObj] = 0;
        switch (i) {
            case 0:
                *obj1 = tabObj[0];
                break;
            case 1:
                *obj2 = tabObj[1];
                break;
            case 2:
                *obj3 = tabObj[2];
                break;
            case 3:
                *obj4 = tabObj[3];
                break;
        }
    }

    free(tabObj);
}

void boutique(){
	objet_boutique_t *obj1, *obj2, *obj3, *obj4;
	obj1 = malloc(sizeof(objet_boutique_t));
	obj2 = malloc(sizeof(objet_boutique_t));
	obj3 = malloc(sizeof(objet_boutique_t));
	obj4 = malloc(sizeof(objet_boutique_t));
	apparition(obj1, obj2, obj3, obj4);
  printf("\n%s, %s, %s, %s \n", obj1->nom,obj2->nom,obj3->nom,obj4->nom);

  printf("Bienvenue dans la boutique cher Darick ! \nz"); 
  printf("  Voici les items du jours ! \n")
  printf("\n%s, %s, %s, %s \n", obj1->nom,obj2->nom,obj3->nom,obj4->nom);
  switch()
	free(obj1);
	free(obj2);
	free(obj3);
	free(obj4);


  void boutique() {
  // Initialiser SDL
  SDL_Init(SDL_INIT_VIDEO);

  // Créer une fenêtre
  SDL_Window* window = SDL_CreateWindow("Boutique", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);

  // Créer un rendu
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  // Charger une image pour le bouton "acheter"
  SDL_Surface* acheterSurface = SDL_LoadBMP("acheter.bmp");
  SDL_Texture* acheterTexture = SDL_CreateTextureFromSurface(renderer, acheterSurface);
  SDL_FreeSurface(acheterSurface);

  // Charger une image pour le bouton "vendre"
  SDL_Surface* vendreSurface = SDL_LoadBMP("vendre.bmp");
  SDL_Texture* vendreTexture = SDL_CreateTextureFromSurface(renderer, vendreSurface);
  SDL_FreeSurface(vendreSurface);

  // Boucle principale
  SDL_Event event;
  bool running = true;
  while (running) {
    // Gérer les événements
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        // Vérifier si l'utilisateur a cliqué sur le bouton "acheter"
        if (event.button.x >= 100 && event.button.x < 300 && event.button.y >= 200 && event.button.y < 300) {
          acheter(); // Appeler la fonction pour acheter un objet
        }
        // Vérifier si l'utilisateur a cliqué sur le bouton "vendre"
        else if (event.button.x >= 350 && event.button.x < 550 && event.button.y >= 200 && event.button.y < 300) {
          vendre(); // Appeler la fonction pour vendre un objet
        }
      }
    }

    // Effacer l'écran
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Afficher les boutons "acheter" et "vendre"
    SDL_Rect acheterRect = {100, 200, 200, 100};
    SDL_Rect vendreRect = {350, 200, 200, 100};
    SDL_RenderCopy(renderer, acheterTexture, NULL, &acheterRect);
    SDL_RenderCopy(renderer, vendreTexture, NULL, &vendreRect);

    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer);
  }

  // Libérer les ressources
  SDL_DestroyTexture(acheterTexture);
  SDL_DestroyTexture(vendreTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
}

int main(){
    boutique();

	return 0;
}




