typedef struct objet_boutique_s{
	int id;
	float pourcent_boutique;
	char * Nom;
	int prix;
}objet_boutique_t;

#define NB_OBJET 15


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
	{12, 8, "Plastron de guerrier", 18},
	{13, 15, "Epée du nain amélioré", 12},
	{14, 10, "Lame enragée de rantanplan", 25} 
}

int achat(int *po, int prixObj){
	int finalPo = *po - prixObj;
	return finalPo;
}

int vendre(int *po, int id){
	objet_boutique_t *objet; 
	int prix = objet->boutique_s[id].prix / 10
	int finalPo = *po + prix;
	return finalPo
}


void apparition(objet_boutique_t obj1, objet_boutique_t obj2, objet_boutique_t obj3, objet_boutique_t obj4){
	objet_boutique_t *pourcent;
	int i, j;
	int comp1, comp2, comp3;
	float pourcent;
	float tab_pourcent[NB_OBJET]; 
	for( i = 1; i < NB_OBJET; i++){
		tab_pourcent[i-1] = pourcent->boutique_s[i].pourcent_boutique;
	}
	// j < 4, car on veut tirer aléatoirement 4 objets
	for( j = 0; i<4; i++){
		for( i = 0; i< NB_OBJET; i++ ){
			comp3 = (int)rand()/RAND_MAX*15
			while(comp3 == 0) (int)rand()/RAND_MAX*15;
			comp1 = (float)rand()/RAND_MAX*100; 	 
			comp2 = (float)rand()/RAND_MAX*100;
			pourcent = tab_pourcent[comp3]; 
			if( comp1 < pourcent && pourcent < comp2){
				obj1 
			}
		}
	}	
}
void boutique(...){
	objet_boutique_t obj1, obj2, obj3, obj4
	apparition(obj1 	

}






