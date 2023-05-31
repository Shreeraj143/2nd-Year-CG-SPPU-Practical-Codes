#include <iostream>
using namespace std;
#include <math.h>
#include <GL/glut.h>
#define sin 0.866
int x1 = 0, x2 = 550, yy1 = 200, y2 = 200;
void koch(int x1, int yy1, int x2, int y2, int n)
{
    int xx, yy, x[5], y[5], lx, ly;
    lx = (x2 - x1) / 3;
    ly = (y2 - yy1) / 3;
    x[0] = x1;
    y[0] = yy1;
    x[4] = x2;
    y[4] = y2;
    x[1] = x[0] + lx;
    y[1] = y[0] + ly;
    x[3] = x[0] + 2 * lx;
    y[3] = y[0] + 2 * ly;
    xx = x[3] - x[1];

    yy = y[3] - y[1];
    x[2] = xx * (0.5) + yy * (sin);
    y[2] = -xx * (sin) + yy * (0.5);
    x[2] = x[2] + x[1];
    y[2] = y[2] + y[1];
    if (n > 0)
    {
        koch(x[0], y[0], x[1], y[1], n - 1);
        koch(x[1], y[1], x[2], y[2], n - 1);
        koch(x[2], y[2], x[3], y[3], n - 1);
        koch(x[3], y[3], x[4], y[4], n - 1);
    }
    else
    {
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_LINES);
        glVertex2d(x[0], y[0]);
        glVertex2d(x[1], y[1]);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x[1], y[1]);
        glVertex2d(x[2], y[2]);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x[2], y[2]);
        glVertex2d(x[3], y[3]);
        glEnd();
        glBegin(GL_LINES);
        glVertex2d(x[3], y[3]);
        glVertex2d(x[4], y[4]);
        glEnd();
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    koch(x1, yy1, x2, y2, 2);
    glFlush();
}
void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 480, 0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);

    glutInitWindowSize(640, 480);
    glutCreateWindow("koch curve");
    myinit(); // used to set the OpenGL state variables dealing with viewing and attributes.
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}