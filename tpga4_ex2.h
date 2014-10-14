#ifndef __TPGA4_EX2_H__
#define __TPGA4_EX2_H__

#include "vertex.h"
#include "int_list.h"

// Exécution de l'exercice 2
void tpga4_ex2();

// Enveloppe convexe: Algorithme de Graham (Graham Scan)
int_list* graham_convex_hull(vertex* points, unsigned int point_count);

#endif
