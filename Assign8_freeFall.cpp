#include <iostream>
#include <cmath>
#include <GL/glut.h>

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPointSize(20);
	glColor3f(0.0f, 0.0f, 0.0f);
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

typedef struct {
	double x;
	double y;
} Point;

Point p1 = {320.0, 480.0};
Point p2 = {340.0, 480.0};
Point p3 = {340.0, 480.0};
Point p4 = {340.0, 480.0};

double time1 = 0.0;
double time2 = 0.0;
double time3 = 0.0;
double time4 = 0.0;

void calc() {
	time1 += 0.1;
	time2 += 0.1;
	time3 += 0.1;
	time4 += 0.1;

	p1.y = (-0.5*9.8)*(time1*time1)+0+480;
	p2.y = (-0.5*1.6)*(time2*time2)+0+480;
	p3.y = (-0.5*2.6)*(time3*time3)+0+480;
	p4.y = (-0.5*5.6)*(time4*time4)+0+480;
	
	if(p1.y < 0.0) {
		p1.y = 480;
		time1 = 0;
	}
	if(p2.y < 0.0) {
		p2.y = 480;
		time2 = 0;
	}
    if(p3.y < 0.0) {
		p3.y = 480;
		time3 = 0;
	}
    if(p4.y < 0.0) {
		p4.y = 480;
		time4 = 0;
	}
}

void display() {
	calc();
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2d(p1.x, p1.y);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2d(p2.x, p2.y);
        glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2d(p3.x, p3.y);
        glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2d(p4.x, p4.y);
	glEnd();
	glFlush();
}

void Timer(int value) {
	glutTimerFunc(1000 / 60, Timer, value);
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("FREEFALL");
	init();
	Timer(0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}