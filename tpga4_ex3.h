#ifndef __TPGA4_EX3_H__
#define __TPGA4_EX3_H__

#include "tpga4.h"
#include "vertex.h"

// Exécution de l'exercice 3
void tpga4_ex3();

// Enveloppe convexe: Algorithme d'insertion par ordre lexicographique
vertex* lexical_convex_hull(vertex* points, unsigned int point_count);

/**
 * Adaptation de la fonction lexico_cmp(v1, v2) pour les prototypes de fonction prenant un argument.
 */
int vertex_lexical_cmp(vertex* v1, vertex* v2, void* args);
/**
 * Obtient le premier triangle non-dégénéré dans l'ordre lexicographique, s'il existe.
 * Si c'est le cas, les paramètre v2 et v3 se voient affectés les adresses des sommets de ce triangle, dans l'ordre canonique.
 *
 * @ref: Pointeur vers le sommet de référence.
 * @v2: Reçoit l'adresse du 2e sommet dans l'ordre canonique.
 * @v2: Reçoit l'adresse du 3e sommet dans l'ordre canonique.
 * @return: Une valeur différente de 0 si un triangle non-dégénéré a été trouvé, sinon 0.
 */
int lexical_first_triangle(vertex* ref, vertex** v2, vertex** v3);

#endif
