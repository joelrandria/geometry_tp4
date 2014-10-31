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
vertex* envConvDC(vertex* vert, unsigned int point_count)
{
	const int lexico = VLINK_LEXICO,	suiv = VLINK_FORWARD;
	if(point_count < 3)
	{
		if(point_count == 2)
		{
			const int convex = VLINK_CONVEX;
			vertex* v = vert->link[lexico][suiv];
			v->link[lexico][suiv] = NULL;	//pour facilité fusion et recherche de gd, dd
			vert->link[convex][suiv] = v;
			
		}
		else
		return vert;
	}
	else
	{
		//trouver le vertex de la médiane (au centre de la liste) dans l'ordre lexicographique
		int moit = point_count/2, 
			moit2 = point_count-moit;
		vertex* moitie = vert;
		for(int i = 0;	i < moit;	i++)
			moitie = moitie->link[lexico][suiv];
		//pour 4: 0,1 à gauche et 2,3 à droite
		//pour 5: 0,1 à gauche et 2,3,4 à droite
		
		return fusionEnv(	envConvDC(points, moit), 
							envConvDC(moitie, moit2));
	}
}

vertex* fusionEnv(vertex* list1, vertex* list2)
{
	const int lexico = VLINK_LEXICO,	suiv = VLINK_FORWARD;
	vertex* gg = list1, *dg = list2,
			*d = dg;
	vertex* gd = gg, *g;
	while(gd->link[lexico][suiv] != NULL)
		gd = gd->link[lexico][suiv];
	g = gd;
	
	while(orientation(g, 
		
	
	fusion(list1, list2, lexico, NULL);
}

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
	
	
	vertex* listLexico = triParFusionDouble(&points[0], point_count-1, lexico, NULL);
	
	
	
	return listLexico;	//pointeur vers le point G (minimum lexicographique).
}



