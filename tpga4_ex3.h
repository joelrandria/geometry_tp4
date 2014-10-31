#ifndef __TPGA4_EX3_H__
#define __TPGA4_EX3_H__

#include "tpga4.h"
#include "vertex.h"
#include "triFusion.h"

// Exécution de l'exercice 3
void tpga4_ex3();

// Enveloppe convexe: Algorithme d'insertion par ordre lexicographique
vertex* lexico_convex_hull(vertex* points, unsigned int point_count);

#endif
