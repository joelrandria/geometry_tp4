#ifndef __TRIFUSION_H__
#define __TRIFUSION_H__

#include "vertex.h"

vertex* quiGagne(vertex* v1, vertex* v2, const int type, const void* arg);

/**état de départ: les deux listes chainées se terminent par NULL. Les deux chaines sont définis en paramètre par un pointeur vers son premier élément.
 * fin: pointeur vers le premier élément de la liste chainée ordonnée*/
vertex* fusion(vertex* list1, vertex* list2, const int type, const void* arg);

vertex* triParFusion(vertex* debList, const int nb, const int type, const void* arg);
vertex* triParFusionDouble(vertex* debList, const int nb, const int type, const void* arg);

#endif
