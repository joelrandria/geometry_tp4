#ifndef __VERTEX_H__
#define __VERTEX_H__

#include <math.h>
#include <stdlib.h>

/*! Dimensions de l'espace */
#define DIM 2
#define X coords[0]
#define Y coords[1]

// Orientations
#define ORIENTATION_CW		-1
#define ORIENTATION_INLINE	0
#define ORIENTATION_CCW		1

// Liens inter vertices
#define VLINK_TYPE_COUNT	4
#define VLINK_NATURAL		0
#define VLINK_POLAR		1
#define VLINK_LEXICO		2
#define VLINK_CONVEX		3

#define VLINK_DIRECTION_COUNT	2
#define VLINK_BACKWARD		0
#define VLINK_FORWARD		1

/*! Structure pour representer un point. */
typedef struct _vertex
{
  double coords[DIM];
  struct _vertex* link[VLINK_TYPE_COUNT][VLINK_DIRECTION_COUNT];
} vertex;

void vertex_init(vertex* v, double x, double y);
vertex* vertex_create(double x, double y);

vertex* vertex_copy(vertex* tab, int count);

void vertex_insert(vertex* ref, vertex* nouv, int link, int direction);

double vertex_distance(const vertex* v1, const vertex* v2);
double square_distance_eucl(const vertex* a, const vertex* b);

int lexico_cmp(const vertex* a, const vertex* b);
int lexico_min(const vertex* points, const unsigned int point_count);

int orientation(const vertex* a, const vertex* b, const vertex* c);
int local_polar_min(const vertex* points, const unsigned int point_count, int point);

#endif
