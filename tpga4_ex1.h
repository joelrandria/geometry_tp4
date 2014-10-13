#ifndef __TPGA4_EX1_H__
#define __TPGA4_EX1_H__

#include "vertex.h"
#include "int_list.h"

// Exécution de l'exercice 1
void tpga4_ex1();

// Fonctions d'affichage
void draw();
void draw_points(vertex* points, int point_count);
void draw_hull(vertex* points, int_list* hull_points);

// Gestionnaires d'évènements
void on_idle_event();

// Enveloppe convexe: Algorithme de Jarvis (Gift Wrapping)
int_list* jarvis_convex_hull(vertex* points, unsigned int point_count);

#endif
