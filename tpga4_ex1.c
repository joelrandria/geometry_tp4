#include "tpga4_ex1.h"

void tpga4_ex1()
{
  _convex_hull = jarvis_convex_hull(_points_ex1, _point_count);
}


int_list* jarvis_convex_hull(const vertex* points, const unsigned int point_count)
{
	int_list* hull;
	int last_hull_point;
	int lexico_min_point;
	int local_polar_min_point;

	lexico_min_point = lexico_min(points, point_count);
	last_hull_point = lexico_min_point;

	hull = 0;
	hull = int_list_enqueue(hull, lexico_min_point);

	while ((local_polar_min_point = local_polar_min(points, point_count, last_hull_point))
			!= lexico_min_point)
	{
		hull = int_list_enqueue(hull, local_polar_min_point);
		last_hull_point = local_polar_min_point;
	}

	return hull;
}
