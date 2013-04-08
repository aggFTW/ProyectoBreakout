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




static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw ball
    glColor3f (1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(posXBall, posYBall, 0);
    glutSolidSphere(radius, 30, 30);
    glPopMatrix();
    
    // Draw left paddle
    glColor3f (1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(padX1, padY1);
    glVertex2f(padX1, padY2);
    glVertex2f(padX2, padY2);
    glVertex2f(padX2, padY1);
    glEnd();
    
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



//void restartRound()
//{
//    xDir = 1;
//    yDir = 1;
//    xChange = 0.01;
//    yChange = 0.0;
//    
//    ballX1 = -0.05;
//    ballX2 = +0.05;
//    ballY1 = -0.05;
//    ballY2 = +0.05;
//    
//    padX1 = -1.00;
//    padX2 = -0.95;
//    padY1 = -0.15;
//    padY2 = +0.15;
//}



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
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
    
    glutCreateWindow("Breakout");
    
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(display);
    glutTimerFunc(timeRedraw, myTimer, 1);
    
    init();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}
