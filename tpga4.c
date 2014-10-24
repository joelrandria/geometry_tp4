#include "tpga4.h"

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
#define MARGIN 20
void create_random_points()
{
	int i;

	_points = malloc(sizeof(*_points) * _point_count);
	for (i = 0; i < _point_count; ++i)
	{
	  vertex_init(&_points[i],
		      myRandom(MARGIN, WINDOW_WIDTH-MARGIN),
		      myRandom(MARGIN, WINDOW_HEIGHT-MARGIN));
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

	printf("calcul fini\n");
	
	glutMainLoop();
	
	free(_points);

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
void draw_points(const vertex* points, const unsigned int point_count)
{
	unsigned int i;

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1, 1, 1);

	for (i = 0; i < _point_count; ++i)
		glVertex2f(_points[i].X, _points[i].Y);

	glEnd();
}
void draw_hull(const vertex* points, const int_list* hull_points)
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
