#include "tpga4_ex4.h"

void tpga4_ex4()
{
	_convex_ordonnes_ex4 = divide_convex_hull(_points_ex4, _point_count);
}

#define test(n)	printf("test %d", n)

vertex* fusionEnv(vertex* list1, vertex* list2)
{
	const int lexico = VLINK_LEXICO,	convex = VLINK_CONVEX,	prec = VLINK_BACKWARD,	suiv = VLINK_FORWARD;
	vertex* gg = list1, *dg = list2;
	vertex* gd = gg, *g, *d, *g2, *d2;
	while(gd->link[lexico][suiv] != NULL)
		gd = gd->link[lexico][suiv];
		
	//on réassocie les deux couples
	gd->link[lexico][suiv] = dg;
	//dg->link[lexico][suiv] = gd;
	
	
	g = gd;
	d = dg;
	g2 = g->link[convex][suiv];		//ce suivant est juste en dessus dans l'ordre polaire
	d2 = d->link[convex][prec];		//ce précédant est juste en dessus dans l'ordre polaire
	
	while((d != d2 && orientPolaire(g, d, d2) <= M_PI) || (g != g2 && orientPolaire(d, g, g2) >= M_PI))
	{
		while(d != d2 && orientPolaire(g, d, d2) <= M_PI)
		{
			d = d2;
			d2 = d->link[convex][prec];
		}
		while(g != g2 && orientPolaire(d, g, g2) >= M_PI)
		{
			g = g2;
			g2 = g->link[convex][suiv];
		}
	}
	
	vertex* hg = g, *hd = d;
	//g->link[convex][prec] = d;	//grosse faute pour le reste de l'algorithme
	//d->link[convex][suiv] = g;
	
	
	//et c'est reparti dans l'autre sens
	g = gd;
	d = dg;
	g2 = g->link[convex][prec];		//ce précédent est juste en dessus dans l'ordre polaire
	d2 = d->link[convex][suiv];		//ce suivant est juste en dessus dans l'ordre polaire
	
	while((d != d2 && orientPolaire(g, d, d2) >= M_PI) || (g != g2 && orientPolaire(d, g, g2) <= M_PI))
	{
		while(d != d2 && orientPolaire(g, d, d2) >= M_PI)
		{
			d = d2;
			d2 = d->link[convex][suiv];
		}
		while(g != g2 && orientPolaire(d, g, g2) <= M_PI)
		{
			g = g2;
			g2 = g->link[convex][prec];
		}
	}
	
	//on ferme l'enveloppe convexe.
	g->link[convex][suiv] = d;
	d->link[convex][prec] = g;
	hg->link[convex][prec] = hd;
	hd->link[convex][suiv] = hg;
	
	return gg;
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
	const int lexico = VLINK_LEXICO,	suiv = VLINK_FORWARD,	prec = VLINK_BACKWARD;
	if(point_count < 3)
	{
		const int convex = VLINK_CONVEX;
		vertex* v = vert;
		if(point_count == 2 && !( equal(vert ,  vert->link[lexico][suiv])) )
		{
			v = vert->link[lexico][suiv];
			vert->link[convex][suiv] = v;
			v->link[convex][prec] = vert;
		}
		
		//peux importe que v == vert ou v == vert->link[lexico][suiv]
		v->link[lexico][suiv] = NULL;//pour facilité fusion et recherche de gd, dd
		v->link[convex][suiv] = vert;
		vert->link[convex][prec] = v;
		
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
		
		return fusionEnv(	envConvDC(vert, moit), 
							envConvDC(moitie, moit2));
	}
}


/**état de départ: chaque points ont leurs voisins polaire à NULL*/
vertex* divide_convex_hull(vertex* points, unsigned int point_count)
{
	const int lexico = VLINK_LEXICO,	suiv = VLINK_FORWARD;//,	prec = VLINK_BACKWARD;
	
	//placer tous les points en les chaînants dans la chaine "lexico" mais par ordre naturel.
	for(int i = 0;	i < point_count;	i++)
	{
		if( i < point_count -1)
			points[i].link[lexico][suiv] = &points[i+1];
	}
	
	vertex* listLexico = triParFusion(&points[0], point_count, lexico, NULL);
	envConvDC(listLexico, point_count);
	
	return listLexico;	//pointeur vers le point G (minimum lexicographique).
}



