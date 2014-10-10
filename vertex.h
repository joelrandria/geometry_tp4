#ifndef __VERTEX_H__
#define __VERTEX_H__

/*! Dimensions de l'espace */
#define DIM 2

#define X coords[0]
#define Y coords[1]

/*! Structure pour representer un point. */
typedef struct
{
  double coords[DIM];
} vertex;

vertex* vertex_create(double x, double y);

float vertex_distance(vertex* v1, vertex* v2);

#endif
