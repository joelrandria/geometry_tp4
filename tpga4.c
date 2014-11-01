#include "tpga4.h"
#include "tpga4_ex1.h"
#include "tpga4_ex2.h"
#include "tpga4_ex3.h"

int _point_count = 0;

vertex* _points_ex1 = NULL;
vertex* _points_ex2 = NULL;
vertex* _points_ex3 = NULL;
vertex* _points_ex4 = NULL;

int_list* _convex_hull = NULL;

vertex* _convex_ordonnes_ex2 = NULL;
vertex* _convex_ordonnes_ex3 = NULL;
vertex* _convex_ordonnes_ex4 = NULL;

// Exercice sélectionné
char _opt_selex = 0;

double myRandom(double a, double b)
{
	double tmp = random();
	return (a + tmp * ((b - a) / RAND_MAX));
}
#define MARGIN 20
void create_random_points()
{
  int i;

  _points_ex1 = malloc(sizeof(*_points_ex1) * _point_count);

  for (i = 0; i < _point_count; ++i)
  {
    vertex_init(&_points_ex1[i],
		myRandom(MARGIN, WINDOW_WIDTH-MARGIN),
		myRandom(MARGIN, WINDOW_HEIGHT-MARGIN));
  }

  _points_ex2 = vertex_copy(_points_ex1, _point_count);
  _points_ex3 = vertex_copy(_points_ex1, _point_count);
  _points_ex4 = vertex_copy(_points_ex1, _point_count);
}

void winInit()
{
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
}

void usage()
{
	printf("Usage: ./tpga4 -n count -m{1|2|3|4}\r\n");
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

			  sscanf(optarg, "%c", &_opt_selex);
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
		case '1': tpga4_ex1(); break;
		case '2': tpga4_ex2(); break;
		case '3': tpga4_ex3(); break;

	        case 'a':

		  tpga4_ex1();
		  tpga4_ex2();
		  tpga4_ex3();

		  break;
	}

	glutMainLoop();

	free(_points_ex1);
	free(_points_ex2);
	free(_points_ex3);
	free(_points_ex4);

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

  switch(_opt_selex)
  {
  case '1':

    draw_jarvis(_points_ex1, _point_count, _convex_hull);
    break;

  case '2':

    draw_exercice(_points_ex2, _point_count, _convex_ordonnes_ex2,
		  0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		  0, 1, 0);
    break;

  case '3':

    draw_exercice(_points_ex3, _point_count, _convex_ordonnes_ex3,
		  0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		  0, 0, 1);
    break;

  case 'a':

    draw_jarvis(_points_ex1, _point_count, _convex_hull);
    draw_exercice(_points_ex2, _point_count, _convex_ordonnes_ex2,
		  WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
		  0, 1, 0);
    draw_exercice(_points_ex3, _point_count, _convex_ordonnes_ex3,
		  0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2,
		  0, 0, 1);
    break;
  }

  glFlush();
}
void draw_points(const vertex* points, const unsigned int point_count)
{
  unsigned int i;

  glBegin(GL_POINTS);

  glColor3f(1, 1, 1);
  glPointSize(2);

  for (i = 0; i < _point_count; ++i)
    glVertex2f(points[i].X, points[i].Y);

  glEnd();
}

void draw_jarvis(const vertex* points, const unsigned int point_count, const int_list* hull_points)
{
  int hull_point;

  glViewport(0, WINDOW_HEIGHT / 2, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

  // Rendu des points
  draw_points(points, point_count);

  // Rendu de l'enveloppe convexe
  glBegin(GL_LINE_LOOP);

  glColor3f(1, 0, 0);

  while (hull_points)
  {
    hull_point = hull_points->value;
    glVertex2f(points[hull_point].X, points[hull_point].Y);
    hull_points = hull_points->next;
  }

  glEnd();
}

#define drawVertex(v) glVertex2f( v->X, v->Y)

void draw_exercice(const vertex* points, const unsigned int point_count, const vertex* hull,
		   int vp_x, int vp_y, int vp_w, int vp_h,
		   int hull_r, int hull_g, int hull_b)
{
  const vertex *v = hull;

  glViewport(vp_x, vp_y, vp_w, vp_h);

  // Rendu des points
  draw_points(points, point_count);

  // Rendu de l'enveloppe convexe
  glBegin(GL_LINE_LOOP);
  glColor3f(hull_r, hull_g, hull_b);

  while (v != NULL)
  {
    drawVertex(v);

    v = v->link[VLINK_CONVEX][VLINK_FORWARD];
    if (v == hull)
      break;
  }

  glEnd();
}
