#include <stdio.h>
#include <math.h>

#include "tpga4.h"
#include "tpga4_ex2.h"
#include "int_stack.h"

int_stack* _current_hull_stack = 0;

void tpga4_ex2()
{
  _convex_hull = graham_convex_hull(_points, _point_count);
}

int_list* graham_convex_hull(vertex* points, unsigned int point_count)
{
  return 0;
}
