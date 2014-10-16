#include "vertex.h"

vertex* vertex_create(double x, double y)
{
	vertex* v = malloc(sizeof(*v));
	v->coords[0] = x;
	v->coords[1] = y;

	return v;
}

double vertex_distance(const vertex* v1, const vertex* v2)
{
	return hypot(v2->Y - v1->Y, v2->X - v1->X);
	//return sqrt(pow((v2->Y - v1->Y), 2) + pow((v2->X - v1->X), 2));
}

/**
 * calcul de la distance entre deux vertex au carré. 
 * temps réduit par rapport à une comparaison de distance avec vertex_distance(a,b)
 */
double square_distance_eucl(const vertex* a, const vertex* b)
{
	return (pow(b->X - a->X, 2) + pow(b->Y - a->Y, 2));
}




int lexico_cmp(const vertex* a, const vertex* b)
{
	if (a->X < b->X)
		return -1;
	else if (a->X == b->X)
	{
		if (a->Y < b->Y)
			return -1;
		else if (a->Y == b->Y)
			return 0;
		//else return 1;
	}
	return 1;
}
int lexico_min(const vertex* points, const uint point_count)
{
	if (point_count <= 0)
		return -1;

	int min = 0;
	uint i;
	for (i = 1; i < point_count; ++i)
		if (lexico_cmp(&points[i], &points[min]) < 0)
			min = i;

	return min;
}

int orientation(const vertex* a, const vertex* b, const vertex* c)
{
	int normal_dot_product = (a->Y - b->Y) * (c->X - a->X) + (b->X - a->X) * (c->Y - a->Y);

	if (normal_dot_product > 0)
		return ORIENTATION_CCW;
	else if (normal_dot_product == 0)
		return ORIENTATION_INLINE;
	else
		return ORIENTATION_CW;
}


int local_polar_min(const vertex* points, const uint point_count, int point)
{
	if (point_count == 0)
		return -1;
		
	uint i;
	int local_polar_min;
	int current_point_orientation;
	
	for (i = 0; i < point_count; ++i)
		if (i != point)
		{
			local_polar_min = i;
			break;
		}

	for (i = 0; i < point_count; ++i)
	{
		if (i == point)
			continue;

		current_point_orientation = orientation(&points[point], &points[local_polar_min], &points[i]);
		if (current_point_orientation == ORIENTATION_CW)
			local_polar_min = i;
		else if (current_point_orientation == ORIENTATION_INLINE)
			if (square_distance_eucl(&points[point], &points[i]) > square_distance_eucl(&points[point], &points[local_polar_min]))
				local_polar_min = i;
	}

	return local_polar_min;
}
