#include "vertex.h"

vertex* vertex_insert(vertex* ref, vertex* nouv, int link, const int direction)
{
	vertex* temp = NULL;
	temp = ref->link[link][direction];

	ref->link[link][direction] = nouv;
	
	nouv->link[link][direction] = temp;
	nouv->link[link][!direction] = ref;
	
	if(temp != NULL)
		temp->link[link][!direction] = nouv;
	
	return nouv;
}
vertex* vertex_insert_before(vertex* ref, vertex* nouv, int link)
{	return vertex_insert(ref, nouv, link, VLINK_BACKWARD);	}
vertex* vertex_insert_after(vertex* ref, vertex* nouv, int link)
{	return vertex_insert(ref, nouv, link, VLINK_FORWARD);	}

vertex* vertex_def(vertex* nouv, int link, vertex* gauche, vertex* droite)
{
	nouv->link[link][VLINK_BACKWARD] = gauche;
	nouv->link[link][VLINK_FORWARD] = droite;
	if(gauche != NULL)
		gauche->link[link][VLINK_FORWARD] = nouv;
	if(droite != NULL)
		droite->link[link][VLINK_BACKWARD] = nouv;
	return nouv;
}


vertex* vertex_last(vertex* ref, int link, int direction)
{
	vertex* temp;
	while((temp = ref->link[VLINK_NATURAL][direction]) != NULL)
		ref = temp;
	return ref;
}

vertex* vertex_ajoutNaturel(vertex* ref, vertex* nouv, int direction)
{
	ref = vertex_last(ref, VLINK_NATURAL, direction);
	ref->link[VLINK_NATURAL][direction] = nouv;
	nouv->link[VLINK_NATURAL][!direction] = ref;
	
	return nouv;
}
vertex* vertex_ajoutNaturelFirst(vertex* ref, vertex* nouv)
{	return ajoutNaturel(ref, VLINK_NATURAL, VLINK_BACKWARD);	}
vertex* vertex_ajoutNaturelLast(vertex* ref, vertex* nouv)
{	return ajoutNaturel(ref, VLINK_NATURAL, VLINK_FORWARD);	}

vertex* vertex_ajoutLexico(vertex* ref, vertex* nouv)
{
	vertex* temp = NULL;
	int dir = lexico_cmp(nouv, ref);
	if(dir == 1)
	{
		while(dir == 1)
		{
			temp = ref;
			ref = ref->link[VLINK_LEXICO][VLINK_FORWARD];
			if(ref == NULL)
				return vertex_insert_after(temp, nouv, VLINK_LEXICO);
			dir = lexico_cmp(nouv, ref);
		}
		return vertex_insert_before(ref,nouv, VLINK_LEXICO);
	}
	else if(dir == -1)
	{
		while(dir == -1)
		{
			temp = ref;
			ref = ref->link[VLINK_LEXICO][VLINK_BACKWARD];
			if(ref == NULL)
				return vertex_insert_before(temp, nouv, VLINK_LEXICO);
			dir = lexico_cmp(nouv, ref);
		}
		return vertex_insert_after(ref, nouv, VLINK_LEXICO);
	}
	else 	//0
		return vertex_insert_after(ref, nouv, VLINK_LEXICO);
}


#define POS(k) tab[fil[k]]
/**tab: tableau d'entrée contenant des vertexs dans un ordre aléatoire
 * retour: tableau de sortie contenant les vertexs de tab dans l'ordre lexicographique
 * taille: taille des deux tableaux précédents (de même taille).
 * */
int* fileDePrioriteLexico(const vertex tab[], const int taille)
{
	int* fil = (int*) malloc(sizeof(int)*(taille+1));	//la fil est un index vers la position du vertex dans tab[]
	int k;

	const vertex* v;
	for(int i = 0;	i < taille;	i++)
	{
		v = &(tab[i]);
		k = i+1;
		//on remonte le numéro d'index i dans l'arbre tantque le père existe (>0) 
		// et qu'il pointe vers un index_vertex qui est inférieur à l'élément
		while(k/2 > 0 && lexico_cmp(v, &(POS(k/2))) == 1)	//attention à IDEM = 2
		{
			fil[k] = fil[k/2];	//on descend l'index du père
			k/=2;
		}
		fil[k] = i;
	}
	
	/*l'arbre est construit et complété avec tous les pères 
	supérieurs ou égaux aux fils*/ 
	int* retour = (int*) malloc(sizeof(int)*taille);
	
	int t2 = taille;
	for(int i = 0;	i < taille;	i++)
	{
		k = 1;
		retour[i] = fil[1];	//on ajoute le premier élément en tête de l'arbre dans le tableau de retour.
		v = &(POS(t2));
		
		while(2*k <= t2)	
		{
			int j = 2*k;
			//printf("coord: %f  %f\n", POS(k).X, POS(k).Y);
			if(j+1 <= t2 && lexico_cmp(&(POS(j+1)),&(POS(j))) == 1)
				j++;	//si le fils j est plus petit lexicographiquement que le fils j+1, alors c'est le fils j+1 qui monte dans l'arbre
			if(lexico_cmp(v,&(POS(j)))>=0)
				break;
			//printf("remplace %d avec %d\n", k, j);
			fil[k] = fil[j];
			k = j;
		}
		fil[k] = fil[t2];
		t2--;
	}
	
	free(fil);
	return retour;
}

void raffraichiLexico(vertex tab[], const int taille)
{
	int* fdp = fileDePrioriteLexico(tab, taille);
	for(int i = 0;	i < taille;	i++)
	{
		tab[fdp[i]].link[VLINK_LEXICO][VLINK_BACKWARD] = (i == 0 ? NULL : tab[fdp[i-1]]);
		tab[fdp[i]].link[VLINK_LEXICO][VLINK_FORWARD] = (i == taille-1 ? NULL : tab[fdp[i+1]]);
	}
}
