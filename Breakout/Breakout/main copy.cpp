//
//  main.cpp
//  Tarea5
//
//  Created by Alejandro Guerrero on 1/31/13.
//  Copyright (c) 2013 Alejandro Guerrero. All rights reserved.
//

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <stdlib.h>

using namespace std;

int	screenWidth = 640, screenHeight = 640;

int xDir = 1;
int yDir = -1;
double xChange = 0.0;
double yChange = 0.01;
double timeRedraw = 8;

double ballX1 = -0.05;
double ballX2 = +0.05;
double ballY1 = -0.05;
double ballY2 = +0.05;
double radius = 0.03;   

double posXBall = 0.0;
double posYBall = 0.0;

double padY1 = -1.00;
double padY2 = -0.95;
double padX1 = -0.15;
double padX2 = +0.15;

// 0 for playing, 1 for game over
int state = 0;

int blockLevel[20][20] = {0};





float colorsAmbient[24][3] = {  0.0215 ,  0.1745 ,  0.0215 ,
    0.135 ,  0.2225 ,  0.1575 ,
    0.05375 ,  0.05 ,  0.06625 ,
    0.25 ,  0.20725 ,  0.20725 ,
    0.1745 ,  0.01175 ,  0.01175 ,
    0.1 ,  0.18725 ,  0.1745 ,
    0.329412 ,  0.223529 ,  0.027451 ,
    0.2125 ,  0.1275 ,  0.054 ,
    0.25 ,  0.25 ,  0.25 ,
    0.19125 ,  0.0735 ,  0.0225 ,
    0.24725 ,  0.1995 ,  0.0745 ,
    0.19225 ,  0.19225 ,  0.19225 ,
    0.0 ,  0.0 ,  0.0 ,
    0.0 ,  0.1 ,  0.06 ,
    0.0 ,  0.0 ,  0.0 ,
    0.0 ,  0.0 ,  0.0 ,
    0.0 ,  0.0 ,  0.0 ,
    0.0 ,  0.0 ,  0.0 ,
    0.02 ,  0.02 ,  0.02 ,
    0.0 ,  0.05 ,  0.05 ,
    0.0 ,  0.05 ,  0.0 ,
    0.05 ,  0.0 ,  0.0 ,
    0.05 ,  0.05 ,  0.05 ,
    0.05 ,  0.05 ,  0.0 ,
};

float colorsDiffuse[24][3] = {  0.07568 ,  0.61424 ,  0.07568 ,
    0.54 ,  0.89 ,  0.63 ,
    0.18275 ,  0.17 ,  0.22525 ,
    1 ,  0.829 ,  0.829 ,
    0.61424 ,  0.04136 ,  0.04136 ,
    0.396 ,  0.74151 ,  0.69102 ,
    0.780392 ,  0.568627 ,  0.113725 ,
    0.714 ,  0.4284 ,  0.18144 ,
    0.4 ,  0.4 ,  0.4 ,
    0.7038 ,  0.27048 ,  0.0828 ,
    0.75164 ,  0.60648 ,  0.22648 ,
    0.50754 ,  0.50754 ,  0.50754 ,
    0.01 ,  0.01 ,  0.01 ,
    0.0 ,  0.50980392 ,  0.50980392 ,
    0.1 ,  0.35 ,  0.1 ,
    0.5 ,  0.0 ,  0.0 ,
    0.55 ,  0.55 ,  0.55 ,
    0.5 ,  0.5 ,  0.0 ,
    0.01 ,  0.01 ,  0.01 ,
    0.4 ,  0.5 ,  0.5 ,
    0.4 ,  0.5 ,  0.4 ,
    0.5 ,  0.4 ,  0.4 ,
    0.5 ,  0.5 ,  0.5 ,
    0.5 ,  0.5 ,  0.4 ,
};

float colorsSpecular[24][3] ={  0.633 ,  0.727811 ,  0.633 ,
    0.316228 ,  0.316228 ,  0.316228 ,
    0.332741 ,  0.328634 ,  0.346435 ,
    0.296648 ,  0.296648 ,  0.296648 ,
    0.727811 ,  0.626959 ,  0.626959 ,
    0.297254 ,  0.30829 ,  0.306678 ,
    0.992157 ,  0.941176 ,  0.807843 ,
    0.393548 ,  0.271906 ,  0.166721 ,
    0.774597 ,  0.774597 ,  0.774597 ,
    0.256777 ,  0.137622 ,  0.086014 ,
    0.628281 ,  0.555802 ,  0.366065 ,
    0.508273 ,  0.508273 ,  0.508273 ,
    0.5 ,  0.5 ,  0.5 ,
    0.50196078 ,  0.50196078 ,  0.50196078 ,
    0.45 ,  0.55 ,  0.45 ,
    0.7 ,  0.6 ,  0.6 ,
    0.7 ,  0.7 ,  0.7 ,
    0.6 ,  0.6 ,  0.5 ,
    0.4 ,  0.4 ,  0.4 ,
    0.04 ,  0.7 ,  0.7 ,
    0.04 ,  0.7 ,  0.04 ,
    0.7 ,  0.04 ,  0.04 ,
    0.7 ,  0.7 ,  0.7 ,
    0.7 ,  0.7 ,  0.04 ,
};


float mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
float mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
float mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess[]= {50.0f};

// 0  "emerald"
// 1  "jade"
// 2  "obsidian"
// 3  "pearl"
// 4  "ruby"
// 5  "turquoise"
// 6  "brass"
// 7  "bronze"
// 8  "chrome"
// 9  "copper"
// 10 "gold"
// 11 "silver"
// 12 "black"
// 13 "cyan"
// 14 "green"
// 15 "red"
// 16 "white"
// 17 "yellow plastic"
// 18 "black"
// 19 "cyan"
// 20 "green"
// 21 "red"
// 22 "white"
// 23 "yellow rubber"
void changeMaterial(int i)
{
    mat_ambient[0] = colorsAmbient[i][0];
    mat_ambient[1] = colorsAmbient[i][1];
    mat_ambient[2] = colorsAmbient[i][2];
    mat_diffuse[0] = colorsDiffuse[i][0];
    mat_diffuse[1] = colorsDiffuse[i][1];
    mat_diffuse[2] = colorsDiffuse[i][2];
    mat_specular[0] = colorsSpecular[i][0];
    mat_specular[1] = colorsSpecular[i][1];
    mat_specular[2] = colorsSpecular[i][2];
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
}







void printBlockLevelMatrix()
{
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            cout << blockLevel[i][j] << " ";
        }
        cout << "\n";
    }
}

/*
 * Every method that generates a level should initialize a 20x20
 * matrix called blockLevel. Each number in the matrix will be used to draw
 * the different blocks in the level.
 * A ___ means ___:
 *      0 - no block
 *      1 - blue block
 *      2 - red block
 *      3 - yellow block
 */
static void generateRandomBlockLevel(int numberRows)
{
    srand ((unsigned) time(NULL));
    
    for (int i = 0; i < numberRows; i++) {
        for (int j = 0; j < 20; j++) {
            blockLevel[i][j] = rand() % 4;
        }
    }
    
    for (int i = numberRows; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            blockLevel[i][j] = 0;
        }
    }
}

static void generateRandomBlockLevelSymmetrical(int numberRows)
{
    srand ((unsigned) time(NULL));
    
    for (int i = 0; i < numberRows; i++) {
        for (int j = 0; j < 10; j++) {
            blockLevel[i][j] = rand() % 4;
            blockLevel[i][19-j] = blockLevel[i][j];
            
            // cout << i << "," << j << " and " << i << "," << 19-j << "\n";
        }
    }
    
    for (int i = numberRows; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            blockLevel[i][j] = 0;
        }
    }
    
    // printBlockLevelMatrix();
}









void drawBlueCube(double x, double y)
{
    glPushMatrix();
    
    changeMaterial(13);             //cyan
    glTranslated(x + 0.05, y + 0.05, 0);
    //glRotated(20, 1, 1, 1);
    glutSolidCube(0.095);
    
    glPopMatrix();
}

void drawRedCube(double x, double y)
{
    glPushMatrix();
    
    changeMaterial(4);              //ruby
    glTranslated(x + 0.05, y + 0.05, 0);
    glutSolidCube(0.095);
    
    glPopMatrix();
}

void drawYellowCube(double x, double y)
{
    glPushMatrix();
    
    changeMaterial(10);             //gold
    glTranslated(x + 0.05, y + 0.05, 0);
    glutSolidCube(0.095);
    
    glPopMatrix();
}

/*
 * A ___ means ___:
 *      0 - no block
 *      1 - blue block
 *      2 - red block
 *      3 - yellow block
 */
static void drawBlocks()
{
    double x = -1.0;
    double y = 0.9;
    int type = 0;
    
    for (int i = 0; i < 20; i++) {
        x = -1.0;
        
        for (int j = 0; j < 20; j++) {
            // get type of square
            type = blockLevel[i][j];
            
            // draw type of square
            switch (type) {
                case 0:
                    break;
                case 1:
                    drawBlueCube(x, y);
                    break;
                case 2:
                    drawRedCube(x, y);
                    break;
                case 3:
                    drawYellowCube(x, y);
                    break;
                default:
                    break;
            }
            
            // update x
            x += 0.1;
        }
        
        y -= 0.1;
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Lights
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position[] = {2.0f, 2.0f, 3.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    // Camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winHt = 1.0;
    glOrtho(-winHt, winHt, -winHt, winHt, -winHt, winHt);
    gluLookAt(0, 0.1, 0.4, 0, 0, 0, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Draw left paddle
    changeMaterial(0);              //emerald
    
    glBegin(GL_QUADS);
    glVertex2f(padX1, padY1);
    glVertex2f(padX1, padY2);
    glVertex2f(padX2, padY2);
    glVertex2f(padX2, padY1);
    glEnd();
    
    // Draw blocks
    drawBlocks();
    
    // Draw ball
    changeMaterial(3);              //pearl
    glPushMatrix();
    glTranslatef(posXBall, posYBall, 0.096);
    glutSolidSphere(radius, 30, 30);
    glPopMatrix();
    
    glutSwapBuffers();
}




// return true if ball in between x range of pad
bool checkBallCollisionWithPad()
{        
    // Check x positions
    if (ballX1 <= padX2 && ballX2 >= padX1 && ballY1 <= padY2 && ballY1 >= (padY1+padY2)/2) {
        return true;
    }
    return false;
}




void updateBallPosition()
{    
    posXBall += (xDir * xChange);
    posYBall += (yDir * yChange);
    
    ballX1 = posXBall - radius;
    ballX2 = posXBall + radius;
    ballY1 = posYBall - radius;
    ballY2 = posYBall + radius;
    
    // check collision of ball with walls
    if (ballY2 >= 1.0) {
        yDir *= -1;
    }
    if (ballX1 <= -1.0 || ballX2 >= 1.0) {
        xDir *= -1;
    }
}


bool gameOver() {
    
    
    return false;
}



void restartRound()
{
    
    generateRandomBlockLevel(10);
}



void myTimer(int value)
{
    if (state == 0) {
        
        // Do checkBallCollision with pad
        if ( checkBallCollisionWithPad() ) {
            yDir *= -1;
            
            xChange = ((ballX1 + ballX2)/2 - (padX1 + padX2)/2) * 0.1;
            if (xChange < 0) {
                xDir = -1;
                xChange *= -1;
            } else {
                xDir = 1;
            }
        }
        
        updateBallPosition();
        
        
    }
    
    glutPostRedisplay();
    glutTimerFunc(timeRedraw, myTimer, 1);
}



void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    double padXmov = 0.08;
    double timeMov = 3;
    
    switch (theKey)
    {
        case 'd':
        case 'D':
            padX1 += padXmov;
            padX2 += padXmov;
            
            if (padX2 >= 1) {
                padX2 = 1;
                padX1 = 0.7;
            }
            break;
            
        case 'a':
        case 'A':
            padX1 -= padXmov;
            padX2 -= padXmov;
            
            if (padX1 <= -1) {
                padX2 = -0.7;
                padX1 = -1.0;
            }
            break;
            
        case 'v':
            timeRedraw += timeMov;
            break;
        case 'V':
            timeRedraw -= timeMov;
            if (timeRedraw <= 0) {
                timeRedraw = 0;
            }
            break;
            
        case 27:
            exit(1);
            
        default:
            break;
    }
}



void init()
{
    gluOrtho2D(-1, 1, -1, 1);
    
    generateRandomBlockLevelSymmetrical(10);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    glutCreateWindow("Breakout");
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(display);
    glutTimerFunc(timeRedraw, myTimer, 1);
    
    init();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
