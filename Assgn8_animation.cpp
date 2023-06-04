#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>

float x_position = -10.0;
int state = 1;

void display(){
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glVertex2f(x_position, 1.0);
    glVertex2f(x_position, -1.0);
    glVertex2f(x_position+2, -1.0);
    glVertex2f(x_position+2, 1.0);
    glEnd();

    glutSwapBuffers();
}

void init(){
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-10, 10, -10, 10);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);

    switch(state){
        case 1:
            if(x_position<8)
                x_position += 0.15;
            else
                state = -1;
            break;

        case -1:
            if(x_position > -10)
                x_position -= 0.15;
            else
                state = 1;
            break;
        }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 200);
    glutInitWindowSize(640, 780);
    glutCreateWindow("Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}