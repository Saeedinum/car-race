#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

//Game Speed
int FPS = 50;
//Game Track
int start = 1;
int gv = 0;
int level = 0;

//Track Score
int score = 0;

//Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

//For Car Left / RIGHT
int lrIndex = 0;

//Car Coming
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

//For Display TEXT
const int font1 = (int)GLUT_BITMAP_TIMES_ROMAN_24;
const int font2 = (int)GLUT_BITMAP_HELVETICA_18;
const int font3 = (int)GLUT_BITMAP_8_BY_13;

char s[30];

void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void tree(int x, int y) {
    int newx = x;
    int newy = y;
    glColor3f(0.871, 0.722, 0.529);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11, newy + 55);
    glVertex2f(newx + 12, newy + 45);
    glVertex2f(newx + 10, newy + 45);
    glEnd();
    glColor3f(0.133, 0.545, 0.133);
    glBegin(GL_TRIANGLES);
    glVertex2f(newx + 11, newy + 58);
    glVertex2f(newx + 15, newy + 52);
    glVertex2f(newx + 7, newy + 52);
    glEnd();
}

void startGame() {
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0); glVertex2f(20, 100);
    glVertex2f(80, 100); glVertex2f(80, 0);
    glEnd();

    // Left Border
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0); glVertex2f(20, 100);
    glVertex2f(23, 100); glVertex2f(23, 0);
    glEnd();

    // Right Border
    glBegin(GL_POLYGON);
    glVertex2f(77, 0); glVertex2f(77, 100);
    glVertex2f(80, 100); glVertex2f(80, 0);
    glEnd();

    // Middle road lines (top, middle, bottom)
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivTop + 80);
    glVertex2f(48, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 80);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    startGame();
    glutSwapBuffers();
}

void timer(int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, timer, 0);
}

void spe_key(int key, int x, int y) {
    // Disable movement of the car (no change to lrIndex)
    //if (key == GLUT_KEY_LEFT && lrIndex > 0) {
    //    lrIndex -= 2;
    //} else if (key == GLUT_KEY_RIGHT && lrIndex < 44) {
    //    lrIndex += 2;
    //}
}

void processKeys(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Esc key to exit
}

int main(int argc, char* argv[]) {
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
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
