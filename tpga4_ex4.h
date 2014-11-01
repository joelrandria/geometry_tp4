#ifndef __TPGA4_EX4_H__
#define __TPGA4_EX4_H__

#include "tpga4.h"
#include "vertex.h"
#include "triFusion.h"

// Fonctions d'affichage
void tpga4_ex4();

/**état de départ: chaque points ont leurs voisins polaire à NULL*/
vertex* divide_convex_hull(vertex* points, unsigned int point_count);

#endif
