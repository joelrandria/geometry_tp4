#include "vertex_fusion_sorting.h"

void vertex_chaining(vertex* vertices, int count, int vlink, int vdirection)
{
  int i;

  if (vdirection == VLINK_FORWARD)
  {
    for (i = 0; i < count - 1; ++i)
      vertices[i].link[vlink][VLINK_FORWARD] = &vertices[i + 1];
  }
  else
  {
    for (i = 1; i < count; ++i)
      vertices[i].link[vlink][VLINK_BACKWARD] = &vertices[i - 1];
  }
}

vertex* vertex_fusion(vertex* left, vertex* right, int vlink, compare_func cmp, void *args)
{
  vertex fusion;
  vertex* scan;

  fusion.link[vlink][VLINK_FORWARD] = 0;
  scan = &fusion;

  while (left != 0 && right != 0)
  {
    if (cmp(left, right, args) < 0)
    {
      scan->link[vlink][VLINK_FORWARD] = left;
      left = left->link[vlink][VLINK_FORWARD];
    }
    else
    {
      scan->link[vlink][VLINK_FORWARD] = right;
      right = right->link[vlink][VLINK_FORWARD];
    }

    scan = scan->link[vlink][VLINK_FORWARD];
  }

  if (left != 0)
    scan->link[vlink][VLINK_FORWARD] = left;
  else
    scan->link[vlink][VLINK_FORWARD] = right;

  return fusion.link[vlink][VLINK_FORWARD];
}
vertex* vertex_fusion_sort_(vertex* first, int count, int vlink, compare_func cmp, void *args)
{
  vertex* left;
  vertex* right;
  vertex* median;

  if (count < 2)
    return first;

  median = vertex_at(first, (count / 2) - 1, vlink, VLINK_FORWARD);

  left = first;
  right = median->link[vlink][VLINK_FORWARD];

  median->link[vlink][VLINK_FORWARD] = 0;

  return (vertex_fusion(
	    vertex_fusion_sort_(left, count / 2, vlink, cmp, args),
	    vertex_fusion_sort_(right, count - (count / 2), vlink, cmp, args),
	    vlink, cmp, args
	    )
    );
}
vertex* vertex_fusion_sort(vertex* vertices, int count, int vlink, compare_func cmp, void *args)
{
  vertex_chaining(vertices, count, vlink, VLINK_FORWARD);

  vertices = vertex_fusion_sort_(vertices, count, vlink, cmp, args);

  vertex_chaining(vertices, count, vlink, VLINK_BACKWARD);

  return vertices;
}
