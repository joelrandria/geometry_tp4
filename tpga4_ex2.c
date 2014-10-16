#include <stdio.h>
#include <math.h>

#include "tpga4.h"
#include "tpga4_ex2.h"

#define ORIENTATION_CCW		1
#define ORIENTATION_INLINE	0
#define ORIENTATION_CW		-1

void tpga4_ex2()
{
  printf("tpga4_ex2()\r\n");

  /* _convex_hull = graham_convex_hull(_points, _point_count); */

  /* glutIdleFunc(on_idle_event); */
  /* glutDisplayFunc(draw); */

  /* glutMainLoop(); */
}

int_list* graham_convex_hull(vertex* points, unsigned int point_count)
{
  return 0;
}
