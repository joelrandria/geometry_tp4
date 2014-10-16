#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <math.h>
#include <stdlib.h>

/*! Dimensions de l'espace */
#define DIM 2

#define X coords[0]
#define Y coords[1]

#define ORIENTATION_CW		-1
#define ORIENTATION_INLINE	0
#define ORIENTATION_CCW		1

/*! Structure pour representer un point. */
typedef struct
{
	double coords[DIM];
} vertex;

vertex* vertex_create(double x, double y);

double vertex_distance(const vertex* v1, const vertex* v2);
double square_distance_eucl(const vertex* a, const vertex* b);
int lexico_cmp(const vertex* a, const vertex* b);
int lexico_min(const vertex* points, const unsigned int point_count);

int orientation(const vertex* a, const vertex* b, const vertex* c);
int local_polar_min(const vertex* points, const unsigned int point_count, int point);

#endif
