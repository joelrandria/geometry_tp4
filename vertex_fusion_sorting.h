#ifndef __VERTEX_FUSION_SORTING_H__
#define __VERTEX_FUSION_SORTING_H__

#include "vertex.h"

/**
 * Prototype de fonction de comparaison de deux vertices prenant un argument complémentaire.
 *
 * La fonction de comparaison retourne:
 *
 * - Une valeur < 0 si (v1 < v2)
 * - Une valeur égale à 0 si (v1 == v2)
 * - Une valeur > 0 si (v1 > v2)
 */
typedef int(*compare_func)(vertex* v1, vertex* v2, void *args);

/**
 * Effectue un tri par fusion sur le tableau de vertices spécifié.
 *
 * @vertices: Tableau de vertices à trier.
 * @count: Taille du tableau.
 * @vlink: Type de relation inter-vertices à trier (ex: VLINK_NATURAL pour trier la liste naturelle de vertices).
 * @cmp: Pointeur vers la fonction de comparaison entre 2 vertices à utiliser.
 * @args: Pointeur vers un argument transmis à la fonction de comparaison.
 * @return: Pointeur vers la première vertice issue du tri.
 */
vertex* vertex_fusion_sort(vertex* vertices, int count, int vlink, compare_func cmp, void *args);

#endif
