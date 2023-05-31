#include<iostream>
#include<math.h>
using namespace std;
#include<GL/glut.h>
#define ROUND(x) int(x)+0.5
int w = 640;
int h = 480;


int breshnam(float,float,float);
int plotpoint(float,float,float,float);

void Myinit()
{
glClearColor(1.0f,1.0f,1.0f,0);
glColor3f(0.0,0.0,0.0);
glPointSize(4.0);
gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}


void Mydisplay()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glBegin(GL_LINES);
	glVertex2d(-w / 2, 0);
	glVertex2d(w / 2, 0);
	glVertex2d(0, -h / 2);
	glVertex2d(0, h / 2);
	glEnd();
	glFlush();
	
breshnam(100,100,50);

glFlush();

}



int breshnam(float xc,float yc,float r)
{
	int x,y;
	x=0;
	y=r;
	float s=3-2*r;
	while(x<=y)
	{
		if(s<0)
			s=s+4*x+6;
		else
		{
			s=s+4*(x-y)+10;
			y--;	
			
		}
		x++;
		plotpoint(xc,yc,x,y);
	}
return 0;
}
int plotpoint(float xc,float yc,float x,float y)
{
	glBegin(GL_POINTS);
	glVertex2i(xc+x,yc+y);
	glVertex2i(xc+x,yc-y);
	glVertex2i(xc-x,yc+y);
	glVertex2i(xc-x,yc-y);
	glVertex2i(xc+y,yc+x);
	glVertex2i(xc+y,yc-x);
	glVertex2i(xc-y,yc+x);
	glVertex2i(xc-y,yc-x);
	
	glEnd();
	glFlush();
		
return 0;
}



int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowPosition(0,0);
glutInitWindowSize(800,600);
glutCreateWindow("Bresenham circle");
Myinit();
glutDisplayFunc(Mydisplay);
glutMainLoop();
}
