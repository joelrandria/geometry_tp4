#include "vertex.h"

void vertex_insert(vertex* ref, vertex* nouv, int link, int direction)
{
  vertex* temp;

  temp = ref->link[link][direction];

  ref->link[link][direction] = nouv;

  nouv->link[link][!direction] = ref;

  
}
