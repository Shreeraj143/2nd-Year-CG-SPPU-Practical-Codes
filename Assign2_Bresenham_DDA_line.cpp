#include <iostream>
#include <GL/glut.h>
#include <math.h>
#define ROUND(X)((int)X+0.5)
using namespace std;
static int menu_id;
static int submenu_id1;
static int submenu_id2;
int w = 640;
int h = 480;
void DDA_simple(float,float,float,float);
void DDA_dashed(float, float, float, float);
void DDA_dotted(float, float, float, float);
void DDA_solid(float, float, float, float);

void BH_dotted(float, float, float, float);
void BH_dashed(float, float, float, float);
void BH_simple(float, float, float, float);
void BH_solid(float, float, float, float);

void init(void) 
{
	glClearColor(1.0, 1.0, 1.0, 0); //clear buffer
	glColor3f(0.0, 0.0, 0.0); //set background colour
	glPointSize(4.0);
	gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2); //dividing screen into 4 quadrants
}
void draw() {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2d(-w / 2, 0);
	glVertex2d(w / 2, 0);
	glVertex2d(0, -h / 2);
	glVertex2d(0, h / 2);
	glEnd();
	glFlush();
}
void DDA_simple(float x1,float y1,float x2,float y2) 
{
	float dx, dy, X, Y,steps, xinc, yinc;
	int i = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy)) 
	{
		steps = abs(dx);
	}
	else 
	{
		steps = abs(dy);
	}

	xinc = dx / steps;
	yinc = dy / steps;
	X = x1;  //assign initial values(starting coordinates)
	Y = y1;
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(ROUND(X), ROUND(Y));
	glEnd();
	i = 1;
	while (i <= steps)
	{
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2f(ROUND(X), ROUND(Y));
		glEnd();
		X = X + xinc;  //changing value of xnew and ynew
		Y = Y + yinc;
		glFlush();
		i++;
	}
}

void DDA_dashed(float x1, float y1, float x2, float y2)
{
	float dx, dy, X, Y,steps;
	int i = 0;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy)) 
	{
		steps = abs(dx);
	}
	else {
		steps = abs(dy);
	}
	dx= dx / steps;
	dy = dy / steps;
	X = x1;
	Y = y1;
	glBegin(GL_POINTS);
	glVertex2f(ROUND(X), ROUND(Y));
	glEnd();
	glFlush();
	i = 1;
	count = 1;
	while(i<=steps)
	{
		X = X + dx;
		Y = Y + dy;
		if (count<=10) //draw for 10 steps
		{
			glBegin(GL_POINTS);
			glVertex2f(ROUND(X), ROUND(Y));
			glEnd();
			glFlush();
			count++;
		}
		if (count >= 10) //skip for 10 steps; count=11
		{
			count++;  //count is incremented 12,13,etc
			if (count == 20) //reset count if 20 steps skipped
			{
				count = 1;
			}
		}
		i++;
	}


}
void DDA_dotted(float x1, float y1, float x2, float y2) 
{
	float dx, dy, X, Y, steps;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy)) 
	{
		steps = abs(dx);
	}
	else
	{
		steps = abs(dy);
	}
	dx = dx / steps;
	dy = dy / steps;
	X = x1;
	Y = y1;
	glBegin(GL_POINTS);
	glVertex2f(ROUND(X), ROUND(Y));
	glEnd();
	int count = 1;
	int i = 1;
	while (i <= steps) 
	{
		X = X + dx;
		Y = Y + dy;
		if (count % 10 == 0)   //count=10(dot),20(dot) etc...1%10==0
		{
			glBegin(GL_POINTS);
			glVertex2f(ROUND(X), ROUND(Y));
			glEnd();
			glFlush();
		}
		count++;
		i++;
	}


}

void DDA_solid(float x1, float y1, float x2, float y2) 
{
	float dx, dy, steps, X, Y;
	dx = x2 - x1;
	dy = y2 - y1;
	if (abs(dx) >= abs(dy)) 
	{
		steps = abs(dx);
	}
	else 
	{
		steps = abs(dy);
	}
	dx = dx / steps;
	dy = dy / steps;
	X = x1;
	Y = y1;
	int i = 0;
	while (i <= steps) 
	{
		glPointSize(8.0); //same as simple, only point size has been increased
		glBegin(GL_POINTS);
		glVertex2f(ROUND(X), ROUND(Y));
		glEnd();
		X = X + dx;
		Y = Y + dy;
		glFlush();
		i++;
	}
}


void BH_simple(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * (dy)) - (dx); //decision parameter
	ds = 2 * (dy);  //if value of decision parameter<0
	dt = 2 * ((dy)-(dx));  //if value of decision parameter>0
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	while (x1 < x2)
	{
		x1++;
		if (di < 0)  //di=di+2dy=>di=di+ds; ynew=yold; xnew=xold+1
		{
			di += ds;
		}
		else  //di=di+2(dy-dx)=>di=di+dt; ynew=yold+1; xnew+xold+1
		{
			y1++;
			di += dt;
		}
		glPointSize(4.0);
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		glEnd();
	}
}
void BH_dashed(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * dy) - dx;
	ds = 2 * dy;
	dt = 2 * (dy - dx);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	count = 1;
	while (x1 < x2)
	{
		x1++;
		if (di < 0)
		{
			di += ds;
		}
		else
		{
			y1++;
			di += dt;
		}
		if (count < 6)  //draw for 6 steps
		{
			glPointSize(4.0);
			glBegin(GL_POINTS);
			glVertex2f(x1, y1);
			glEnd();
			count++;
		}
		if (count >= 6) 
		{
			count++;  //increment count
			if (count == 12)
			{
				count = 0;
			}
		}
	}
}
void BH_dotted(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * dy) - dx;
	ds = 2 * dy;
	dt = 2 * (dy - dx);
	glPointSize(4.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	count = 1;
	while (x1 < x2)
	{
		x1++;
		if (di < 0)
		{
			di += ds;
		}
		else
		{
			y1++;
			di += dt;
		}
		if (count % 10 == 0)
		{
			glPointSize(4.0);
			glBegin(GL_POINTS);
			glVertex2f(x1, y1);
			glEnd();
		}
		count++;
	}
}


void BH_solid(float x1, float y1, float x2, float y2)
{
	float dx, dy, di, ds, dt;
	int count = 0;
	dx = x2 - x1;
	dy = y2 - y1;
	di = (2 * dy) - dx;
	ds = 2 * dy;
	dt = 2 * (dy - dx);
	glPointSize(7.0);
	glBegin(GL_POINTS);
	glVertex2f(x1, y1);
	glEnd();
	while (x1 < x2)
	{
		x1++;
		if (di < 0)
		{
			di += ds;
		}
		else
		{
			y1++;
			di += dt;
		}
		glPointSize(8.0);
		glBegin(GL_POINTS);
		glVertex2f(x1, y1);
		glEnd();
	}
}

void menu_dda(int a) 
{
	switch (a) 
	{
	case 1:
		DDA_simple(10, 50, 150, 200);
		break;
	case 2:
		DDA_dashed(10, 50, 150, 200);
		break;
	case 3:
		DDA_dotted(10, 50, 150, 200);
		break;
	case 4:
		DDA_solid(10, 50, 150, 200);
		break;
	}

}
void menu_bh(int a) 
{
	switch (a) 
	{
	case 1:
		BH_simple(10, 50, 150, 200);
		break;
	case 2:
		BH_dashed(10, 50, 150, 200);
		break;
	case 3:
		BH_dotted(10, 50, 150, 200);
		break;
	case 4:
		BH_solid(10, 50, 150, 200);
		break;
	}

}




int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("DDA and Bresenham");
	glutDisplayFunc(draw);
	submenu_id1=glutCreateMenu(menu_dda);
	glutAddMenuEntry("1.Simple Line", 1);
	glutAddMenuEntry("2.Dashed Line", 2);
	glutAddMenuEntry("3.Dotted Line", 3);
	glutAddMenuEntry("4.Solid Line", 4);

	submenu_id2 = glutCreateMenu(menu_bh);
	glutAddMenuEntry("1.Simple Line", 1);
	glutAddMenuEntry("2.Dashed Line", 2);
	glutAddMenuEntry("3.Dotted Line", 3);
	glutAddMenuEntry("4.Solid Line", 4);

	menu_id = glutCreateMenu(menu_dda);
	glutAddSubMenu("DDA Algorithm", submenu_id1);
	glutAddSubMenu("Bresenham Algorithm", submenu_id2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();
	glutMainLoop();
	return(0);

}