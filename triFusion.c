#include "triFusion.h"
#include <stdio.h>

void test(const int i)
{
	printf("test %d\n", i);
} 

vertex* quiGagne(vertex* v1, vertex* v2, const int type, const void* arg)
{
	if(v1 == NULL)
		return v2;
	else if(v2 == NULL)
		return v1;
	switch(type)
	{
		case VLINK_NATURAL:	return v1;
		case VLINK_LEXICO: 	return (lexico_cmp(v1, v2)	?	v1	: v2);
		case VLINK_POLAR:	
							return (ORIENTATION_CCW == orientation((vertex*) arg, v1, v2) ? 
										v1	:	v2
									);								
	}
	return NULL;
}

/**état de départ: les deux listes chainées se terminent par NULL*/
vertex* fusion(vertex* list1, vertex* list2, const int type, const void* arg)
{
	vertex* debList = quiGagne(list1, list2, type, arg);
	if(debList == list1)
		list1 = list1->link[type][VLINK_FORWARD];
	else
		list2 = list2->link[type][VLINK_FORWARD];
	
	vertex* v = debList; 
	
	while(list1 != NULL && list2 != NULL)
	{
		v->link[type][VLINK_FORWARD] = quiGagne(list1, list2, type, arg);
		v = v->link[type][VLINK_FORWARD];
		if(v == list1)
			list1 = list1->link[type][VLINK_FORWARD];
		else
			list2 = list2->link[type][VLINK_FORWARD];
	}
	if(list1 == NULL)
		v->link[type][VLINK_FORWARD] = list2;	//pas de boucle sachant que les éléments restants dans list2 sont déjà chainés et ordonnée sur list2->link[type][VLINK_FORWARD] 
	else
		v->link[type][VLINK_FORWARD] = list1;
	
	return debList;
}
//typedef int(*func)(vertex*, vertex*, void*) cmpFunc;

vertex* triParFusion(vertex* debList, const int nb, const int type, const void* arg)
{
	//test(5);
	if(nb == 1)
	{
		debList->link[type][VLINK_FORWARD] = NULL;	//pour ne pas à avoir à passer le nombre d'élément des deux listes dans la fonction fusion(list1, list2, type, arg)
		return debList;
	}
	vertex * v = debList;
	int moitie = nb - nb/2; 	// nb/2+nb%2;
	
	for(int i = 0;	i < moitie;	i++)
		v = v->link[type][VLINK_FORWARD];
	
	return fusion(
					triParFusion(debList, moitie, type, arg),
					triParFusion(v, nb/2, type, arg),
					type, arg);
}

vertex* chainageArriere(vertex* debList, const int type)
{
	vertex* v = debList, *v2 = NULL;
	while(v != NULL)
	{
		v->link[type][VLINK_BACKWARD] = v2;
		v2 = v;
		v = v->link[type][VLINK_FORWARD];
	}
	
	return debList;
}

vertex* triParFusionDouble(vertex* debList, const int nb, const int type, const void* arg)
{
	vertex* v = triParFusion(debList, nb, type, arg);
	return chainageArriere(v, type); 
}


