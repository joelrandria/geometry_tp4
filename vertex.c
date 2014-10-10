#include "vertex.h"

#include <math.h>
#include <stdlib.h>

vertex* vertex_create(double x, double y)
{
  vertex* v;

  v = malloc(sizeof(*v));
  v->coords[0] = x;
  v->coords[1] = y;

  return v;
}

float vertex_distance(vertex* v1, vertex* v2)
{
  return sqrt(pow((v2->coords[1] - v1->coords[1]), 2) + pow((v2->coords[0] - v1->coords[0]), 2));
}
