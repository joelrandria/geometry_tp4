#include "tpga4_ex3.h"

#include "vertex.h"
#include "vertex_fusion_sorting.h"

#include <stdio.h>

void tpga4_ex3()
{
  _convex_ordonnes_ex3 = lexico_convex_hull(_points_ex3, _point_count);

  // ToDo JRA: Supprimer les lignes suivantes qui ne sont là que pour ne pas faire crasher le programme
  _convex_ordonnes_ex3 = _convex_ordonnes_ex2;
}

int vertex_lexico_cmp(vertex* v1, vertex* v2, void* args)
{
  return lexico_cmp(v1, v2);
}

vertex* lexico_convex_hull(vertex* points, unsigned int point_count)
{
  vertex* min_lexico;

  printf("lexico_convex_hull()\r\n");

  min_lexico = vertex_fusion_sort(points, _point_count, VLINK_LEXICO, vertex_lexico_cmp, 0);

  printf("----- APRÈS TRI -----\r\n");
  vertex_print_all(min_lexico, VLINK_LEXICO, VLINK_FORWARD);
  printf("---------------------\r\n");

  return 0;
}
