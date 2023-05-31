#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

//Point class for taking the points
class Point {
public:
    float x, y;
    void setxy(float x2, float y2)//set the values of x & y
    {
        x = x2; y = y2;
    }
};

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}//calculate the factorial

float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}//calculate the binomial coefficient

Point abc[20];
int SCREEN_HEIGHT = 500;//height of display window
int points = 0;
int clicks = 4;
void myInit() {
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0,0.0,0.0);
    glPointSize(3);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,500.0);
}

void drawDot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}//draw points

void drawLine(Point p1, Point p2) {
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    glFlush();
}//draw lines

//Calculate the bezier point [generalized]
Point drawBezierGeneralized(Point PT[], double t) {
    Point P;
    P.x = 0; P.y = 0;//initially set to 0  
    for (int i = 0; i<clicks; i++)
    {
        P.x = P.x + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].x;
        //p.x +bcoff*t^i *(1-t)^(clicks-1-i) * pt[i].x
        P.y = P.y + binomial_coff((float)(clicks - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (clicks - 1 - i)) * PT[i].y;
        //p.y +bcoff*t^i *(1-t)^(clicks-1-i) * pt[i].y
    }
    return P;
}//calculate the position of a point on the curve

void myMouse(int button, int state, int x, int y) {
  // If left button was clicked
  if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    // Store where mouse was clicked, Y is backwards.
    abc[points].setxy((float)x,(float)(SCREEN_HEIGHT - y));//store the control points
    points++;

    // Draw the red  dot.
    drawDot(x, SCREEN_HEIGHT - y);//control points are plot

    // If (click-amout) points are drawn do the curve.
    if(points == clicks) 
    {
        //glColor3f(0.2,1.0,0.0);
        // Drawing the control lines
        for(int k=0;k<clicks-1;k++){
            glColor3f(0.0,0.0,0.0);
            drawLine(abc[k], abc[k+1]);
        }
        Point p1 = abc[0];
        /* Draw each segment of the curve.Make t increment in smaller amounts for a more detailed curve.*/
        for(double t = 0.0;t <= 1.0; t += 0.02)
        {
            Point p2 = drawBezierGeneralized(abc,t);
            cout<<p1.x<<"  ,  "<<p1.y<<endl;
            cout<<p2.x<<"  ,  "<<p2.y<<endl;
            cout<<endl;//show in terminal
            glColor3f(0.2,1.0,0.0);
            drawLine(p1, p2);
            p1 = p2;
        }
        glColor3f(0.0,0.0,0.0);

        points = 0;//to draw next bezier curve
    }
  }
}

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,500);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Bezier Curve");
    glutMouseFunc(myMouse);
    glutDisplayFunc(myDisplay);
    myInit();
    glutMainLoop();
    return 0;
}