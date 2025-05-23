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

// Game Speed
int FPS = 50;
// Game Track
int start = 0; // Changed to 0 to show home page first
int gv = 0;
int level = 0;
int home = 1; // Added home page flag

// Track Score
int score = 0;

// Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

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
const int font3 = (int)GLUT_BITMAP_8_BY_13;

void renderBitmapString(float x, float y, void *font, const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

// Added function to display home page with car shape
void homePage()
{
    // Green background already set in display function

    // Title
    glColor3f(1.0, 1.0, 0.0); // Yellow color
    glPushMatrix();
    glTranslatef(30, 80, 0.0);
    glScalef(1.5, 1.5, 1.0);
    renderBitmapString(0, 0, (void *)font1, "RACING CAR GAME");
    glPopMatrix();


// Draw centered car
    // Front Tire
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(46, 45);
    glVertex2f(46, 47);
    glVertex2f(54, 47);
    glVertex2f(54, 45);
    glEnd();

    // Back Tire
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(46, 41);
    glVertex2f(46, 43);
    glVertex2f(54, 43);
    glVertex2f(54, 41);
    glEnd();

    // Car Body
    glColor3f(0.678, 1.000, 0.184);
    glBegin(GL_POLYGON);
    glVertex2f(48, 41);
    glVertex2f(48, 48);
    glColor3f(0.000, 0.545, 0.545);
    glVertex2f(50, 50);
    glVertex2f(52, 48);
    glVertex2f(52, 41);
    glEnd();

    // Start Button with 3D effect (similar to retry button style)
    // Button shadow
    glColor3f(0.0, 0.3, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(37.5, 24.5);
    glVertex2f(62.5, 24.5);
    glVertex2f(62.5, 28.5);
    glVertex2f(37.5, 28.5);
    glEnd();

    // Main button
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(38, 25);
    glVertex2f(62, 25);
    glVertex2f(62, 29);
    glVertex2f(38, 29);
    glEnd();

    // Button highlight
    glColor3f(0.5, 1.0, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(38, 29);
    glVertex2f(39, 28);
    glVertex2f(61, 28);
    glVertex2f(62, 29);
    glEnd();

    // Start text with shadow for better readability
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(43.2, 26, (void *)font1, "START");
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(43, 26.2, (void *)font1, "START");

    // Instructions
    glColor3f(1.0, 1.0, 1.0);
    renderBitmapString(30, 15, (void *)font3, "Use Arrow Keys to Control the Car");
    renderBitmapString(30, 12, (void *)font3, "UP/DOWN: Adjust Speed");
    renderBitmapString(30, 9, (void *)font3, "LEFT/RIGHT: Move Car");
    renderBitmapString(30, 6, (void *)font3, "ESC: Exit Game");
}

void startGame()
{
    // Road
    glColor3f(0.412, 0.412, 0.412);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    // Road Left Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(23, 100);
    glVertex2f(23, 0);
    glEnd();

    // Road Right Border
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(77, 0);
    glVertex2f(77, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    // Road Middle Border
    // TOP
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivTop + 80);
    glVertex2f(48, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 80);
    glEnd();

    // Middle
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();

    // Bottom
    glColor3f(1.000, 1.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm + 0);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 0);
    glEnd();

    // Only update movement and score if the game is active (start == 1)
    if (start)
    {
        // Update road dividers
        roadDivTop--;
        if (roadDivTop < -100)
        {
            roadDivTop = 20;
            score++;
        }

        roadDivMdl--;
        if (roadDivMdl < -60)
        {
            roadDivMdl = 60;
            score++;
        }

        roadDivBtm--;
        if (roadDivBtm < -20)
        {
            roadDivBtm = 100;
            score++;
        }

        // Update enemy car positions
        // Car 1
        car1--;
        if (car1 < -100)
        {
            car1 = 0;
            lrIndex1 = lrIndex;
        }
        // Kill check car1
        if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10))
        {
            start = 0;
            gv = 1;
        }

        // Car 2
        car2--;
        if (car2 < -100)
        {
            car2 = 0;
            lrIndex2 = lrIndex;
        }
        // Kill check car2
        if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10))
        {
            start = 0;
            gv = 1;
        }

        // Car 3
        car3--;
        if (car3 < -100)
        {
            car3 = 0;
            lrIndex3 = lrIndex;
        }
        // Kill check car3
        if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10))
        {
            start = 0;
            gv = 1;
        }

        // Update level and speed based on score
        if (score % 50 == 0)
        {
            int last = score / 50;
            if (last != level)
            {
                level = score / 50;
                FPS = FPS + 2;
            }
        }
    }

    // Score Board (displayed regardless of game state)
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(80, 97);
    glVertex2f(100, 97);
    glVertex2f(100, 98 - 8);
    glVertex2f(80, 98 - 8);
    glEnd();

    // Print Score
    char buffer[50];
    sprintf(buffer, "SCORE: %d", score);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95, (void *)font3, buffer);
    // Speed Print
    char buffer1[50];
    sprintf(buffer1, "SPEED:%dKm/h", FPS);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 2, (void *)font3, buffer1);
    // Level Print
    char level_buffer[50];
    sprintf(level_buffer, "LEVEL: %d", level);
    glColor3f(0.000, 1.000, 0.000);
    renderBitmapString(80.5, 95 - 4, (void *)font3, level_buffer);

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

    // Display Game Over message if game is over
    if (gv == 1) {
        // Background shadow for "GAME OVER" text (for 3D effect)
        glColor3f(0.5, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(35.3, 59.7, 0.0);
        glScalef(1.2, 1.2, 1.0);
        renderBitmapString(0, 0, (void *)font1, "GAME OVER");
        glPopMatrix();

        // Main "GAME OVER" text
        glColor3f(1.0, 0.0, 0.0);
        glPushMatrix();
        glTranslatef(35, 60, 0.0);
        glScalef(1.2, 1.2, 1.0);
        renderBitmapString(0, 0, (void *)font1, "GAME OVER");
        glPopMatrix();

        // Score text with glow effect
        char buffer2[50];
        sprintf(buffer2, "Your Score is : %d", score);

        // Score text shadow
        glColor3f(0.0, 0.3, 0.0);
        renderBitmapString(33.2, 55.8, (void *)font1, buffer2);

        // Main score text
        glColor3f(0.0, 1.0, 0.0);
        renderBitmapString(33, 56, (void *)font1, buffer2);

        // Retry Button with 3D effect
        // Button shadow
        glColor3f(0.0, 0.3, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(37.5, 37.5);
        glVertex2f(58.5, 37.5);
        glVertex2f(58.5, 41.5);
        glVertex2f(37.5, 41.5);
        glEnd();

        // Main button
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(38, 38);
        glVertex2f(58, 38);
        glVertex2f(58, 42);
        glVertex2f(38, 42);
        glEnd();

        // Button highlight
        glColor3f(0.5, 1.0, 0.5);
        glBegin(GL_POLYGON);
        glVertex2f(38, 42);
        glVertex2f(39, 41);
        glVertex2f(57, 41);
        glVertex2f(58, 42);
        glEnd();

        // Retry text with shadow for better readability
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(43.2, 39, (void *)font1, "Retry");
        glColor3f(1.0, 1.0, 1.0);
        renderBitmapString(43, 39.2, (void *)font1, "Retry");

        // Exit Button with 3D effect
        // Button shadow
        glColor3f(0.5, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(37.5, 31.5);
        glVertex2f(58.5, 31.5);
        glVertex2f(58.5, 35.5);
        glVertex2f(37.5, 35.5);
        glEnd();

        // Main button
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(38, 32);
        glVertex2f(58, 32);
        glVertex2f(58, 36);
        glVertex2f(38, 36);
        glEnd();

        // Button highlight
        glColor3f(1.0, 0.5, 0.5);
        glBegin(GL_POLYGON);
        glVertex2f(38, 36);
        glVertex2f(39, 35);
        glVertex2f(57, 35);
        glVertex2f(58, 36);
        glEnd();

        // Exit text with shadow for better readability
        glColor3f(0.0, 0.0, 0.0);
        renderBitmapString(44.2, 33, (void *)font1, "Exit");
        glColor3f(1.0, 1.0, 1.0);
        renderBitmapString(44, 33.2, (void *)font1, "Exit");
    }
}

// Modified mouseClick function to handle home page button
void mouseClick(int button, int state, int x, int y) {
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    float worldX = x * 100.0 / glutGet(GLUT_WINDOW_WIDTH);
    float worldY = (windowHeight - y) * 100.0 / windowHeight;

    // Handle home page start button
    if (home == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Start button bounds (38 to 62 x, 25 to 29 y)
        if (worldX >= 38 && worldX <= 62 && worldY >= 25 && worldY <= 29) {
            // Start the game
            home = 0;
            start = 1;
        }
    }

    // Handle game over screen buttons
    if (gv == 1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Retry button bounds (38 to 58 x, 38 to 42 y)
        if (worldX >= 38 && worldX <= 58 && worldY >= 38 && worldY <= 42) {
            // Reset game
            score = 0;
            level = 0;
            FPS = 50;
            start = 1;
            gv = 0;
            car1 = 0;
            car2 = 35;
            car3 = 70;
            roadDivTop = roadDivMdl = roadDivBtm = 0;
            lrIndex = lrIndex1 = lrIndex2 = lrIndex3 = 0;
        }

        // Exit button bounds (38 to 58 x, 32 to 36 y)
        if (worldX >= 38 && worldX <= 58 && worldY >= 32 && worldY <= 36) {
            exit(0);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.000, 0.392, 0.000, 1); // Background color

    // Display appropriate screen based on game state
    if (home) {
        homePage();
    } else {
        startGame();
    }

    glFlush();
    glutSwapBuffers();
}

void spe_key(int key, int x, int y)
{
    // Only process key inputs when game is active
    if (start && !home) {
        switch (key)
        {
        case GLUT_KEY_DOWN:
            if (FPS > (50 + (level * 2)))
                FPS = FPS - 2;
            break;
        case GLUT_KEY_UP:
            FPS = FPS + 2;
            break;

        case GLUT_KEY_LEFT:
            if (lrIndex >= 0)
            {
                lrIndex = lrIndex - (FPS / 10);
                if (lrIndex < 0)
                {
                    lrIndex = -1;
                }
            }
            break;

        case GLUT_KEY_RIGHT:
            if (lrIndex <= 44)
            {
                lrIndex = lrIndex + (FPS / 10);
                if (lrIndex > 44)
                {
                    lrIndex = 45;
                }
            }
            break;

        default:
            break;
        }
    }
}

void keyHandler(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // ESC key
        exit(0);
        break;
    default:
        break;
    }
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

    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(keyHandler);
    glutMouseFunc(mouseClick);

    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);

    glutTimerFunc(1000, timer, 0);
    glutMainLoop();

    return 0;
}
