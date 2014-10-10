#include "tpga4.h"
#include "tpga4_ex1.h"

#include <math.h>
#include <string.h>

// Variables globales communes
int _point_count = 0;
vertex* _points = 0;

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

  winInit();

  create_random_points();

  if (_opt_selex == 1)
    tpga4_ex1();

  return EXIT_SUCCESS;
}
