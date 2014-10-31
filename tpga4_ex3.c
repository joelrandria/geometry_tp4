#include "tpga4_ex3.h"

/*! Affichage.
 *\warning Particularite: "callback function", ie pas d'argument transmis... Tout en global, yeurk!
 */
void display(void)
{
	glColor3f(0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(1.0, 1.0, 1.0);
	
	vertex* v = _points[0], *temp;
	if(v == NULL)
		return;
	
	while((temp = v.link[VLINK_LEXICO][VLINK_BACKWARD]) != NULL)
		v = temp;
	
	temp = v; 	//pour retracer les contours des triangles par dessus. pour le fun.
	
	glBegin(GL_TRIANGLE_STRIP);
	do
	{
		glVertex2f(v.X, v.Y);
		v = v.link[VLINK_LEXICO][VLINK_FORWARD];
	}
	while(v != NULL);
	glEnd();
	
	////////////////////////////////////////////////////////////////////
	v = temp;
	vertex* temp2 = v;;
	
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
		glVertex2f(v.X, v.Y);
		temp = v.link[VLINK_LEXICO][VLINK_FORWARD];
		glVertex2f(temp.X, temp.Y);
	glEnd();
	
	temp2 = temp.link[VLINK_LEXICO][VLINK_FORWARD];
	while(temp2 != NULL)
	{
		glBegin(GL_LINE_STRIP);
			glVertex2f(v.X, v.Y);
			glVertex2f(temp2.X, temp2.Y);
			glVertex2f(temp.X, temp.Y);
			v = temp;
			temp = temp2;
		glEnd();
		temp2 = temp.link[VLINK_LEXICO][VLINK_FORWARD];
	}
	////////////////////////////////////////////////////////////////////
	
	glFlush();
}

void tpga4_ex3()
{
  glutDisplayFunc(display);
  glutMainLoop();
}
