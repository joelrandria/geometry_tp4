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
vertex* vertex_insert_after(vertex* ref, vertex* nouv, int link, const int direction)
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


