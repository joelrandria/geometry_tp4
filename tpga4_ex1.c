#include "tpga4_ex1.h"

void tpga4_ex1()
{
  _convex_ordonnes_ex1 = jarvis_convex_hull(_points_ex1, _point_count);
}


int_list* jarvis_convex_hull2(const vertex* points, const unsigned int point_count)
{
	const int lexico_min_point = lexico_min(points, point_count);

	int_list* hull = NULL;
	hull = int_list_enqueue(hull, lexico_min_point);
	
	int last_hull_point = lexico_min_point;
	int local_polar_min_point;
	while ((local_polar_min_point = local_polar_min(points, point_count, last_hull_point))
								!= lexico_min_point)
	{
		hull = int_list_enqueue(hull, local_polar_min_point);
		last_hull_point = local_polar_min_point;
	}

	return hull;
}

vertex* jarvis_convex_hull(vertex* points, const unsigned int point_count)
{
	if(point_count == 0)
		return NULL;
	else if(point_count == 1)
	{
		points->link[VLINK_CONVEX][VLINK_FORWARD] = points;
		return points;
	}
	const int lexico_min_point = lexico_min(points, point_count);
	vertex* v = &points[lexico_min_point];
	vertex *const debList = v;
	
	int last_hull_point = lexico_min_point;
	int local_polar_min_point;
	while ((local_polar_min_point = local_polar_min(points, point_count, last_hull_point))
								!= lexico_min_point)
	{
		v->link[VLINK_CONVEX][VLINK_FORWARD] = &points[local_polar_min_point];
		last_hull_point = local_polar_min_point;
		v = v->link[VLINK_CONVEX][VLINK_FORWARD];
	}
	v->link[VLINK_CONVEX][VLINK_FORWARD] = debList;
	
	
	return debList;
}
