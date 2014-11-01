#include "tpga4_ex3.h"

#include "vertex.h"
#include "vertex_fusion_sorting.h"

void tpga4_ex3()
{
  _convex_ordonnes_ex3 = lexical_convex_hull(_points_ex3, _point_count);
}

int vertex_lexical_cmp(vertex* v1, vertex* v2, void* args)
{
  return lexico_cmp(v1, v2);
}
int lexical_first_triangle(vertex* ref, vertex** v2, vertex** v3)
{
  vertex* temp;

  *v2 = ref->link[VLINK_LEXICO][VLINK_FORWARD];
  *v3 = (*v2)->link[VLINK_LEXICO][VLINK_FORWARD];

  while ((*v3 != 0) && (orientation(ref, *v2, *v3) == ORIENTATION_INLINE))
  {
    *v2 = *v3;
    *v3 = (*v3)->link[VLINK_LEXICO][VLINK_FORWARD];
  }

  if (*v3 != 0)
  {
    if (orientation(ref, *v2, *v3) != ORIENTATION_CCW)
    {
      temp = *v2;
      *v2 = *v3;
      *v3 = temp;
    }
  }

  return (*v3 != 0);
}

void convex_hull_start(vertex* first)
{
  first->link[VLINK_CONVEX][VLINK_BACKWARD] = first;
  first->link[VLINK_CONVEX][VLINK_FORWARD] = first;
}
void convex_hull_distinct_insert(vertex* ref, vertex* new)
{
  if (lexico_cmp(ref, new) != 0)
      vertex_insert(ref, new, VLINK_CONVEX, VLINK_FORWARD);
}
void convex_hull_remove_range(vertex* start, vertex* end)
{
  vertex* to_remove;
  vertex* to_remove_next;

  while (start->link[VLINK_CONVEX][VLINK_FORWARD] != end)
  {
    to_remove = start->link[VLINK_CONVEX][VLINK_FORWARD];
    to_remove_next = to_remove->link[VLINK_CONVEX][VLINK_FORWARD];

    start->link[VLINK_CONVEX][VLINK_FORWARD] = to_remove_next;
    to_remove_next->link[VLINK_CONVEX][VLINK_BACKWARD] = start;

    to_remove->link[VLINK_CONVEX][VLINK_BACKWARD] = 0;
    to_remove->link[VLINK_CONVEX][VLINK_FORWARD] = 0;
  }
}

vertex* lexical_convex_hull(vertex* points, unsigned int point_count)
{
  vertex* v2;
  vertex* v3;

  vertex* lex_min;
  vertex* last_inserted;
  vertex* lex_next;

  vertex* start_range;
  vertex* end_range;

  // Tri des vertices par ordre lexicographique O(n log(n))
  lex_min = vertex_fusion_sort(points, point_count, VLINK_LEXICO, vertex_lexical_cmp, 0);

  // Insertion du minimum lexicographique dans l'enveloppe convexe
  convex_hull_start(lex_min);

  // 2 points: Insertion du 2e point dans l'enveloppe si distinct
  if (point_count < 3)
  {
    convex_hull_distinct_insert(lex_min, lex_min->link[VLINK_LEXICO][VLINK_FORWARD]);
    return lex_min;
  }

  // Obtention du 1er triangle non-dégénéré dans l'ordre lexicographique
  if (lexical_first_triangle(lex_min, &v2, &v3) == 0)
  {
    // Points tous alignés: Insertion du maximum lexicographique si distinct
    convex_hull_distinct_insert(lex_min, v2);
    return lex_min;
  }

  // Insertion des sommets du triangle dans l'enveloppe convexe
  vertex_insert(lex_min, v2, VLINK_CONVEX, VLINK_FORWARD);
  vertex_insert(v2, v3, VLINK_CONVEX, VLINK_FORWARD);

  // Obtient le maximum lexicographique de l'enveloppe courante
  if (lexico_cmp(v2, v3) < 0)
    last_inserted = v3;
  else
    last_inserted = v2;

  // Boucle d'insertion dans l'ordre lexicographique
  lex_next = last_inserted->link[VLINK_LEXICO][VLINK_FORWARD];
  while (lex_next)
  {
    start_range = last_inserted;
    while (orientation(lex_next, start_range, start_range->link[VLINK_CONVEX][VLINK_BACKWARD])
	   != ORIENTATION_CW)
      start_range = start_range->link[VLINK_CONVEX][VLINK_BACKWARD];

    end_range = last_inserted;
    while (orientation(lex_next, end_range, end_range->link[VLINK_CONVEX][VLINK_FORWARD])
	   != ORIENTATION_CCW)
      end_range = end_range->link[VLINK_CONVEX][VLINK_FORWARD];

    convex_hull_remove_range(start_range, end_range);

    vertex_insert(start_range, lex_next, VLINK_CONVEX, VLINK_FORWARD);

    last_inserted = lex_next;
    lex_next = lex_next->link[VLINK_LEXICO][VLINK_FORWARD];
  }

  return lex_min;
}
