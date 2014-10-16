/**retourne si le premier vecteur est supérieur au deuxième par rapport 
 * à l'ordre lexicographique*/


#define ALIGNE 0x11		//à gauche ou aligné => p.pos & GAUCHE	//opération binaire
#define GAUCHE 0x01
#define DROITE 0x10

#define X coords[0]
#define Y coords[1]

int equal(const vertex* p1, const vertex* p2)
{
	return (p1->coords[0] == p2->coords[0] && p1->coords[1] == p2->coords[1]);
}

int cote(const vertex* p1, const vertex* p2, const vertex* p)
{
	if(equal(p1,p2) || equal(p1,p) || equal(p2,p))
		return ALIGNE;
	
	double e = (p2->Y-p1->Y)*(p->X-p2->X)-(p->Y-p2->Y)*(p2->X-p1->X);
	//printf("%f\n", e);
	
	if(e < 0) 		return DROITE;
	else if(e > 0)	return GAUCHE;
	else 			return ALIGNE;
}

/**v1 supérieur lexicographiquement à v2?*/
int superieur(const vertex* v1, const vertex* v2)
{
	if(v1->X > v2->X)
		return TRUE;
	else if(v1->X < v2->X)
		return FALSE;
	else
	{
		if(v1->Y > v2->Y)
			return TRUE;
		else if(v1->Y < v2->Y)
			return FALSE;
		else
			return IDEM;
	}
}

#define TRUE 1
#define FALSE 0

vertex* rechEnveloppe(const vertex[] tab, const int taille)
{
	//assert(taille > 0);
	if(taille == 0)
		return NULL;
	
	vertex* vmin = &tab[0];
	//recherche du minimum lexicographique
	for(int i = 1;	i < taille;	i++)
	{
		if(superieur(&tab[i], vmin)
			vmin = &tab[i];
	}
	
	vertex* v = vmin;
	vertex* retour = (vertex*) malloc(sizeof(vertex)*(taille+1));	//+1 pour la sentinelle
	retour[0] = v;
	int t2 = 1;	//nombre des éléments insérer dans le tableau retour (nouvelle position)
	
	int* tabAligne = (int*)malloc(sizeof(int)*taille);	//référencement des positions des vertex alignés lors d'une recherche de contour d'enveloppe.
	
	do
	{
		for(int i = 0;	i < taille;	i++)
		{
			int i2 = 1;	//tous sauf le min lexicographique
			while(i2 < t2 && &tab[i] != &retour[i2])
				i2++;
			
			
			if(i2 < t2)	//le vertex tab[i] n'est pas déjà dans les anciens vertex ajouté à l'enveloppe (sauf le min)
			{			//prend surtout en compte &tab[i] != retour[t2-1]
				//en recheche d'algo
				int j = 0;
				int c = GAUCHE;
				int tAligne;
				while(j < taille && c != DROITE)
				{
					tAligne = 0;
					if(i != j)
					{
						c = cote(&retour[t2-1], &tab[i], &tab[j]);
						if(c == ALIGNE)
						{
							tabAligne[tAligne] = j;
							tAligne++;
						}
					}	
					j++;
				}
				if(c & GAUCHE)	//on a trouvé un point dont le segment
				{
					v = &tab[i];
					//on cherche le point aligné le plus loin du point d'origine.
					for(int j2 = 0;	j2 < tAligne;	j2++)
					{
						
						const vector* v2 = retour[t2-1];
						int a = abs(v->x - v2->x);
						int b; 	//abs(tab[tabAligne[j2]].x - v2->x);
						if(a == 0)	//donc b aussi
						{
							a = abs(v->y - v2->y);
							b = abs(tab[tabAligne[j2]].y - v2->y);
						}
						else
							b = abs(tab[tabAligne[j2]].x - v2->x);
						
						if(a < b)	//en prenant ce nouveau point, le segment sera plus grand
							v = &tab[tabAligne[j2]];
					}
					break;
				}
			}
		}
		//insertion du minimum de l'angle polaire
		if(v != vmin)
		{
			retour[t2] = v;
			t2++;
		}
		else
			retour[t2] = NULL;
	}
	while(v != vmin);
	
	
	free(tabAligne);
	return retour;
} 
