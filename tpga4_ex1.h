#ifndef __TPGA4_EX1_H__
#define __TPGA4_EX1_H__

#include "vertex.h"
#include "int_list.h"

// Exécution de l'exercice 1
void tpga4_ex1();

// Enveloppe convexe: Algorithme de Jarvis (Gift Wrapping)
int_list* jarvis_convex_hull(vertex* points, unsigned int point_count);

#endif
