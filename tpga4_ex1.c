#include <stdio.h>
#include <math.h>

#include <GL/glut.h>

#include "tpga4.h"
#include "tpga4_ex1.h"

#define ORIENTATION_CCW		1
#define ORIENTATION_INLINE	0
#define ORIENTATION_CW		-1

// Enveloppe convexe
int_list* _convex_hull = 0;

void tpga4_ex1()
{
  _convex_hull = jarvis_convex_hull(_points, _point_count);

  glutIdleFunc(on_idle_event);
  glutDisplayFunc(draw);

  glutMainLoop();
}

void on_idle_event()
{
  draw();
}

void draw()
{
  glColor3f(0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT);

  draw_points(_points, _point_count);
  draw_hull(_points, _convex_hull);

  glFlush();
}
void draw_points(vertex* points, int point_count)
{
  int i;

  glBegin(GL_POINTS);
  glColor3f(1, 1, 1);

  for (i = 0; i < _point_count; ++i)
    glVertex2f(_points[i].X, _points[i].Y);

  glEnd();
}
void draw_hull(vertex* points, int_list* hull_points)
{
  int hull_point;

  glBegin(GL_LINE_LOOP);
  glColor3f(0, 1, 0);

  while (hull_points)
  {
    hull_point = hull_points->value;

    glVertex2f(points[hull_point].X, points[hull_point].Y);

    hull_points = hull_points->next;
  }

  glEnd();
}

int lexico_cmp(vertex* a, vertex* b)
{
  if (a->X < b->X)
  {
    return -1;
  }
  else if (a->X == b->X)
  {
    if (a->Y < b->Y)
    {
      return -1;
    }
    else if (a->Y == b->Y)
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  return 1;
}
int lexico_min(vertex* points, unsigned int point_count)
{
  int i;
  int min;

  if (point_count <= 0)
    return -1;

  min = 0;

  for (i = 1; i < point_count; ++i)
  {
    if (lexico_cmp(&points[i], &points[min]) < 0)
      min = i;
  }

  return min;
}

int orientation(vertex* a, vertex* b, vertex* c)
{
  int normal_dot_product;

  normal_dot_product = (a->Y - b->Y) * (c->X - a->X) + (b->X - a->X) * (c->Y - a->Y);

  if (normal_dot_product > 0)
    return ORIENTATION_CCW;
  else if (normal_dot_product == 0)
    return ORIENTATION_INLINE;
  else
    return ORIENTATION_CW;
}

double square_distance_eucl(vertex* a, vertex* b)
{
  return (pow(b->X - a->X, 2) + pow(b->Y - a->Y, 2));
}

int local_polar_min(vertex* points, unsigned int point_count, int point)
{
  int i;
  int local_polar_min;
  int current_point_orientation;

  if (point_count <= 0)
    return -1;

  for (i = 0; i < point_count; ++i)
  {
    if (i != point)
    {
      local_polar_min = i;
      break;
    }
  }

  for (i = 0; i < point_count; ++i)
  {
    if (i == point)
      continue;

    current_point_orientation = orientation(&points[point], &points[local_polar_min], &points[i]);
    if (current_point_orientation == ORIENTATION_CW)
    {
      local_polar_min = i;
    }
    else if (current_point_orientation == ORIENTATION_INLINE)
    {
      if (square_distance_eucl(&points[point], &points[i]) > square_distance_eucl(&points[point], &points[local_polar_min]))
	local_polar_min = i;
    }
  }

  return local_polar_min;
}

int_list* jarvis_convex_hull(vertex* points, unsigned int point_count)
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
