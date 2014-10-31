#include "tpga4_ex4.h"

void tpga4_ex4()
{
	_convex_ordonnes_ex4 = graham_convex_hull(_points, _point_count);
}

/**envconv EC_DC({} S, entier taille)
 * si(taille >= seuil)
 * 		Sg, 
 * 		Sd <- Partition de S suivant la médiane en Xy
 * 			//Sg et Sd ont une taille égale à 1 près et sont séparables par une droite (presque verticale au pire)
 * 		
 * 		lg <- EC_DC(Sg, tailleG);
 * 		ld <- EC_DC(Sg, tailleD);
 * 
 * 		retourner fusion(lg, ld);
 * else
 * 		retourner env conv à la main
 * */
/**état de départ: chaque points ont leurs voisins polaire à NULL*/
vertex* divide_convex_hull(vertex* points, unsigned int point_count)
{
	
	const int lexico = VLINK_LEXICO,	suiv = VLINK_FORWARD,	prec = VLINK_BACKWARD;
	
	//placer tous les points en les chaînants dans la chaine "lexico" mais par ordre naturel.
	for(int i = 0;	i < point_count;	i++)
	{
		if( i < point_count -1)
			points[i].link[lexico][suiv] = &points[i+1];
	}
	vertex* v;	//point de départ de la chaine simple;
	
	
	vertex* listLexico = triParFusion(&points[0], point_count-1, lexico, NULL);
	
	vertex* v2 = NULL;
	//définir l'ordre lexico dans l'autre sens? simple mais en O(n).
	v = listLexico;
	while(v != NULL)
	{
		v->link[lexico][prec] = v2;
		v2 = v;
		v = v->link[lexico][suiv];
	}
	
	//trouver le vertex de la médiane (au centre de la liste) dans l'ordre lexicographique
	int moit = point_count/2;
	vertex* moitie = listLexico;
	for(int i = 0;	i < moit;	i++)
		moitie = moitie->link[lexico][suiv];
	
	const int convex = VLINK_CONVEX;
	
	v = listLexico;
	v2 = v->link[lexico][suiv];
	while(v2 != NULL)
	{
		vertex* vMax = v2;
		while(v2 != NULL)
		{	
			int orient = orientation(vMax, v, v2);
			if(ORIENTATION_CCW == orient || ORIENTATION_INLINE == orient)
				vMax = v2;
			v2 = v2->link[lexico][suiv];
		}
		v->link[convex][suiv] = vMax;
		v = vMax;
		v2 = v->link[lexico][suiv];
	}
	
	return listLexico;	//pointeur vers le point G (minimum lexicographique).
}



