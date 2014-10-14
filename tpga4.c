#include "tpga4.h"
#include "tpga4_ex1.h"
#include "tpga4_ex2.h"

#include <math.h>
#include <string.h>

int _point_count = 0;
vertex* _points = 0;

int_list* _convex_hull = 0;

// Exercice sélectionné
int _opt_selex = 0;

double myRandom(double a, double b)
{
  double tmp = random();

  return (a + tmp * ((b - a) / RAND_MAX));
}
void create_random_points()
{
  int i;

  _points = malloc(sizeof(*_points) * _point_count);
  for (i = 0; i < _point_count; ++i)
  {
    _points[i].X = myRandom(0, WINDOW_WIDTH);
    _points[i].Y = myRandom(0, WINDOW_HEIGHT);
  }
}

void winInit()
{
  gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void usage()
{
  printf("Usage: ./tpga4 -n count -m{1}\r\n");
}

int main(int argc, char **argv)
{
  int c;

  opterr = 0;
  while ((c = getopt(argc, argv, "n:m:")) != EOF)
  {
    switch (c)
    {
    case 'n':

      if ((sscanf(optarg, "%d", &_point_count) != 1) || _point_count <= 0)
	_point_count = 50;
      break;

    case 'm':

      if ((sscanf(optarg, "%d", &_opt_selex) != 1) || _opt_selex <= 0)
	_opt_selex = 1;
      break;

    default: usage(); break;
    }
  }

  if (!_opt_selex)
  {
    usage();
    return EXIT_SUCCESS;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowPosition(5,5);
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow("TP Géométrie Algorithmique #4");
  glutIdleFunc(on_idle_event);
  glutDisplayFunc(draw);

  winInit();

  create_random_points();

  switch (_opt_selex)
  {
  case 1: tpga4_ex1(); break;
  case 2: tpga4_ex2(); break;
  }

  glutMainLoop();

  return EXIT_SUCCESS;
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
