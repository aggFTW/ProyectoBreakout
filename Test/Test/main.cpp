// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//
//////////////////////
//
//  main.cpp
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
#include "imageloader.h"

#include <SFML/Audio.hpp>
#include "ResourcePath.hpp"

using namespace std;

double ANGLE_BLOCKS_CONSTANT = 50.0;


int	screenWidth = 740, screenHeight = 640;
double topbar = 1.15625;

int xDir = 1;
int yDir = -1;
double xChange = 0.0;
double yChange = 0.01;

double angleC = 0.0;

double timeRedraw = 8;
double timePlaying = 0;

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

int score = 0;
int lives = 5;

// -1 for main menu
//  0 for playing
//  1 for game over
int state = -1;

int blockLevel[20][20] = {0};
double blockLevelAngles[20][20] = {};


bool sound = true;
sf::Music music;
sf::Music block;
sf::Music pad;

static GLuint texName[2];

struct bonus {
    int i;
    int j;
    double timeLeft;
    int type;
} ;

bonus bonuses[5] = {};
int bonusIndex = 0;



float colorsAmbient[24][4] = {  0.0215 ,  0.1745 ,  0.0215 ,1,
    0.135 ,  0.2225 ,  0.1575 ,1,
    0.05375 ,  0.05 ,  0.06625 ,1,
    0.25 ,  0.20725 ,  0.20725 ,1,
    0.1745 ,  0.01175 ,  0.01175 ,1,
    0.1 ,  0.18725 ,  0.1745 ,1,
    0.329412 ,  0.223529 ,  0.027451 ,1,
    0.2125 ,  0.1275 ,  0.054 ,1,
    0.25 ,  0.25 ,  0.25 ,1,
    0.19125 ,  0.0735 ,  0.0225 ,1,
    0.24725 ,  0.1995 ,  0.0745 ,1,
    0.19225 ,  0.19225 ,  0.19225 ,1,
    0.0 ,  0.0 ,  0.0 ,1,
    0.0 ,  0.1 ,  0.06 ,1,
    0.0 ,  0.0 ,  0.0 ,1,
    0.0 ,  0.0 ,  0.0 ,1,
    0.0 ,  0.0 ,  0.0 ,1,
    0.0 ,  0.0 ,  0.0 ,1,
    0.02 ,  0.02 ,  0.02 ,1,
    0.0 ,  0.05 ,  0.05 ,1,
    0.0 ,  0.05 ,  0.0 ,1,
    0.05 ,  0.0 ,  0.0 ,1,
    0.05 ,  0.05 ,  0.05 ,1,
    0.05 ,  0.05 ,  0.0 ,1
};

float colorsDiffuse[24][4] = {  0.07568 ,  0.61424 ,  0.07568 ,1,
    0.54 ,  0.89 ,  0.63 ,1,
    0.18275 ,  0.17 ,  0.22525 ,1,
    1 ,  0.829 ,  0.829 ,1,
    0.61424 ,  0.04136 ,  0.04136 ,1,
    0.396 ,  0.74151 ,  0.69102 ,1,
    0.780392 ,  0.568627 ,  0.113725 ,1,
    0.714 ,  0.4284 ,  0.18144 ,1,
    0.4 ,  0.4 ,  0.4 ,1,
    0.7038 ,  0.27048 ,  0.0828 ,1,
    0.75164 ,  0.60648 ,  0.22648 ,1,
    0.50754 ,  0.50754 ,  0.50754 ,1,
    0.01 ,  0.01 ,  0.01 ,1,
    0.0 ,  0.50980392 ,  0.50980392 ,1,
    0.1 ,  0.35 ,  0.1 ,1,
    0.5 ,  0.0 ,  0.0 ,1,
    0.55 ,  0.55 ,  0.55 ,1,
    0.5 ,  0.5 ,  0.0 ,1,
    0.01 ,  0.01 ,  0.01 ,1,
    0.4 ,  0.5 ,  0.5 ,1,
    0.4 ,  0.5 ,  0.4 ,1,
    0.5 ,  0.4 ,  0.4 ,1,
    0.5 ,  0.5 ,  0.5 ,1,
    0.5 ,  0.5 ,  0.4 ,1
};

float colorsSpecular[24][4] ={  0.633 ,  0.727811 ,  0.633 ,1,
    0.316228 ,  0.316228 ,  0.316228 ,1,
    0.332741 ,  0.328634 ,  0.346435 ,1,
    0.296648 ,  0.296648 ,  0.296648 ,1,
    0.727811 ,  0.626959 ,  0.626959 ,1,
    0.297254 ,  0.30829 ,  0.306678 ,1,
    0.992157 ,  0.941176 ,  0.807843 ,1,
    0.393548 ,  0.271906 ,  0.166721 ,1,
    0.774597 ,  0.774597 ,  0.774597 ,1,
    0.256777 ,  0.137622 ,  0.086014 ,1,
    0.628281 ,  0.555802 ,  0.366065 ,1,
    0.508273 ,  0.508273 ,  0.508273 ,1,
    0.5 ,  0.5 ,  0.5 ,1,
    0.50196078 ,  0.50196078 ,  0.50196078 ,1,
    0.45 ,  0.55 ,  0.45 ,1,
    0.7 ,  0.6 ,  0.6 ,1,
    0.7 ,  0.7 ,  0.7 ,1,
    0.6 ,  0.6 ,  0.5 ,1,
    0.4 ,  0.4 ,  0.4 ,1,
    0.04 ,  0.7 ,  0.7 ,1,
    0.04 ,  0.7 ,  0.04 ,1,
    0.7 ,  0.04 ,  0.04 ,1,
    0.7 ,  0.7 ,  0.7 ,1,
    0.7 ,  0.7 ,  0.04 ,1
};


GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess[]= {100.0f};



//Makes the image into a texture, and returns the id of the texture
void loadTexture(Image* image,int k)
{
    
    glBindTexture(GL_TEXTURE_2D, texName[k]); //Tell OpenGL which texture to edit
    
    //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 image->width, image->height,  //Width and height
                 0,                            //The border of the image
                 GL_RGB, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                 //as unsigned numbers
                 image->pixels);               //The actual pixel data
}



bool checkBonusTimeLeft()
{
    for (int i = 0; i < 5; i++) {
        if (bonuses[i].timeLeft > 0) {
            return false;
        }
    }
    
    return true;
}



// This method should be called checking that the bonus can be substituted
// by calling checkBonusTimeLeft()
//      (only 5 bonuses are possible at any time)
void createBonusCoin(int i, int j)
{
    blockLevel[i][j] = 7;
    blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT;
    
    bonuses[bonusIndex].i = i;
    bonuses[bonusIndex].j = j;
    bonuses[bonusIndex].timeLeft = 4500;
    bonuses[bonusIndex].type = 7;
    
    bonusIndex = (bonusIndex + 1) % 5;
}



void decreaseBonusTime()
{
    for (int i = 0; i < 5; i++) {
        if (bonuses[i].timeLeft > 0) {
            
            bonuses[i].timeLeft -= timeRedraw;
            
            if (bonuses[i].timeLeft < 0) {
                
                //cout << "Quitar moneda en " << bonuses[i].i << "y" << bonuses[i].j << "\n";
                
                blockLevel[bonuses[i].i][bonuses[i].j] = 0;
                
                bonuses[i].i = 0;
                bonuses[i].j = 0;
                bonuses[i].timeLeft = 0;
                bonuses[i].type = 0;
            }
        }
    }
}






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
    glMaterialfv(GL_FRONT,GL_AMBIENT,colorsAmbient[i]);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,colorsDiffuse[i]);
    glMaterialfv(GL_FRONT,GL_SPECULAR,colorsSpecular[i]);
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
 *      4 - white, 1 hit block
 *      5 - gray, 2 hit block
 *      6 - black, 3 hit block
 *      7 - coin
 */

int randomBlock()
{
    int b;
    
    do {
        b = rand() % 7;
    } while (b == 4 || b == 5 || b == 6);
    
    return b;
}

static void generateRandomBlockLevel(int numberRows)
{
    srand ((unsigned) time(NULL));
    
    for (int i = 0; i < numberRows; i++) {
        for (int j = 0; j < 20; j++) {
            blockLevel[i][j] = randomBlock();
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
            blockLevel[i][j] = randomBlock();
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


static void generateRandomBlockLevelSymmetricalWithBarriers20(int numberRows)
{
    srand ((unsigned) time(NULL));
    
    for (int i = 0; i < numberRows; i++) {
        bool rowBlock = false;
        
        if (rand() % 5 > 3) {
            rowBlock = true;
        }
        
        for (int j = 0; j < 10; j++) {
            if (rowBlock) {
                blockLevel[i][j] = 6;
                blockLevel[i][19-j] = 6;
            } else {
                blockLevel[i][j] = randomBlock();
                blockLevel[i][19-j] = blockLevel[i][j];
            }
            
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









void drawCube(double x, double y, double angle)
{
    glPushMatrix();
    
    glTranslated(x + 0.05, y + 0.05, 0);
    glRotated(angle - ANGLE_BLOCKS_CONSTANT, 1, 1, 1);
    glutSolidCube(0.095);
    
    glPopMatrix();
}

void drawBlueCube(double x, double y, double angle)
{
    changeMaterial(13);             //cyan
    drawCube(x,y,angle);
}

void drawRedCube(double x, double y, double angle)
{
    changeMaterial(4);              //ruby
    drawCube(x,y,angle);
}

void drawYellowCube(double x, double y, double angle)
{
    changeMaterial(17);             //yellow plastic
    drawCube(x,y,angle);
}

void drawWhiteHitCube(double x, double y, double angle)
{
    changeMaterial(3);             //pearl
    drawCube(x,y,angle);
}

void drawGrayHitCube(double x, double y, double angle)
{
    changeMaterial(8);             //chrome
    drawCube(x,y,angle);
}

void drawBlackHitCube(double x, double y, double angle)
{
    changeMaterial(2);             //obsidian
    drawCube(x,y,angle);
}

void drawBonusCoin(double x, double y)
{
    glPushMatrix();
    
    changeMaterial(10);             //gold
    glTranslated(x + 0.05, y + 0.05, 0);
    glRotated(angleC, 0.0, 1.0, 0.0);
    glScalef(1.0, 1.0, 0.15);
    glutSolidSphere(0.04, 20, 20);
    
    glPopMatrix();
}

/*
 * A ___ means ___:
 *      0 - no block
 *      1 - blue block
 *      2 - red block
 *      3 - yellow block
 *      4 - white, 1 hit block
 *      5 - gray, 2 hit block
 *      6 - black, 3 hit block
 *      7 - coin
 */
static void drawBlocks()
{
    double x = -1.0;
    double y = 0.9;
    int type = 0;
    double angleB = 0;
    
    for (int i = 0; i < 20; i++) {
        x = -1.0;
        
        for (int j = 0; j < 20; j++) {
            // get type of square
            type = blockLevel[i][j];
            angleB = blockLevelAngles[i][j];
            
            // draw type of square
            switch (type) {
                case 0:
                    break;
                case 1:
                    drawBlueCube(x, y, angleB);
                    break;
                case 2:
                    drawRedCube(x, y, angleB);
                    break;
                case 3:
                    drawYellowCube(x, y, angleB);
                    break;
                case 4:
                    drawWhiteHitCube(x, y, angleB);
                    break;
                case 5:
                    drawGrayHitCube(x, y, angleB);
                    break;
                case 6:
                    drawBlackHitCube(x, y, angleB);
                    break;
                case 7:
                    drawBonusCoin(x, y);
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


void reshape(int x, int y)
{
    screenWidth = x;
    screenHeight = y;
    
    // Camera
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winHt = 1.0;
    glOrtho(-winHt, winHt, -winHt, topbar, -winHt, winHt);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0.1, 0.4, 0, 0, 0, 0, 1, 0);
}



static void displayGame()
{
    
    // Draw left paddle
    changeMaterial(0);              //emerald
    glPushMatrix();
    glTranslatef((padX1 + padX2)/2.0, (padY1 + padY2)/2.0, 0);
    glScaled(1.0, 0.1, 0.8);
    glutSolidCube(0.3);
    glPopMatrix();
    
    // Draw blocks
    drawBlocks();
    
    // Draw ball
    changeMaterial(3);              //pearl
    glPushMatrix();
    glTranslatef(posXBall, posYBall, 0.096);
    glutSolidSphere(radius, 30, 30);
    glPopMatrix();
    
}

static void displayGameOver()
{    
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glBegin(GL_QUADS);
    glTexCoord2f(-1.0f, -1.0f);    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(-1.0f, 1.0f);    glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, -1.0f);    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, NULL);
}

static void displayGamePaused()
{
    glColor3f(1.0, 1.0, 1.0);
    displayGame();
    
    // Display paused overlay
    glColor3f(1.0, 1.0, 1.0);
    char msg[7];
    sprintf(msg, "%s", "PAUSED");
    glRasterPos2f(-0.09f, -0.2f);
    for (int k=0; k<6; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[k]);
    
}

static void displayMainMenu()
{
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);    glVertex3f(-1.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);    glVertex3f(-1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f);    glVertex3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f);    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, NULL);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Lights
    GLfloat lightIntensity[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[] = {0.0f, 1.0f, 3.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    
    switch (state) {
        case -1:                    //mainmenu
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            displayMainMenu();
            break;
        case 0:                     //playing
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            displayGame();
            break;
        case 1:                     //game over
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            displayGameOver();
            break;
        case 2:                     //paused
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT0);
            displayGamePaused();
            break;
        default:
            break;
    }
    
    
    // Draw top bar
    changeMaterial(11);              //silver
    glPushMatrix();
    glTranslatef(0, (topbar + 1.0) / 2, -0.2);
    glScaled(25.0, 2.0, 1.0);
    glutSolidCube(0.095);
    glPopMatrix();
    
    
    // Display score
    char msg[250] = {};
    glColor3f(1.0, 1.0, 1.0);
    std::string f_str = "Score: " + std::to_string(score);
    char * ss = const_cast<char*> (f_str.c_str());
    sprintf(msg, "%s", ss);
    glRasterPos2f(-0.95f, 1.1f);
    for (int k=0; k<34; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg[k]);
    
    
    // Display lives
    char msg2[250] = {};
    glColor3f(1.0, 1.0, 1.0);
    f_str = "Lives: " + std::to_string(lives);
    ss = const_cast<char*> (f_str.c_str());
    //    changeMaterial(3);              //pearl
    //    drawText(ss, -0.95, 1.1, 0.7);
    sprintf(msg2, "%s", ss);
    glRasterPos2f(0.75f, 1.1f);
    for (int k=0; k<34; k++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg2[k]);
    
    
    glutSwapBuffers();
}















// return true if ball collided with pad
bool checkBallCollisionWithPad()
{
    // Check x positions
    if (ballX1 <= padX2 && ballX2 >= padX1 && ballY1 <= padY2 && ballY1 >= (padY1+padY2)/2) {
        return true;
    }
    return false;
}

void printBlockCollision(int from, int i, int j, double x, double y)
{
    cout << "from: " << from << "\n---------------------------\n";
    cout << "x: " << x << "\n";
    cout << "y: " << y << "\n";
    cout << "posXBall: " << posXBall << "\n";
    cout << "posYBall: " << posYBall << "\n";
    cout << "i: " << i << "\n";
    cout << "j: " << j << "\n";
}

void scoreBlock(int type, int i, int j)
{
    switch (type) {
        case 1:
            blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT - 1.0;
            score += 1;
            break;
        case 2:
            blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT - 1.0;
            score += 2;
            break;
        case 3:
            blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT - 1.0;
            score += 3;
            break;
        case 4:
            blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT - 1.0;
            score += 5;
            break;
        case 5:
            blockLevel[i][j] = 4;
            break;
        case 6:
            blockLevel[i][j] = 5;
            break;
        case 7:
            score += 50;
            break;
            
        default:
            break;
    }
}

void checkBallCollisionWithBlocks()
{
    double x = -1.0;
    double y = 0.9;
    int type = 0;
    
    for (int i = 0; i < 20; i++) {
        x = -1.0;
        
        for (int j = 0; j < 20; j++) {
            // get type of square
            type = blockLevel[i][j];
            
            // check for collision when appropiate
            if (type != 0 && blockLevelAngles[i][j] == ANGLE_BLOCKS_CONSTANT) {
                // Center block:    x + 0.05, y + 0.05
                // Center ball:     posXBall, posYBall === radius
                
                // Top and bottom - if x center ball in block x range
                if (posXBall < x + 0.1 && posXBall > x)
                {
                    if ((posYBall - radius <= y + 0.1 && posYBall - radius >= y + 0.9) ||
                        (posYBall + radius >= y && posYBall + radius <= y + 0.1))
                    {
                        yDir *= -1;
                        scoreBlock(type, i, j);
                        
                        if (sound) {
                            block.play();
                        }
                    }
                }
                
                // Left and right - if y center ball in block y range
                if (posYBall < y + 0.1 && posYBall > y)
                {
                    if ((posXBall - radius <= x + 0.1 && posXBall - radius >= x + 0.9) ||
                        (posXBall + radius >= x && posXBall + radius <= x + 0.1))
                    {
                        xDir *= -1;
                        scoreBlock(type, i, j);
                        
                        if (sound) {
                            block.play();
                        }
                    }
                }
            }
            
            // update x
            x += 0.1;
        }
        
        y -= 0.1;
    }
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



void restartRound()
{
    xDir = 1;
    yDir = -1;
    xChange = 0.0;
    yChange = 0.01;
    timeRedraw = 8;
    
    ballX1 = -0.05;
    ballX2 = +0.05;
    ballY1 = -0.05;
    ballY2 = +0.05;
    radius = 0.03;
    
    posXBall = 0.0;
    posYBall = 0.0;
    
    padY1 = -1.00;
    padY2 = -0.95;
    padX1 = -0.15;
    padX2 = +0.15;
    
    score = 0;
    
    state = 0;
    
    timePlaying = 0;
    
    generateRandomBlockLevelSymmetricalWithBarriers20(10);
}

void restartGame()
{
    lives = 5;
    
    restartRound();
}



void myTimer(int value)
{
    angleC += 0.5;
    
    if (state == 0) {
        
        timePlaying += timeRedraw;
        
        // Do checkBallCollision with pad
        if ( checkBallCollisionWithPad() ) {
            if (sound) {
                pad.play();
            }
            
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
        
        checkBallCollisionWithBlocks();
        
        // Rotate blocks if they were hit
        for (int i = 0; i < 20; i ++) {
            for (int j = 0; j < 20; j++) {
                if (blockLevelAngles[i][j] < ANGLE_BLOCKS_CONSTANT) {
                    blockLevelAngles[i][j] -= 1.0;
                }
                
                if (blockLevelAngles[i][j] == 0.0) {
                    blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT;
                    blockLevel[i][j] = 0;
                }
            }
        }
        
        if (ballY1 < -1.0) {
            lives = lives - 1;
            if (lives <= 0)
            {
                state = 1;
            }
            else
            {
                restartRound();
            }
            
        }
        
        decreaseBonusTime();
        
        if (rand() % 10000 > 9990 && checkBonusTimeLeft()) {
            int i = rand() % 10;
            int j = rand() % 20;
            createBonusCoin(i, j);
        }
        
        
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
            if (state == 0) {
                padX1 += padXmov;
                padX2 += padXmov;
                
                if (padX2 >= 1) {
                    padX2 = 1;
                    padX1 = 0.7;
                }
            }
            break;
            
        case 'a':
        case 'A':
            if (state == 0) {
                padX1 -= padXmov;
                padX2 -= padXmov;
                
                if (padX1 <= -1) {
                    padX2 = -0.7;
                    padX1 = -1.0;
                }
            }
            break;
            
        case 's':
        case 'S':
            sound = !sound;
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
            
        case 'p':
        case 'P':
            if (state == 0) {
                state = 2;
            } else if (state == 2) {
                state = 0;
            }
            
            break;
            
//        case 'r':
//            restartRound();
//            break;
            
        case 'm':
        case 'M':
            restartGame();
            state = -1;
            break;
            
        case '\r':
            if (state == -1) {
                state = 0;
            }
            break;
            
        case 27:
            exit(1);
            
        default:
            break;
    }
}

void special(int theKey, int mouseX, int mouseY)
{
    double padXmov = 0.08;
    
    switch (theKey)
    {
        case GLUT_KEY_RIGHT:
            if (state == 0) {
                padX1 += padXmov;
                padX2 += padXmov;
                
                if (padX2 >= 1) {
                    padX2 = 1;
                    padX1 = 0.7;
                }
            }
            
            break;
        case GLUT_KEY_LEFT:
            if (state == 0)
            {
                padX1 -= padXmov;
                padX2 -= padXmov;
                
                if (padX1 <= -1) {
                    padX2 = -0.7;
                    padX1 = -1.0;
                }
            }
            
            break;
        default:
            break;
    }
}

void mouse(int x, int y)
{
    if (state == 0) {
        double pos = ((double) x - screenWidth / 2.0) / (screenWidth / 2.0);
        
        padX1 = pos - 0.15;
        padX2 = pos + 0.15;
        
        if (padX2 >= 1) {
            padX2 = 1;
            padX1 = 0.7;
        }
        
        if (padX1 <= -1) {
            padX2 = -0.7;
            padX1 = -1.0;
        }
    }
    
    glutPostRedisplay();
}

void processMenu(int val){
    
    switch (val) {
        case 10:
            restartGame();
            break;
        case 20:
            if (state == 0) {
                state = 2;
            } else if (state == 2) {
                state = 0;
            }
            break;
        case 21:
            sound = !sound;
            break;
        case 30:
            exit(1);
            break;
            
        default:
            break;
    }
    
}

void addMenues(){
	int mainMenu, subMenu1, subMenu2, subMenu3;
    
	mainMenu = glutCreateMenu(processMenu);
	subMenu1 = glutCreateMenu(processMenu);
	subMenu2 = glutCreateMenu(processMenu);
	subMenu3 = glutCreateMenu(processMenu);
    
    glutSetMenu(mainMenu);
    glutAddMenuEntry("Restart game", 10);
    glutAddMenuEntry("Pause", 20);
    glutAddMenuEntry("Toggle sound", 21);
	glutAddMenuEntry("Quit", 30);
    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}



int init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    generateRandomBlockLevelSymmetricalWithBarriers20(10);
    
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j  < 20; j++) {
            blockLevelAngles[i][j] = ANGLE_BLOCKS_CONSTANT;
        }
    }
    
    
    for (int i = 0; i < 5; i++) {
        bonuses[i].i = 0;
        bonuses[i].j = 0;
        bonuses[i].timeLeft = 0;
        bonuses[i].type = 0;
    }
    
    // Load music to play
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
    // Load pad sound
    if (!pad.openFromFile(resourcePath() + "paddle.wav")) {
        return EXIT_FAILURE;
    }
    
    // Load block sound
    if (!block.openFromFile(resourcePath() + "block.wav")) {
        return EXIT_FAILURE;
    }
    
    srand ((unsigned) time(NULL));
    
    // Load textures
    GLuint i=0;
    glGenTextures(7, texName); //Make room for our texture
    Image* image;
    std::string imagename;
    imagename = resourcePath() + "mainmenu.bmp";
    image = loadBMP(imagename.c_str()); loadTexture(image,i++);
    imagename = resourcePath() + "gameover.bmp";
    image = loadBMP(imagename.c_str()); loadTexture(image,i++);
    delete image;
    
    return EXIT_SUCCESS;
}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("Breakout");
    
    
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(special);
    glutPassiveMotionFunc(mouse);
    glutDisplayFunc(display);
    glutTimerFunc(timeRedraw, myTimer, 1);
    glutReshapeFunc(reshape );
    
    if (init() == EXIT_FAILURE)
        exit(1);
    addMenues();
    
    // Play the music
    //    music.setLoop(true);
    //    music.play();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}










#include <assert.h>
#include <fstream>

using namespace std;

Image::Image(char* ps, int w, int h) : pixels(ps), width(w), height(h)
{
    
}

Image::~Image()
{
    delete[] pixels;
}

namespace
{
    //Converts a four-character array to an integer, using little-endian form
    int toInt(const char* bytes)
    {
        return (int)(((unsigned char)bytes[3] << 24) |
                     ((unsigned char)bytes[2] << 16) |
                     ((unsigned char)bytes[1] << 8) |
                     (unsigned char)bytes[0]);
    }
    
    //Converts a two-character array to a short, using little-endian form
    short toShort(const char* bytes)
    {
        return (short)(((unsigned char)bytes[1] << 8) |
                       (unsigned char)bytes[0]);
    }
    
    //Reads the next four bytes as an integer, using little-endian form
    int readInt(ifstream &input)
    {
        char buffer[4];
        input.read(buffer, 4);
        return toInt(buffer);
    }
    
    //Reads the next two bytes as a short, using little-endian form
    short readShort(ifstream &input)
    {
        char buffer[2];
        input.read(buffer, 2);
        return toShort(buffer);
    }
    
    //Just like auto_ptr, but for arrays
    template<class T>
    class auto_array
    {
    private:
        T* array;
        mutable bool isReleased;
    public:
        explicit auto_array(T* array_ = NULL) :
        array(array_), isReleased(false)
        {
        }
        
        auto_array(const auto_array<T> &aarray)
        {
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        ~auto_array()
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
        }
        
        T* get() const
        {
            return array;
        }
        
        T &operator*() const
        {
            return *array;
        }
        
        void operator=(const auto_array<T> &aarray)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = aarray.array;
            isReleased = aarray.isReleased;
            aarray.isReleased = true;
        }
        
        T* operator->() const
        {
            return array;
        }
        
        T* release()
        {
            isReleased = true;
            return array;
        }
        
        void reset(T* array_ = NULL)
        {
            if (!isReleased && array != NULL)
            {
                delete[] array;
            }
            array = array_;
        }
        
        T* operator+(int i)
        {
            return array + i;
        }
        
        T &operator[](int i)
        {
            return array[i];
        }
    };
}

Image* loadBMP(const char* filename)
{
    ifstream input;
    input.open(filename, ifstream::binary);
    assert(!input.fail() || !"Could not find file");
    char buffer[2];
    input.read(buffer, 2);
    assert(buffer[0] == 'B' && buffer[1] == 'M' || !"Not a bitmap file");
    input.ignore(8);
    int dataOffset = readInt(input);
    
    //Read the header
    int headerSize = readInt(input);
    int width;
    int height;
    switch (headerSize)
    {
        case 40:
            //V3
            width = readInt(input);
            height = readInt(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            assert(readShort(input) == 0 || !"Image is compressed");
            break;
        case 12:
            //OS/2 V1
            width = readShort(input);
            height = readShort(input);
            input.ignore(2);
            assert(readShort(input) == 24 || !"Image is not 24 bits per pixel");
            break;
        case 64:
            //OS/2 V2
            assert(!"Can't load OS/2 V2 bitmaps");
            break;
        case 108:
            //Windows V4
            assert(!"Can't load Windows V4 bitmaps");
            break;
        case 124:
            //Windows V5
            assert(!"Can't load Windows V5 bitmaps");
            break;
        default:
            assert(!"Unknown bitmap format");
    }
    
    //Read the data
    int bytesPerRow = ((width * 3 + 3) / 4) * 4 - (width * 3 % 4);
    int size = bytesPerRow * height;
    auto_array<char> pixels(new char[size]);
    input.seekg(dataOffset, ios_base::beg);
    input.read(pixels.get(), size);
    
    //Get the data into the right format
    auto_array<char> pixels2(new char[width * height * 3]);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            for (int c = 0; c < 3; c++)
            {
                pixels2[3 * (width * y + x) + c] =
                pixels[bytesPerRow * y + 3 * x + (2 - c)];
            }
        }
    }
    
    input.close();
    return new Image(pixels2.release(), width, height);
}

