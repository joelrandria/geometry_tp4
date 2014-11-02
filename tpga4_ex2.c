#include "tpga4_ex2.h"

void tpga4_ex2()
{
	_convex_ordonnes_ex2 = graham_convex_hull(_points_ex2, _point_count);
}

/**état de départ: chaque points ont leurs voisins polaire à NULL*/
vertex* graham_convex_hull(vertex* points, unsigned int point_count)
{
	if(point_count == 0)
		return NULL;
	else if(point_count == 1)
	{
		points->link[VLINK_CONVEX][VLINK_FORWARD] = points;
		return points;
	}
	
	int idG = lexico_min(points, point_count);
	const int polar = VLINK_POLAR,	suiv = VLINK_FORWARD;
	vertex* G = &points[idG];
	for(int i = 0;	i < point_count;	i++)
	{
		if( i < point_count -1)
			points[i].link[polar][suiv] = &points[i+1];
	}
	vertex* v;	//point de départ de la chaine simple;
	if(idG > 0)
	{
		v = &points[0];
		points[idG-1].link[polar][suiv] = G->link[polar][suiv];	//inclu si &points[idG+1] -> NULL
	}
	else
		v = &points[1];
	G->link[polar][suiv] = NULL;
	
	
	vertex* listPolaire = triParFusion(v, point_count-1, polar, G);
	
	vertex* v2 = NULL;
	const int convex = VLINK_CONVEX;
	G->link[convex][suiv] = listPolaire;
	
	v = listPolaire;
	v2 = v->link[polar][suiv];
	while(v2 != NULL)
	{
		vertex* vMax = v2;
		while(v2 != NULL)
		{	
			int orient = orientation(vMax, v, v2);
			if(ORIENTATION_CCW == orient || ORIENTATION_INLINE == orient)
				vMax = v2;
			v2 = v2->link[polar][suiv];
		}
		v->link[convex][suiv] = vMax;
		v = vMax;
		v2 = v->link[polar][suiv];
	}
	
	v->link[convex][suiv] = G;
	
	return G;
	//fileDePrioritePolaire(points, point_count);
}







/**********************************************************************/
/**********************************************************************/
/**********************************************************************/


//fonction qui ne sera finalement pas utilisées





#define POS(k) points[fil[k]]
/**points: tableau d'entrée contenant des vertexs dans un ordre aléatoire
 * taille: taille des deux tableaux précédents (de même taille).
 * 
 * retour: p
 * */
int* fileDePrioritePolaire(const vertex points[], const uint taille)
{
	int minLexico = lexico_min(points, taille);
	const vertex* vMin = &points[minLexico];
	int* fil = (int*) malloc(sizeof(int)*taille);	//la fil est un index vers la position du vertex dans points[]
	assert(fil != NULL);
	
	double* angleP = (double*) malloc(sizeof(double)*taille);	//stockage de l'angle polaire de chaque vertex par rapport au min lexicographique (permet de ne pas recalculer le père (k/2) à chaque tour de boucle)
	assert(angleP != NULL);
	//angleP[minLexico] = -1;	//évite le core dumped à la désallocation
	int* retour = (int*) malloc(sizeof(int)*(taille-1));	//tableau retourné, index vers la position du 
	assert(retour != NULL);
	
	int k;

	for(int i = 0;	i < taille;	i++)
	{
		if(i == minLexico)
			continue;
			
		k = (i < minLexico ? i+1 : i);
		double calc = calculPolaire(vMin, &(points[i]));
		angleP[i] = calc;
		//on remonte le numéro d'index i dans l'arbre tantque le père existe (>0) 
		// et qu'il pointe vers un index_vertex qui est inférieur à l'élément
		while(k/2 > 0 && calc < angleP[fil[k/2]])					//while(k/2 > 0 && calc > calculPolaire(vMin, &(POS(k/2))))
		{
			fil[k] = fil[k/2];	//on descend l'index du père
			k/=2;
		}
		fil[k] = i;
	}
	/*l'arbre est construit et complété avec tous les pères 
	supérieurs ou égaux aux fils*/ 
	
	int t2 = taille-1;
	for(int i = 0;	i < taille-1;	i++)
	{
		k = 1;
		retour[i] = fil[1];	//on ajoute le premier élément en tête de l'arbre dans le tableau de retour.
		int index = fil[t2];		///v = &(POS(t2));
		
		while(2*k <= t2)	
		{
			int j = 2*k;
			//printf("coord: %f  %f\n", POS(k).X, POS(k).Y);
			if(j+1 <= t2 && angleP[fil[j+1]] < angleP[fil[j]])		///(superieur(&(POS(j+1)),&(POS(j))))
				j++;	//si le fils j est plus petit polairement que le fils j+1, alors c'est le fils j+1 qui monte dans l'arbre
			if(angleP[index] < angleP[fil[j]])
				break;
			//printf("remplace %d avec %d\n", k, j);
			fil[k] = fil[j];
			k = j;
		}
		fil[k] = fil[t2];
		t2--;
	}
	
	for(int i = 0;	i < taille -1;	i++)
		printf("%d -> %lf\n", retour[i], angleP[retour[i]]);
	
	free(fil);
	free(angleP);
	return retour;
}
