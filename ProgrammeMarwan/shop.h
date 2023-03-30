#include <SDL2/SDL.h>
#include <SDL2/SDL_Image.h>

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
