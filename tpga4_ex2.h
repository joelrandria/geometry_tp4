#ifndef __TPGA4_EX2_H__
#define __TPGA4_EX2_H__

#include "tpga4.h"
#include "vertex.h"
#include "triFusion.h"

// Exécution de l'exercice 2
void tpga4_ex2();

// Enveloppe convexe: Algorithme de Graham (Graham Scan)
vertex* graham_convex_hull(vertex* points, unsigned int point_count, int idG);
//int* fileDePrioritePolaire(const vertex points[], const uint taille);

#endif
