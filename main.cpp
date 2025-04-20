#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Game Speed - Frames per second, controlling the game�s refresh rate
int FPS = 50;

// Game Track
int start = 1; // Indicates the game is running
int gv = 0;    // Game-over flag (0 = game ongoing, 1 = game over)

// Form move track
int roadDivTopMost = 0;
int roadDiv1 = 0;
int roadDiv2 = 20;
int roadDiv3 = 40;
int roadDiv4 = 60;
int roadDiv5 = 80;

// For Car Left / RIGHT
int lrIndex = 0;

// Car Coming
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

// For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

void startGame()
{
    glColor3f(0.412, 0.412, 0.412); // road background
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    // Left Border
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(23, 100);
    glVertex2f(23, 0);
    glEnd();

    // Right Border
    glBegin(GL_POLYGON);
    glVertex2f(77, 0);
    glVertex2f(77, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    // Middle road lines (five thinner lines)
    glColor3f(1.0, 1.0, 0.0);
    // Line 1
    glBegin(GL_POLYGON);
    glVertex2f(49, roadDiv1);
    glVertex2f(49, roadDiv1 + 10);
    glVertex2f(51, roadDiv1 + 10);
    glVertex2f(51, roadDiv1);
    glEnd();
    // Line 2
    glBegin(GL_POLYGON);
    glVertex2f(49, roadDiv2);
    glVertex2f(49, roadDiv2 + 10);
    glVertex2f(51, roadDiv2 + 10);
    glVertex2f(51, roadDiv2);
    glEnd();
    // Line 3
    glBegin(GL_POLYGON);
    glVertex2f(49, roadDiv3);
    glVertex2f(49, roadDiv3 + 10);
    glVertex2f(51, roadDiv3 + 10);
    glVertex2f(51, roadDiv3);
    glEnd();
    // Line 4
    glBegin(GL_POLYGON);
    glVertex2f(49, roadDiv4);
    glVertex2f(49, roadDiv4 + 10);
    glVertex2f(51, roadDiv4 + 10);
    glVertex2f(51, roadDiv4);
    glEnd();
    // Line 5
    glBegin(GL_POLYGON);
    glVertex2f(49, roadDiv5);
    glVertex2f(49, roadDiv5 + 10);
    glVertex2f(51, roadDiv5 + 10);
    glVertex2f(51, roadDiv5);
    glEnd();

    // MAIN car
    // Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 5);
    glVertex2f(lrIndex + 26 - 2, 7);
    glVertex2f(lrIndex + 30 + 2, 7);
    glVertex2f(lrIndex + 30 + 2, 5);
    glEnd();
    // Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26 - 2, 1);
    glVertex2f(lrIndex + 26 - 2, 3);
    glVertex2f(lrIndex + 30 + 2, 3);
    glVertex2f(lrIndex + 30 + 2, 1);
    glEnd();
    // Car Body
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26, 1);
    glVertex2f(lrIndex + 26, 8);
    glColor3f(0.000, 0.545, 0.545);

    glVertex2f(lrIndex + 28, 10);
    glVertex2f(lrIndex + 30, 8);
    glVertex2f(lrIndex + 30, 1);
    glEnd();

    // Opposite car 1
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 4);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26, car1 + 100);
    glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
    glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 30, car1 + 100);
    glEnd();

    car1--;
    if (car1 < -100)
    {
        car1 = 0;
        lrIndex1 = lrIndex;
    }
    // KIll check car1
    if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10))
    {
        start = 0;
        gv = 1;
    }

    // Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 4);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26, car2 + 100);
    glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 28, car2 + 100 - 9);
    glVertex2f(lrIndex2 + 30, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 30, car2 + 100);
    glEnd();
    car2--;
    if (car2 < -100)
    {
        car2 = 0;
        lrIndex2 = lrIndex;
    }
    // KIll check car2
    if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10))
    {
        start = 0;
        gv = 1;
    }

    // Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
    glEnd();
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 30, car3 + 100);
    glEnd();
    car3--;
    if (car3 < -100)
    {
        car3 = 0;
        lrIndex3 = lrIndex;
    }
    // KIll check car3
    if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10))
    {
        start = 0;
        gv = 1;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    startGame();
    glutSwapBuffers();
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 650);
    glutInitWindowPosition(200, 20);
    glutCreateWindow("Car Game");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glClearColor(0.184, 0.310, 0.310, 1);

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
