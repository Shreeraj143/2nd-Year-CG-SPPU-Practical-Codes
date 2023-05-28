#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;

int option = 1;

struct Point
{
    int x;
    int y;
};

// Defined for color
struct Color
{
    float r;
    float g;
    float b;
};

// Here the datatype is Color (defined earlier)
Color getPixelColor(int x, int y)
{
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    // x and y: These are the pixel coordinates you want to read the color from. The (x, y) coordinates specify the location of the pixel in the frame buffer.
    // 1 and 1: These parameters specify the width and height of the area to read. In this case, it reads a single pixel at (x, y).
    // GL_RGB: This parameter specifies the format of the color components to read. GL_RGB indicates that the color should be returned as red, green, and blue components.
    // GL_FLOAT: This parameter specifies the data type of the color components to read. GL_FLOAT indicates that the color components should be returned as floating-point values.
    // &color: This is the memory address of the color variable where the color values will be stored. The & operator is used to obtain the address of a variable.
    return color;
}

// Used to set a given color to the pixel
void setPixelColor(int x, int y, Color color)
{
    glColor3f(color.r, color.g, color.b);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

// Floodfill algorithm
void FloodFill(int x, int y, Color oldColor, Color newColor)
{
    Color color;
    color = getPixelColor(x, y); //color variable has stored the color of the pixel
    if (color.r == oldColor.r && color.g == oldColor.g && color.b == oldColor.b) // Condition to check if oldColor and pixel color are same
    {

        setPixelColor(x, y, newColor);
        FloodFill(x + 1, y, oldColor, newColor);
        FloodFill(x, y + 1, oldColor, newColor);
        FloodFill(x - 1, y, oldColor, newColor);
        FloodFill(x, y - 1, oldColor, newColor);
    }
    return;
}

// Boundary Fill Algorithm
void Boundaryfill(int x, int y, Color oColor, Color bColor)
{
    Color color;
    color = getPixelColor(x, y);
    if ((color.r != oColor.r || color.g != oColor.g || color.b != oColor.b) 
    && (color.r !=bColor.r ||color.g != bColor.g || color.b != bColor.b))
    {
        setPixelColor(x, y, oColor);
        Boundaryfill(x + 1, y, oColor, bColor);
        Boundaryfill(x, y + 1, oColor, bColor);
        Boundaryfill(x - 1, y, oColor, bColor);
        Boundaryfill(x, y - 1, oColor, bColor);
    }
    return;
}

// Initial display
// This function is a callback function used in OpenGL to define what should be displayed on the screen.
// It is called whenever the contents of the window need to be redrawn
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_LOOP);
    glVertex2i(250, 250);
    glVertex2i(250, 300);
    glVertex2i(300, 300);
    glVertex2i(300, 250);
    glEnd();
    glFlush();
}

// Initializing conditions
// This function initializes the state of OpenGL and sets various initial conditions. It is typically called once at the beginning of the program.
void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);
    gluOrtho2D(0.0, 650.0, 0.0, 650.0);
}

// The MYmouse function is a callback function in an OpenGL program that is triggered when a mouse button is pressed or released. 
// button: An integer representing the mouse button that triggered the event. The value can be one of the predefined constants like GLUT_LEFT_BUTTON, GLUT_RIGHT_BUTTON, or GLUT_MIDDLE_BUTTON, which indicate the left, right, or middle mouse buttons, respectively.
// state: An integer representing the state of the button. It can be GLUT_DOWN when the button is pressed or GLUT_UP when the button is released.
// x and y: Integers representing the coordinates of the mouse cursor at the time of the event. The origin (0,0) is at the bottom-left corner of the window.
void MYmouse(int button, int state, int x, int y)
{
    Color newColor = {0.0f, 1.0f, 0.0f};
    Color oldColor = {0.0f, 0.0f, 0.0f}; 
    Color bColor = {1.0f, 1.0f, 1.0f};
    Color oColor = {1.0f, 0.0f, 0.0f};
    if (option == 1)
    {
        FloodFill(x, 650 - y, oldColor, newColor);
    }
    else if (option == 2)
    {
        Boundaryfill(x, 650 - y, oColor, bColor);
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(650, 650);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Polygon filling");
    cout << "1.Flood Fill Algorithm\n";
    cout << "2.Boundary Fill Algorithm\n";
    cout << "Enter your choice:\n";
    cin >> option;
    glutDisplayFunc(display);

    glutMouseFunc(MYmouse);
    myinit();
    glutMainLoop();
    return 0;
}
