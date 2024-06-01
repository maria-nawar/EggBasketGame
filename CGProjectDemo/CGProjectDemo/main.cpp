//
//  main.cpp
//  CGProjectDemo
//
//  EGG BASKET GAME
//
//
//  Created by Maria Nawar on 20/4/24.
//
//

#include<stdio.h>
#include<GLUT/glut.h>
#include<stdlib.h>
#include<math.h>
#include<cmath>
#include<string.h>
#include<string>
#include<sstream>
#include<fstream>


#define PI 3.14159265358979323846
#define GL_SILENCE_DEPRECATION

using namespace std;


GLfloat column1 = -0.55f;
GLfloat column2 = 0.0f;
GLfloat column3 = 0.55f;
GLfloat dropY=0.40f;

GLfloat Hx=column2;
GLfloat Hy=dropY;

GLfloat Sx=column2;
GLfloat Sy=dropY;

GLfloat Ex = column2; // Start from the middle column initially
GLfloat Ey = dropY;
GLfloat Eradius =0.05f;

GLfloat Bx = column2;
GLfloat By=-0.78f;
GLfloat Bradius =0.15f;

GLfloat Ox = column2;
GLfloat Oy=dropY;
GLfloat Oradius =0.05f;

GLfloat Cx = column2;
GLfloat Cy=dropY;
GLfloat Cradius =0.05f;

GLfloat Gx = column2; // Start from the middle column initially
GLfloat Gy = dropY;
GLfloat Gradius =0.055f;


static int flag=0;
int totaldrop=0;
int totalEgg=0;
int totalBomb=0;
int totalHeart=0;
int totalShield=0;
int totalGoldenEgg=0;
int totalClock=0;

int totalH = 3;
int score = 0;
int highscore = 0;

bool shieldActive = false;
bool goldenEggActive = false;
bool ClockActive = false;

int Duration = 10000; // Duration of golden egg effect in milliseconds (10 seconds)

int ShieldTimer = 0; // Timer to track the duration of the shield effect
int goldenEggTimer = 0; // Timer to track the duration of the golden egg effect
int ClockTimer = 0; // Timer to track the duration of the clock effect

int timer = 0;

void drawSky();
void drawField();
void drawGrass();
void drawStone();
void drawBanner();
void drawPlay();
void chicken();
void Hen();
void chickendrop();
void chickendropline();
void drawHeart();



void renderBitmapString(float x, float y, float z, void *font, char *string) {
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void renderBitmapString(float x, float y, void *font, const string &string) {
    glRasterPos2f(x, y);
    for (char c : string) {
        glutBitmapCharacter(font, c);
    }
}


void TimerCount()
{
    if (timer == 0) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "0");
    }
    if (timer <= 1000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "1");
    }
    else if (timer <= 2000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "2");
    }
    else if (timer <= 3000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "3");
    }
    else if (timer <= 4000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "4");
    }
    else if (timer <= 5000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "5");
    }
    else if (timer <= 6000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "6");
    }
    else if (timer <= 7000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "7");
    }
    else if (timer <= 8000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "8");
    }
    else if (timer <= 9000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "9");
    }
    else if (timer <= 10000) {
        renderBitmapString(0.0f, -0.10f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "10");
    }

}


enum GameState {
    HOME_MENU,
    GAME_MENU,
    INSTRUCTION,
    PAUSED,
    GAMEOVER,
    NAME_ID
};

GameState gameState = NAME_ID;

void drawNAME_ID()
{
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(-0.50f, 0.50f, 0.0f, GLUT_BITMAP_HELVETICA_18, "MARIA NAWAR          21-45395-3");
    renderBitmapString(-0.50f, 0.40f, 0.0f, GLUT_BITMAP_HELVETICA_18, "MD. AKIB SHAHRIER    21-45428-3");
    renderBitmapString(-0.50f, 0.30f, 0.0f, GLUT_BITMAP_HELVETICA_18,  "HASIN ANJUM          21-45430-3");
    renderBitmapString(-0.50f, 0.20f, 0.0f, GLUT_BITMAP_HELVETICA_18,  "TANJIB UL ISLAM      21-45393-3");
    renderBitmapString(-0.50f, 0.10f, 0.0f, GLUT_BITMAP_HELVETICA_18,  "SAKIB HOSSAIN        21-45388-3");
    renderBitmapString(-0.50f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18,  "SUBRINA ISLAM PRITY  21-45813-3");
    
    renderBitmapString(-0.26f, -0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'C' to CONTINUE");
}

void drawHomeMenu()
{
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(-0.20f, 0.30f, 0.0f, GLUT_BITMAP_HELVETICA_18, "EGG BASKET GAME");
    renderBitmapString(-0.10f, 0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "CATCH!!");
    renderBitmapString(-0.26f, -0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'S' to START");
}

void drawGameMenu()
{
    glColor3f(0.0, 0.0, 0.0);
    //renderBitmapString(-0.20f, 0.30f, 0.0f, GLUT_BITMAP_HELVETICA_18, "GAME MENU");
    renderBitmapString(-0.27f, 0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'P' to PAUSE");
    
    glColor3f(0.4, 0.2, 0.0);
    renderBitmapString(-0.20f, 0.10F, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'Q' to QUIT");
    
    
    if(ClockActive)
    {
        timer=ClockTimer;
        TimerCount();
        
        glColor3f(1.0, 0.2, 0.0);
        renderBitmapString(0.10f, -0.10f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Speed Up");
    }
    
    if(shieldActive)
    {
        timer=ShieldTimer;
        TimerCount();
    }
        
    if(goldenEggActive)
    {
        timer=goldenEggTimer;
        TimerCount();
        
        glColor3f(1.0, 0.2, 0.0);
        renderBitmapString(0.10f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18, "2X SCORE");
        
    }

}

void instruction()
{
    glColor3f(0.10, 0.20, 1.0);
    renderBitmapString(-0.20f, 0.50f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "HOW TO PLAY");
    
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(-0.525f, 0.40f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Use LEFT and RIGHT button to move the basket");
    renderBitmapString(-0.28f, 0.30f, 0.0f, GLUT_BITMAP_HELVETICA_18, "DON'T MISS THE EGGS");
    renderBitmapString(-0.40f, 0.20f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Catch LIVES and SHIELD for bonus!");
    renderBitmapString(-0.41f, 0.10f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Avoid BOMB to protect your HEARTS");
}

void drawPaused()
{
    instruction();
    renderBitmapString(-0.30f, -0.40F, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'R' to RESUME");
    renderBitmapString(-0.30f, -0.50F, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'Q' to QUIT");
}

void drawInstruction()
{
    instruction();
    
    glColor3f(0.4, 0.2, 0.0);
    renderBitmapString(-0.26f, -0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'S' to START");
}

void drawGameOver()
{
    glColor3f(0.0, 0.0, 0.0);
    renderBitmapString(-0.20f, 0.30f, 0.0f, GLUT_BITMAP_HELVETICA_18, "GAME OVER");
    renderBitmapString(-0.32f, 0.20f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Press 'M' to Main Menu");
}

void HighScore()
{
    if(score>=highscore)
    {
        highscore=score;
    }
}

// Function to draw
void drawEgg(){
    
    int triangleAmount = 100;

    glColor3ub(221, 161, 36);
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(Ex, Ey); // center of circle
        for(int i = 0; i <= triangleAmount;i++)
        {
            glVertex2f( Ex + ((Eradius) * cos(-i * 2 * PI / triangleAmount)),
                       Ey + ((Eradius+.02f) * sin(i * 2 * PI / triangleAmount)) );
        }
    
    
    
    int lineAmount = 100; //# of triangles used to draw circle
    
    glColor3f(0.60, 0.40, 0.25);
    glLineWidth(3.0);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i <= lineAmount;i++) {
            glVertex2f(
                Ex + ((Eradius) * cos(i * 2 * PI / lineAmount)),
                Ey + ((Eradius+.02f)* sin(i * 2 * PI / lineAmount))
            );
        }
    
    glEnd();

}

void drawGoldenEgg(){
    
    int triangleAmount = 100;

    glColor3ub(246, 236, 81);
    
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(Gx, Gy); // center of circle
        for(int i = 0; i <= triangleAmount;i++)
        {
            glVertex2f( Gx + ((Gradius) * cos(-i * 2 * PI / triangleAmount)),
                       Gy + ((Gradius+.02f) * sin(i * 2 * PI / triangleAmount)) );
        }
    
    
    int lineAmount = 100; //# of triangles used to draw circle
    
    glColor3ub(221, 161, 36);
    glLineWidth(4.0);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i <= lineAmount;i++) {
            glVertex2f(
                Gx + ((Gradius) * cos(i * 2 * PI / lineAmount)),
                Gy + ((Gradius+.02f)* sin(i * 2 * PI / lineAmount))
            );
        }
    
    glEnd();

}


void drawBomb(){
    
    int triangleAmount = 100;
    

    glColor3f(0.0, 0.0, 0.0);
   
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(Ox,Oy); // center of circle
        for(int i = 0; i <= triangleAmount;i++)
        {
            glVertex2f( Ox + ((Oradius) * cos(-i * 2 * PI / triangleAmount)),
                       Oy + ((Oradius) * sin(i * 2 * PI / triangleAmount)) );
        }
    glEnd();

}

void drawClock(){
    
    int triangleAmount = 100;

    glColor3ub(255, 153, 204);
   
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(Cx,Cy); // center of circle
        for(int i = 0; i <= triangleAmount;i++)
        {
            glVertex2f( Cx + ((Cradius) * cos(-i * 2 * PI / triangleAmount)),
                       Cy + ((Cradius) * sin(i * 2 * PI / triangleAmount)) );
        }
    glEnd();

}


void drawHeartDrop()
{
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(Hx, 0.03f + Hy);
    glVertex2f(0.0081f + Hx, 0.0388f + Hy);
    glVertex2f(0.0153f + Hx, 0.0436f + Hy);
    glVertex2f(0.024f + Hx, 0.0452f + Hy);
    glVertex2f(0.0312f + Hx, 0.0428f + Hy);
    glVertex2f(0.0366f + Hx, 0.038f + Hy);
    glVertex2f(0.0414f + Hx, 0.0302f + Hy);
    glVertex2f(0.0432f + Hx, 0.0214f + Hy);
    glVertex2f(0.0426f + Hx, 0.012f + Hy);
    glVertex2f(0.04f + Hx, 0.0048f + Hy);
    glVertex2f(0.0354f + Hx, -0.0022f + Hy);
    glVertex2f(Hx, -0.0442f + Hy);
    glVertex2f(-0.0354f + Hx, -0.0022f + Hy);
    glVertex2f(-0.04f + Hx, 0.0048f + Hy);
    glVertex2f(-0.0426f + Hx, 0.012f + Hy);
    glVertex2f(-0.0432f + Hx, 0.0214f + Hy);
    glVertex2f(-0.0414f + Hx, 0.0302f + Hy);
    glVertex2f(-0.0366f + Hx, 0.038f + Hy);
    glVertex2f(-0.0312f + Hx, 0.0428f + Hy);
    glVertex2f(-0.024f + Hx, 0.0452f + Hy);
    glVertex2f(-0.0153f + Hx, 0.0436f + Hy);
    glVertex2f(-0.0081f + Hx, 0.0388f + Hy);
    glVertex2f( Hx, 0.03 + Hy);
    glEnd();
}

void drawShield()
{
    glColor3f(0.6, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f + Sx, -0.075f + Sy);
    glVertex2f(0.015f + Sx, -0.0645f + Sy);
    glVertex2f(0.03f + Sx, -0.057f + Sy);
    glVertex2f(0.045f + Sx, -0.0525f + Sy);
    glVertex2f(0.0525f + Sx, -0.048f + Sy);
    glVertex2f(0.06f + Sx, -0.042f + Sy);
    glVertex2f(0.0675f + Sx, -0.0345f + Sy);
    glVertex2f(0.075f + Sx, -0.0225f + Sy);
    glVertex2f(0.075f + Sx, -0.015f + Sy);
    glVertex2f(0.0675f + Sx, 0.0f + Sy);
    glVertex2f(0.06f + Sx, 0.018f + Sy);
    glVertex2f(0.057f + Sx, 0.027f + Sy);
    glVertex2f(0.06f + Sx, 0.0375f + Sy);
    glVertex2f(0.0675f + Sx, 0.0525f + Sy);
    glVertex2f(0.045f + Sx, 0.075f + Sy);
    glVertex2f(0.0375f + Sx, 0.072f + Sy);
    glVertex2f(0.03f + Sx, 0.0675f + Sy);
    glVertex2f(0.0225f + Sx, 0.063f + Sy);
    glVertex2f(0.015f + Sx, 0.06f + Sy);
    glVertex2f(0.0f + Sx, 0.06f + Sy);

    glColor3f(0.0, 0.8, 0.8);
    glVertex2f(-0.015f + Sx, 0.06f + Sy);
    glVertex2f(-0.0225f + Sx, 0.063f + Sy);
    glVertex2f(-0.03f + Sx, 0.0675f + Sy);
    glVertex2f(-0.0375f + Sx, 0.072f + Sy);
    glVertex2f(-0.045f + Sx, 0.075f + Sy);
    glVertex2f(-0.0675f + Sx, 0.0525f + Sy);
    glVertex2f(-0.06f + Sx, 0.0375f + Sy);
    glVertex2f(-0.057f + Sx, 0.027f + Sy);
    glVertex2f(-0.06f + Sx, 0.018f + Sy);
    glVertex2f(-0.0675f + Sx, 0.0f + Sy);
    glVertex2f(-0.075f + Sx, -0.015f + Sy);
    glVertex2f(-0.075f + Sx, -0.0225f + Sy);
    glVertex2f(-0.0675f + Sx, -0.0345f + Sy);
    glVertex2f(-0.06f + Sx, -0.042f + Sy);
    glVertex2f(-0.0525f + Sx, -0.048f + Sy);
    glVertex2f(-0.045f + Sx, -0.0525f + Sy);
    glVertex2f(-0.03f + Sx, -0.057f + Sy);
    glVertex2f(-0.015f + Sx, -0.0645f + Sy);
    glVertex2f(0.0f + Sx, -0.075f + Sy);
    glEnd();
    
}


void drawBasket()
{
    int Amount = 100;

    glColor3f(0.64, 0.48, 0.20);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(Bx, By); // center of circle
        for(int i = 0; i <= Amount;i++)
        {
            glVertex2f( Bx + ((Bradius) * cos(-i * PI / Amount)),
                       By + ((Bradius) * sin(-i * PI / Amount)) );
        }
    glEnd();
    
    
    glColor3f(0.5, 0.18, 0.04);
    glLineWidth(5.0);
    
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i <= Amount;i++) {
            glVertex2f(
                Bx + ((Bradius) * cos(-i *  PI / Amount)),
                By + ((Bradius)* sin(-i * PI /Amount)) );
        }
    glEnd();
    
    
    glColor3f(0.5, 0.18, 0.04);
    glBegin(GL_QUADS);
    glVertex2f((Bx + (Bradius+0.03)),By );
    glVertex2f((Bx + (Bradius+0.03)),By + 0.04 );
    glVertex2f((Bx - (Bradius+0.03)),By + 0.04 );
    glVertex2f((Bx - (Bradius+0.03)),By );
    glEnd();
    
    
    glColor3f(0.65, 0.4, 0.0);
    
    glBegin(GL_LINES);
    for(float i = 0; i <= 0.2;i=i+0.05)
    {
        glVertex2f((Bx +i),By );
        glVertex2f((Bx +i),By + 0.04 );
        
        glVertex2f((Bx -i),By + 0.04 );
        glVertex2f((Bx -i),By );
        
    }
    glEnd();

}

void Impact()
{
    if (shieldActive||goldenEggActive)
    {
        int Amount = 50;
        glLineWidth(7.0);
        //glColor3ub(37, 150, 220);
        glColor3ub(255,229, 205);
        glBegin(GL_LINE_STRIP);
        for(int i = - 5; i <= Amount+4 ;i++) {
            glVertex2f(
                Bx + ((Bradius+0.01) * cos(-i * PI / Amount)),
                By + ((Bradius+0.01)* sin(-i * PI /Amount)) );
        }
        
        glColor3ub(11, 26, 132);
        
        if(goldenEggActive)
        {
            glColor3ub(255,255, 105);
        }
        for(int i = -4 ; i <= Amount+4;i++) {
            glVertex2f(
                Bx + ((Bradius+0.03) * cos(-i * PI / Amount)),
                By + ((Bradius+0.03)* sin(-i * PI /Amount)) );
        }
        glEnd();
        
    }
    else
    {
        drawBasket();
    }
}


//int prevItem=0;

GLfloat level1=0.007f;
GLfloat level2=0.010f;
GLfloat level3=0.014f;
GLfloat Speed;

int levelItems=3;
int randomItem;

void LevelSpeed()
{
    if(totaldrop<=8)
    {
        Speed=level1;
        renderBitmapString(-0.5f, 0.80f, GLUT_BITMAP_TIMES_ROMAN_24, "Level: 1");
    }
    else if(totaldrop<=15)
    {
        Speed=level2;
        renderBitmapString(-0.5f, 0.80f, GLUT_BITMAP_TIMES_ROMAN_24, "Level: 2");
    }
    else
    {
        Speed=level3;
        renderBitmapString(-0.5f, 0.80f, GLUT_BITMAP_TIMES_ROMAN_24, "Level: 3");
    }
}

void item()
{
    levelItems = (Speed==level1) ? 3 : ((Speed==level2) ? 4 : 6);
    randomItem = rand() % levelItems;
}

void itemFall()
{
    int randomColumn = rand() % 3;
    
    if (randomItem == 0 )
    {
        totaldrop++;
        totalEgg++;
        
        Ex = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
    else if (randomItem == 1 && ((totalBomb+2)<totalEgg))
    {
        totaldrop++;
        totalBomb++;
        
        Ox = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
    else if(randomItem == 2 && ((totalHeart+2)<totalEgg))
    {
        totaldrop++;
        totalHeart++;
        
        Hx = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
    else if(randomItem == 3 && ((totalShield+3)<totalEgg))
    {
        totaldrop++;
        totalShield++;
        
        Sx = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
    else if(randomItem == 4 && ((totalGoldenEgg+5)<totalEgg))
    {
        totaldrop++;
        totalGoldenEgg++;
        
        Sx = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
    else if(randomItem == 5 && ((totalClock+5)<totalEgg))
    {
        totaldrop++;
        totalClock++;
        
        Cx = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
    else
    {
        randomItem = 0;
        totaldrop++;
        totalEgg++;
        
        Ex = randomColumn == 0 ? column1 : (randomColumn == 1 ? column2 : column3);
    }
}


void update(int value)
{
    if(flag)
    {
        if(totaldrop==0)
        {
            randomItem=0;
            totaldrop++;
            totalEgg++;
        }
        
        LevelSpeed();
        if(randomItem==0)
        {
            Ey -= Speed; // Move the egg downward (change this value to adjust the falling speed)
        }
        else if (randomItem == 1)
        {
            Oy -= Speed;
        }
        else if (randomItem == 2)
        {
            Hy -= Speed;
        }
        else if (randomItem == 3)
        {
            Sy -= Speed;
        }
        else if (randomItem == 4)
        {
            Gy -= Speed;
        }
        else if (randomItem == 5)
        {
            Cy -= Speed;
        }
      
        if (goldenEggTimer > 0)
        {
            goldenEggTimer -= 16; // Decrement timer by the time elapsed (16 milliseconds)
            if (goldenEggTimer <= 0)
            {
                goldenEggActive = false;
            }
        }
        
        if (ShieldTimer > 0)
        {
            ShieldTimer -= 16; // Decrement timer by the time elapsed (16 milliseconds)
            if (ShieldTimer <= 0)
            {
                shieldActive = false;
            }
        }
        
        if (ClockTimer > 0)
        {
            ClockTimer -= 16; // Decrement timer by the time elapsed (16 milliseconds)
            if (ClockTimer <= 0)
            {
                ClockActive = false;
            }
        }
        
        if(Sy < -0.73f && Sy >= -0.78f)
        {
            if((Bx+Bradius)>Sx && (Bx-Bradius)<Sx)
            {
                if(ClockActive)
                {
                    ClockActive=false;
                }
                if(!goldenEggActive)
                {
                    shieldActive=true;
                    ShieldTimer = Duration;
                }
                
                Ey=dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Gy=dropY;
                Cy=dropY;
                
                item();
                itemFall();
            }
        }
        
        if(Gy < -0.73f && Gy >= -0.78f)
        {
            if((Bx+Bradius)>Gx && (Bx-Bradius)<Gx)
            {
                if(shieldActive||ClockActive)
                {
                    shieldActive=false;
                    ClockActive=false;
                }
                goldenEggActive = true; // Set golden egg caught state
                goldenEggTimer = Duration; // Start the timer for golden egg effect
                
                Ey=dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Gy=dropY;
                Cy=dropY;
                
                item();
                itemFall();
                
            }
        }
        
        if(Cy < -0.73f && Cy >= -0.78f)
        {
            if((Bx+Bradius)>Cx && (Bx-Bradius)<Cx)
            {
                if(shieldActive||goldenEggActive)
                {
                    shieldActive=false;
                }
                else
                {
                    ClockActive=true;
                    ClockTimer = Duration;
                    Speed=Speed+0.02f;
                }
                Ey=dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Gy=dropY;
                Cy=dropY;
                
                item();
                itemFall();
            
            }
        }
        
        
        if(Ey < -0.73f && Ey >= -0.78f)
        {
            if((Bx+Bradius)>Ex && (Bx-Bradius)<Ex)
            {
                if(goldenEggActive)
                {
                    score=score+2;
                }
                else
                {
                    score++;
                }
                
                Ey=dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Gy=dropY;
                Cy=dropY;
                
                item();
                itemFall();
                
            }
        }
        else if (Ey < -0.78f)
        {
            if(goldenEggActive)
            {
                //no heart decrese;
            }
            else
            {
                totalH-=1;
                drawHeart();
            }
            
            Ey=dropY;
            Oy=dropY;
            Hy=dropY;
            Sy=dropY;
            Gy=dropY;
            Cy=dropY;
        
            itemFall();
        }
        
        if(Hy < -0.73f && Hy >= -0.78f)// Check if the HEART has reached the bottom of the basket
        {
            if((Bx+Bradius)>Hx && (Bx-Bradius)<Hx)
            {
                if(totalH<5)
                {
                    totalH=totalH+1;
                }
                drawHeart();
                
                Ey=dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Gy=dropY;
                Cy=dropY;
                
                item();
                itemFall();
                
            }
        }
        
        if(Oy < -0.73f && Oy >= -0.78f)
        {
            if((Bx+Bradius)>Ox && (Bx-Bradius)<Ox)
            {
                if(shieldActive||goldenEggActive)
                {
                    shieldActive=false;
                }
                else
                {
                    totalH-=1;
                    drawHeart();
                }
                    
                Ey=dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Gy=dropY;
                Cy=dropY;
                
                item();
                itemFall();
            }
        }
        
        if((Hy < -0.78f)||(Oy < -0.78f)||Sy < -0.78f||Gy < -0.78f||(Cy < -0.78f))
        {
            Ey=dropY;
            Oy=dropY;
            Hy=dropY;
            Sy=dropY;
            Gy=dropY;
            Cy=dropY;
            
            item();
            itemFall();
            
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


void handleKeypress(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'C':
        case 'c':
            if(gameState == HOME_MENU)
            {
                gameState = NAME_ID;
                flag=0;
                break;
            }
            if(gameState == NAME_ID)
            {
                gameState = HOME_MENU;
                flag=0;
            }
            break;
            
        case 'P':
        case 'p':
            if (gameState == GAME_MENU) {
                gameState = PAUSED;
                flag=0;
            }
            break;
            
        case 'Q':
        case 'q':
            if ((gameState == GAME_MENU)||(gameState == PAUSED)) {
                gameState = GAMEOVER;
                flag=0;
            }
            break;

        case 'R':
        case 'r':
            if (gameState == PAUSED) {
                gameState = GAME_MENU;
                flag=1;
            }
            break;
            
        case 'S':
        case 's':
            if (gameState == INSTRUCTION) {
                gameState = GAME_MENU;
                flag=1;
            }
            if (gameState == HOME_MENU) {
                gameState = INSTRUCTION;
                flag=0;
            }
            break;
            
        case 'M':
        case 'm':
            if (gameState == GAMEOVER) {
                gameState = HOME_MENU;
                
                flag=0;
                
                score=0;
                totalH=3;
                totaldrop=0;
                totalEgg=0;
                totalBomb=0;
                totalHeart=0;
                totalShield=0;
                totalGoldenEgg=0;
                totalClock=0;
                
                Ey = dropY;
                Oy=dropY;
                Hy=dropY;
                Sy=dropY;
                Cy=dropY;
                Bx = column2;
                shieldActive=false;
                goldenEggActive=false;
                ClockActive=false;
            }
            break;
            
    }
}

void SpecialInput(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            //do something here
            break;

        case GLUT_KEY_DOWN:
            //do something here
            break;

        case GLUT_KEY_LEFT:
            if(Bx>-0.75)
            {
                Bx -= 0.05f;// Move left
            }
            break;
        case GLUT_KEY_RIGHT:
            if(Bx<0.75)
            {
                Bx += 0.05f; // Move right
            }
            break;
    }
    glutPostRedisplay();
}

void drawLines()
{
    glColor3f (0.0,0.0,0.0);
    
    string DROPStr = "TDROP: " + to_string(totaldrop);
    renderBitmapString(0.7f, 0.8f, GLUT_BITMAP_TIMES_ROMAN_24, DROPStr);
    
    string EStr = "EGG: " + to_string(totalEgg);
    renderBitmapString(0.7f, 0.7f, GLUT_BITMAP_TIMES_ROMAN_24, EStr);
    
    string BStr = "BOMB: " + to_string(totalBomb);
    renderBitmapString(0.7f, 0.6f, GLUT_BITMAP_TIMES_ROMAN_24, BStr);
    
    string HStr = "HEART: " + to_string(totalHeart);
    renderBitmapString(0.7f, 0.5f, GLUT_BITMAP_TIMES_ROMAN_24, HStr);
    
    string SStr = "SHIELD: " + to_string(totalShield);
    renderBitmapString(0.7f, 0.4f, GLUT_BITMAP_TIMES_ROMAN_24, SStr);
    
    string GStr = "GOLD: " + to_string(totalGoldenEgg);
    renderBitmapString(0.7f, 0.3f, GLUT_BITMAP_TIMES_ROMAN_24, GStr);
    
    string CStr = "CLOCK: " + to_string(totalClock);
    renderBitmapString(0.7f, 0.2f, GLUT_BITMAP_TIMES_ROMAN_24, CStr);
    
}

void drawScore()
{
    glColor3f (0.0,0.0,0.0);
    string scoreStr = "Score: " + to_string(score);
    renderBitmapString(0.7f, 0.9f, GLUT_BITMAP_TIMES_ROMAN_24, scoreStr);
    if(gameState!=GAME_MENU)
    {
        renderBitmapString(-0.5f, 0.1f, GLUT_BITMAP_TIMES_ROMAN_24, scoreStr);
        string highscoreStr = "High Score: " + to_string(highscore);
        renderBitmapString(-0.5f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, highscoreStr);
    }
}

void Constant()
{
    drawSky();
    drawField();
    drawStone();
    glLoadIdentity();
    glTranslated(0.0f, -0.05f, 0.0f);
    drawGrass();
    glTranslated(0.15f, -0.07f, 0.0f);
    glScaled(1.1, 1.1, 0.0);
    drawGrass();
    glLoadIdentity();
    
}

void display()
{
    glClearColor(0.80f, 0.80f, 0.80f, 0.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    
    Constant();
    HighScore();
    
    switch (gameState)
    {
        case NAME_ID:
            drawNAME_ID();
            break;
            
        case HOME_MENU:
            drawBanner();
            drawPlay();
            
            drawHomeMenu();
            glLoadIdentity(); // Reset the transformation matrix
            glTranslatef(0.55f, -0.50f, 0.0f);
            glScalef(1.1, 0.75, 0.0);
            Hen();
            chicken();
            glLoadIdentity(); // Reset the transformation matrix
            glTranslatef(-0.55f, -0.50f, 0.0f);
            glScalef(-1.1, 0.75, 0.0);
            Hen();
            chicken();
            glLoadIdentity();
            break;
            
        case INSTRUCTION:
            drawBanner();
            drawPlay();
            drawInstruction();
            break;
            
        case GAME_MENU:
            
            glLoadIdentity();
            glTranslated(0.00f, 0.55f, 0.0f);
            glScaled(1.0, 0.2, 0.0);
            drawField();
            glLoadIdentity();
            LevelSpeed();
            //drawLines();
            drawGameMenu();
            
            drawEgg();
            drawBomb();
            drawShield();
            drawGoldenEgg();
            drawClock();
        
            drawHeart();
            drawHeartDrop();
            
            glLoadIdentity();
            glScaled(0.6, 0.4, 0.0);
            
            glTranslated(-0.90f, 1.2f, 0.0f);
            chickendrop();
            chickendropline();
            glTranslated(0.90f, 0.0f, 0.0f);
            chickendrop();
            chickendropline();
            glTranslated(0.90f, 0.0f, 0.0f);
            chickendrop();
            chickendropline();
            glLoadIdentity();
            
            drawBasket();
            Impact();
            drawScore();
            if(totalH==0)
            {
                gameState=GAMEOVER;
            }
            break;
            
        case PAUSED:
            drawBanner();
            drawPaused();
            break;
            
        case GAMEOVER:
            drawScore();
            drawGameOver();
            break;
            
            
    }
            glFlush(); // Render the scene
}

// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(750, 900); // Set window size
    glutInitWindowPosition(60, 50);  // Set the window's initial position according to the monitor
    glutCreateWindow("Egg Basket Game"); // Set window title
    //glutFullScreen();
    glutDisplayFunc(display);// Register display callback function
    glutSpecialFunc(SpecialInput);
    glutKeyboardFunc(handleKeypress); // Register keyboard callback function
    glutTimerFunc(16, update, 0);
    glutIdleFunc(display);
    
    glutMainLoop(); // Enter the GLUT event processing loop
    
    return 0;
}


void drawStone1(){
    
    glColor3f(0.4, 0.2, 0.0);
    glBegin(GL_LINES);
    
    glVertex2f(-0.96, -0.96);
    glVertex2f(-1.0, -0.96);
    
    glVertex2f(-0.96, -0.92);
    glVertex2f(-1.0, -0.92);
    
    glVertex2f(-0.96, -0.88);
    glVertex2f(-1.0, -0.88);
    
    glVertex2f(-0.96, -0.84);
    glVertex2f(-1.0, -0.84);
    
    glVertex2f(-0.94, -0.98);
    glVertex2f(-0.90, -0.98);
    
    glVertex2f(-0.94, -0.94);
    glVertex2f(-0.90, -0.94);
    
    glVertex2f(-0.94, -0.90);
    glVertex2f(-0.90, -0.90);
    
    glVertex2f(-0.94, -0.86);
    glVertex2f(-0.90, -0.86);
    
    glEnd();
}


void drawStone(){
    
    glTranslatef(-0.065f, 0.0f, 0.0f);
    drawStone1();
    for(int count=0;count<=20;count++){
        
        glTranslatef(+0.12f, 0.0f, 0.0f);
        drawStone1();
       
    }
    glLoadIdentity();
    
}


void drawHeart1()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.03f);
    glVertex2f(0.0081f, 0.0388f);
    glVertex2f(0.0153f, 0.0436f);
    glVertex2f(0.024f, 0.0452f);
    glVertex2f(0.0312f, 0.0428f);
    glVertex2f(0.0366f, 0.038f);
    glVertex2f(0.0414f, 0.0302f);
    glVertex2f(0.0432f, 0.0214f);
    glVertex2f(0.0426f, 0.012f);
    glVertex2f(0.0399f, 0.0048f);
    glVertex2f(0.0354f, -0.0022f);
    glVertex2f(0.0f, -0.0442f);
    glVertex2f(-0.0354f, -0.0022f);
    glVertex2f(-0.0399f, 0.0048f);
    glVertex2f(-0.0426f, 0.012f);
    glVertex2f(-0.0432f, 0.0214f);
    glVertex2f(-0.0414f, 0.0302f);
    glVertex2f(-0.0366f, 0.038f);
    glVertex2f(-0.0312f, 0.0428f);
    glVertex2f(-0.024f, 0.0452f);
    glVertex2f(-0.0153f, 0.0436f);
    glVertex2f(-0.0081f, 0.0388f);
    glVertex2f(0.0f, 0.03);

    glEnd();
}

void drawHeart(){
    
    glLoadIdentity(); // Reset the transformation matrix
    glTranslatef(-0.9f, 0.9f, 0.0f);
    drawHeart1();
    
    for(int i = 0; i<totalH-1; i++)
    {
        glTranslatef(+0.12f, 0.0f, 0.0f);
        drawHeart1();
    }
    glLoadIdentity();
}


void drawBanner(){
    
    glColor3f(0.64, 0.48, 0.20);
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 0.64);
    glVertex2f(0.15, 0.62);
    glVertex2f(0.30, 0.60);
    glVertex2f(0.45, 0.56);
    glVertex2f(0.60, 0.52);
    glVertex2f(0.50, 0.0);
    glVertex2f(-0.50, 0.0);
    glVertex2f(-0.60, 0.52);
    glVertex2f(-0.45, 0.56);
    glVertex2f(-0.30, 0.60);
    glVertex2f(-0.15, 0.62);
    glEnd();

}


void drawPlay(){
    
    GLfloat x=0.0f;
    GLfloat y=-0.18f;
    GLfloat radius =.3f;
    int triangleAmount = 100;
    
    glColor3f(0.64, 0.48, 0.20);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle
        for(int i = 0; i <= triangleAmount;i++)
        {
            glVertex2f( x + ((radius+.05f) * cos(i * 2 * PI / triangleAmount)),
                       y + ((radius-0.2f) * sin(i * 2 * PI / triangleAmount)) );
        }
    glEnd();
    
    int lineAmount = 100; //# of triangles used to draw circle
    
    glColor3f(0.60, 0.40, 0.25);
    glLineWidth(5.0);
    glBegin(GL_LINE_LOOP);
        for(int i = 0; i <= lineAmount;i++) {
            glVertex2f(
                x + ((radius+.05f) * cos(i * 2 * PI / lineAmount)),
                y + ((radius-0.2f)* sin(i * 2 * PI / lineAmount))
            );
        }
    glEnd();

}

void drawSky(){
    
    glBegin(GL_QUADS);
    glColor3f(0.16, 0.22, 0.67);
    glVertex2f(-1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glColor3f(0.62, 0.84, 0.94);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();
    
}


void drawField(){
    
    glBegin(GL_QUADS);
    glColor3f(0.33, 0.18, 0.04);
    glVertex2f(-1.0, -0.80);
    glVertex2f(1.0, -0.80);
    glColor3f(0.65, 0.4, 0.15);
    glVertex2f(1.0, -1.0);
    glVertex2f(-1.0, -1.0);
    glEnd();
    
}

void drawGrass1(){
    glColor3f(0.07, 0.46, 0.25);
    glBegin(GL_POLYGON);
    glVertex2f(-0.87, -0.65);
    glVertex2f(-0.80, -0.54);
    glVertex2f(-0.85, -0.65);
    glVertex2f(-0.88, -0.80);
    glVertex2f(-0.90, -0.79);
    glEnd();
    
    glLineWidth(2.0);
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.87, -0.65);
    glVertex2f(-0.80, -0.54);
    glVertex2f(-0.85, -0.65);
    glVertex2f(-0.88, -0.80);
    glVertex2f(-0.90, -0.79);
    glEnd();

    glColor3f(0.07, 0.62, 0.23);
    glBegin(GL_POLYGON);
    glVertex2f(-0.83, -0.68);
    glVertex2f(-0.78, -0.6);
    glVertex2f(-0.82, -0.68);
    glVertex2f(-0.83, -0.80);
    glVertex2f(-0.85, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.83, -0.68);
    glVertex2f(-0.78, -0.6);
    glVertex2f(-0.82, -0.68);
    glVertex2f(-0.83, -0.80);
    glVertex2f(-0.85, -0.79);
    glEnd();
    
    glColor3f(0.07, 0.64, 0.22);
    glBegin(GL_POLYGON);
    glVertex2f(-0.79, -0.66);
    glVertex2f(-0.76, -0.58);
    glVertex2f(-0.77, -0.65);
    glVertex2f(-0.86, -0.80);
    glVertex2f(-0.88, -0.79);
    glEnd();

    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.79, -0.66);
    glVertex2f(-0.76, -0.58);
    glVertex2f(-0.77, -0.65);
    glVertex2f(-0.86, -0.80);
    glVertex2f(-0.88, -0.79);
    glEnd();
    
    glColor3f(0.07, 0.65, 0.20);
    glBegin(GL_POLYGON);
    glVertex2f(-0.77, -0.67);
    glVertex2f(-0.71, -0.62);
    glVertex2f(-0.75, -0.66);
    glVertex2f(-0.83, -0.80);
    glVertex2f(-0.85, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.77, -0.67);
    glVertex2f(-0.71, -0.62);
    glVertex2f(-0.75, -0.66);
    glVertex2f(-0.83, -0.80);
    glVertex2f(-0.85, -0.79);
    glEnd();

    
    glColor3f(0.07, 0.55, 0.23);
    glBegin(GL_POLYGON);
    glVertex2f(-0.752, -0.742);
    glVertex2f(-0.70, -0.688);
    glVertex2f(-0.74, -0.74);
    glVertex2f(-0.765, -0.80);
    glVertex2f(-0.78, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.752, -0.742);
    glVertex2f(-0.70, -0.688);
    glVertex2f(-0.74, -0.74);
    glVertex2f(-0.765, -0.80);
    glVertex2f(-0.78, -0.79);
    glEnd();
    
    glColor3f(0.07, 0.68, 0.27);
    glBegin(GL_POLYGON);
    glVertex2f(-0.765, -0.71);
    glVertex2f(-0.68, -0.725);
    glVertex2f(-0.76, -0.72);
    glVertex2f(-0.80, -0.80);
    glVertex2f(-0.82, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.765, -0.71);
    glVertex2f(-0.68, -0.725);
    glVertex2f(-0.76, -0.72);
    glVertex2f(-0.80, -0.80);
    glVertex2f(-0.82, -0.79);
    glEnd();

    
    glColor3f(0.07, 0.65, 0.23);
    glBegin(GL_POLYGON);
    glVertex2f(-0.92, -0.67);
    glVertex2f(-0.99, -0.61);
    glVertex2f(-0.91, -0.66);
    glVertex2f(-0.86, -0.80);
    glVertex2f(-0.88, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.92, -0.67);
    glVertex2f(-0.99, -0.61);
    glVertex2f(-0.91, -0.66);
    glVertex2f(-0.86, -0.80);
    glVertex2f(-0.88, -0.79);
    glEnd();

    glColor3f(0.04, 0.51, 0.03);
    glBegin(GL_POLYGON);
    glVertex2f(-0.79, -0.66);
    glVertex2f(-0.76, -0.58);
    glVertex2f(-0.77, -0.65);
    glVertex2f(-0.86, -0.80);
    glVertex2f(-0.88, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.79, -0.66);
    glVertex2f(-0.76, -0.58);
    glVertex2f(-0.77, -0.65);
    glVertex2f(-0.86, -0.80);
    glVertex2f(-0.88, -0.79);
    glEnd();
    
    
    glColor3f(0.05, 0.5, 0.12);
    glBegin(GL_POLYGON);
    glVertex2f(-0.96, -0.63);
    glVertex2f(-1.0, -0.65);
    glVertex2f(-0.955, -0.62);
    glVertex2f(-0.87, -0.80);
    glVertex2f(-0.89, -0.79);
    glEnd();
    
    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.96, -0.63);
    glVertex2f(-1.0, -0.65);
    glVertex2f(-0.955, -0.62);
    glVertex2f(-0.87, -0.80);
    glVertex2f(-0.89, -0.79);
    glEnd();
    
    glColor3f(0.0, 0.40, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.92, -0.745);
    glVertex2f(-0.955, -0.72);
    glVertex2f(-0.915, -0.74);
    glVertex2f(-0.875, -0.80);
    glVertex2f(-0.895, -0.79);
    glEnd();

    glColor3f(0.04, 0.45, 0.08);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.92, -0.745);
    glVertex2f(-0.955, -0.72);
    glVertex2f(-0.915, -0.74);
    glVertex2f(-0.875, -0.80);
    glVertex2f(-0.895, -0.79);
    glEnd();
}

void drawGrass(){
    
    glTranslatef(-0.1f, 0.0f, 0.0f);
    drawGrass1();
    for(int count=0;count<=10;count++)
    {
        glTranslatef(+0.25f, 0.0f, 0.0f);
        drawGrass1();
    }
    glLoadIdentity();
    
}



void chicken()
{
    
    glLineWidth(4.50f);
    glColor3ub(0,0,0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.104f, 0.031f);
    glVertex2f(0.117f, 0.023f);
    glVertex2f(0.128f, 0.043f);
    glVertex2f(0.130f, 0.086f);
    glVertex2f(0.128f, 0.11f);
    glVertex2f(0.146f, 0.086f);
    glVertex2f(0.159f, 0.086f);
    glVertex2f(0.168f, 0.086f);
    glVertex2f(0.170f, 0.098f);
    glVertex2f(0.164f, 0.11f);
    glVertex2f(0.182f, 0.096f);
    glVertex2f(0.190f, 0.096f);
    glVertex2f(0.193f, 0.103f);
    glVertex2f(0.164f, 0.182f);
    glVertex2f(0.155f, 0.222f);
    glVertex2f(0.155f, 0.305f);
    glVertex2f(0.159f, 0.417f);
    glVertex2f(0.150f, 0.48f);
    glVertex2f(0.127f, 0.547f);
    glVertex2f(0.116f, 0.57f);
    glVertex2f(0.094f, 0.586f);
    glVertex2f(0.074f, 0.594f);
    glVertex2f(0.052f, 0.59f);
    glVertex2f(0.030f, 0.578f);
    glVertex2f(0.005f, 0.554f);
    glVertex2f(-0.004f, 0.542f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.027f, 0.526f);
    glVertex2f(0.005f, 0.538f);
    glVertex2f(-0.008f, 0.534f);
    glVertex2f(-0.017f, 0.526f);
    glVertex2f(-0.024f, 0.511f);
    glVertex2f(-0.028f, 0.495f);
    glVertex2f(-0.026f, 0.479f);
    glVertex2f(-0.026f, 0.475f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.132f, 0.495f);
    glVertex2f(0.116f, 0.522f);
    glVertex2f(0.101f, 0.538f);
    glVertex2f(0.085f, 0.546f);
    glVertex2f(0.074f, 0.546f);
    glVertex2f(0.050f, 0.534f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.209f, -0.346f);
    glVertex2f(0.187f, -0.365f);
    glVertex2f(0.176f, -0.373f);
    glVertex2f(0.163f, -0.35f);
    glVertex2f(0.176f, -0.373f);
    glVertex2f(0.174f, -0.401f);
    glVertex2f(0.167f, -0.425f);
    glVertex2f(0.152f, -0.448f);
    glVertex2f(0.161f, -0.44f);
    glVertex2f(0.174f, -0.444f);
    glVertex2f(0.172f, -0.452f);
    glVertex2f(0.167f, -0.468f);
    glVertex2f(0.156f, -0.464f);
    glVertex2f(0.156f, -0.48f);
    glVertex2f(0.147f, -0.484f);
    glVertex2f(0.136f, -0.48f);
    glVertex2f(0.132f, -0.468f);
    glVertex2f(0.121f, -0.492f);
    glVertex2f(0.114f, -0.492f);
    glVertex2f(0.105f, -0.484f);
    glVertex2f(0.112f, -0.468f);
    glVertex2f(0.101f, -0.484f);
    glVertex2f(0.089f, -0.488f);
    glVertex2f(0.083f, -0.48f);
    glVertex2f(0.085f, -0.46f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.102f, -0.467f);
    glVertex2f(0.084f, -0.459f);
    glVertex2f(0.068f, -0.443f);
    glVertex2f(0.059f, -0.42f);
    glVertex2f(0.059f, -0.392f);
    glVertex2f(0.057f, -0.376f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.064f, -0.429f);
    glVertex2f(0.040f, -0.445f);
    glVertex2f(0.022f, -0.449f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.016f, -0.401f);
    glVertex2f(0.042f, -0.409f);
    glVertex2f(0.060f, -0.405f);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.056f, -0.437f);
    glVertex2f(0.056f, -0.457f);
    glVertex2f(0.049f, -0.468f);
    glVertex2f(0.036f, -0.457f);
    glVertex2f(0.042f, -0.464f);
    glVertex2f(0.040f, -0.48f);
    glVertex2f(0.033f, -0.484f);
    glVertex2f(0.022f, -0.472f);
    glVertex2f(0.018f, -0.48f);
    glVertex2f(0.009f, -0.484f);
    glVertex2f(0.002f, -0.48f);
    glVertex2f(-0.002f, -0.468f);
    glVertex2f(-0.009f, -0.472f);
    glVertex2f(-0.022f, -0.472f);
    glVertex2f(-0.022f, -0.464f);
    glVertex2f(-0.018f, -0.449f);
    glVertex2f(-0.009f, -0.449f);
    glVertex2f(-0.031f, -0.441f);
    glVertex2f(-0.042f, -0.425f);
    glVertex2f(-0.056f, -0.389f);
    glVertex2f(-0.056f, -0.366f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.013f, -0.385f);
    glVertex2f(-0.053f, -0.366f);
    glVertex2f(-0.087f, -0.322f);
    glVertex2f(-0.111f, -0.271f);
    glVertex2f(-0.127f, -0.204f);
    glVertex2f(-0.124f, -0.144f);
    glVertex2f(-0.109f, -0.148f);
    glVertex2f(-0.129f, -0.148f);
    glVertex2f(-0.133f, -0.125f);
    glVertex2f(-0.124f, -0.085f);
    glVertex2f(-0.113f, -0.057f);
    glVertex2f(-0.129f, -0.061f);
    glVertex2f(-0.113f, -0.01f);
    glVertex2f(-0.104f, 0.002f);
    glVertex2f(-0.113f, 0.002f);
    glVertex2f(-0.102f, 0.034f);
    glVertex2f(-0.087f, 0.053f);
    glVertex2f(-0.069f, 0.065f);
    glVertex2f(-0.058f, 0.069f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(-0.041f, 0.287f);
    glVertex2f(-0.048f, 0.2f);
    glVertex2f(-0.061f, 0.137f);
    glVertex2f(-0.077f, 0.101f);
    glVertex2f(-0.106f, 0.081f);
    glVertex2f(-0.101f, 0.073f);
    glVertex2f(-0.090f, 0.073f);
    glVertex2f(-0.077f, 0.077f);
    glVertex2f(-0.075f, 0.057f);
    glVertex2f(-0.066f, 0.057f);
    glVertex2f(-0.053f, 0.069f);
    glVertex2f(-0.057f, 0.053f);
    glVertex2f(-0.057f, 0.03f);
    glVertex2f(-0.048f, 0.022f);
    glVertex2f(-0.028f, 0.034f);
    glVertex2f(-0.019f, 0.042f);
    glVertex2f(-0.013f, 0.026f);
    glVertex2f(-0.010f, 0.026f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.283f, -0.01f);
    glVertex2f(0.197f, -0.081f);
    glVertex2f(0.170f, -0.117f);
    glVertex2f(0.150f, -0.157f);
    glVertex2f(0.141f, -0.2f);
    glVertex2f(0.141f, -0.247f);
    glVertex2f(0.157f, -0.287f);
    glVertex2f(0.173f, -0.295f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.177f, -0.236f);
    glVertex2f(0.170f, -0.267f);
    glVertex2f(0.173f, -0.295f);
    glVertex2f(0.186f, -0.323f);
    glVertex2f(0.208f, -0.342f);
    glVertex2f(0.228f, -0.338f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.230f, -0.275f);
    glVertex2f(0.221f, -0.299f);
    glVertex2f(0.224f, -0.323f);
    glVertex2f(0.228f, -0.342f);
    glVertex2f(0.259f, -0.354f);
    glVertex2f(0.288f, -0.342f);
    glVertex2f(0.315f, -0.303f);
    glVertex2f(0.321f, -0.263f);
    glVertex2f(0.315f, -0.236f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    
    glVertex2f(0.288f, -0.311f);
    glVertex2f(0.290f, -0.291f);
    glVertex2f(0.288f, -0.279f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.270f, -0.307f);
    glVertex2f(0.286f, -0.275f);
    glVertex2f(0.295f, -0.244f);
    glVertex2f(0.293f, -0.208f);
    glEnd();
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.295f, -0.244f);
    glVertex2f(0.310f, -0.232f);
    glVertex2f(0.335f, -0.216f);
    glVertex2f(0.353f, -0.18f);
    glVertex2f(0.370f, -0.141f);
    glVertex2f(0.379f, -0.109f);
    glVertex2f(0.379f, -0.125f);
    glVertex2f(0.386f, -0.141f);
    glVertex2f(0.395f, -0.125f);
    glVertex2f(0.397f, -0.101f);
    glVertex2f(0.404f, -0.113f);
    glVertex2f(0.413f, -0.117f);
    glVertex2f(0.424f, -0.097f);
    glVertex2f(0.424f, -0.074f);
    glVertex2f(0.417f, -0.054f);
    glVertex2f(0.428f, -0.054f);
    glVertex2f(0.428f, -0.046f);
    glVertex2f(0.408f, -0.01f);
    glVertex2f(0.379f, 0.017f);
    glVertex2f(0.326f, 0.053f);
    glVertex2f(0.268f, 0.085f);
    glVertex2f(0.217f, 0.096f);
    glVertex2f(0.184f, 0.092f);
    glVertex2f(0.166f, 0.081f);
    glVertex2f(0.155f, 0.065f);
    glVertex2f(0.150f, 0.053f);
    glVertex2f(0.150f, 0.033f);
    glVertex2f(0.170f, 0.005f);
    glVertex2f(0.210f, -0.014f);
    glVertex2f(0.237f, -0.03f);
    glVertex2f(0.244f, -0.042f);
    glVertex2f(0.255f, -0.034f);
    glVertex2f(0.257f, -0.014f);
    glVertex2f(0.264f, -0.006f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.224f, 0.147f);
    glVertex2f(-0.204f, 0.175f);
    glVertex2f(-0.197f, 0.202f);
    glVertex2f(-0.198f, 0.198f);
    glVertex2f(-0.201f, 0.218f);
    glVertex2f(-0.216f, 0.273f);
    glVertex2f(-0.225f, 0.325f);
    glVertex2f(-0.227f, 0.368f);
    glVertex2f(-0.218f, 0.4f);
    glVertex2f(-0.232f, 0.404f);
    glVertex2f(-0.263f, 0.376f);
    glVertex2f(-0.278f, 0.341f);
    glVertex2f(-0.281f, 0.309f);
    glVertex2f(-0.278f, 0.281f);
    glVertex2f(-0.272f, 0.265f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.280f, 0.297f);
    glVertex2f(-0.362f, 0.324f);
    glVertex2f(-0.396f, 0.32f);
    glVertex2f(-0.427f, 0.309f);
    glVertex2f(-0.456f, 0.289f);
    glVertex2f(-0.471f, 0.253f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.340f, 0.273f);
    glVertex2f(-0.369f, 0.285f);
    glVertex2f(-0.404f, 0.285f);
    glVertex2f(-0.440f, 0.273f);
    glVertex2f(-0.462f, 0.258f);
    glVertex2f(-0.489f, 0.234f);
    glVertex2f(-0.504f, 0.202f);
    glVertex2f(-0.507f, 0.19f);
    glVertex2f(-0.473f, 0.198f);
    glVertex2f(-0.440f, 0.198f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.365f, 0.218f);
    glVertex2f(-0.403f, 0.218f);
    glVertex2f(-0.430f, 0.202f);
    glVertex2f(-0.447f, 0.19f);
    glVertex2f(-0.458f, 0.171f);
    glVertex2f(-0.465f, 0.155f);
    glVertex2f(-0.461f, 0.139f);
    glVertex2f(-0.430f, 0.147f);
    glVertex2f(-0.392f, 0.143f);
    glVertex2f(-0.343f, 0.131f);
    glVertex2f(-0.314f, 0.115f);
    glVertex2f(-0.281f, 0.111f);
    glVertex2f(-0.252f, 0.123f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.368f, 0.193f);
    glVertex2f(-0.357f, 0.24f);
    glVertex2f(-0.341f, 0.268f);
    glVertex2f(-0.324f, 0.288f);
    glVertex2f(-0.317f, 0.291f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.316f, 0.255f);
    glVertex2f(-0.318f, 0.228f);
    glVertex2f(-0.325f, 0.208f);
    glVertex2f(-0.341f, 0.192f);
    glVertex2f(-0.321f, 0.204f);
    glVertex2f(-0.301f, 0.208f);
    glVertex2f(-0.281f, 0.204f);
    glVertex2f(-0.258f, 0.192f);
    glVertex2f(-0.245f, 0.168f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.343f, 0.133f);
    glVertex2f(-0.327f, 0.081f);
    glVertex2f(-0.316f, 0.034f);
    glVertex2f(-0.303f, -0.021f);
    glVertex2f(-0.287f, -0.065f);
    glVertex2f(-0.267f, -0.1f);
    glVertex2f(-0.238f, -0.14f);
    glVertex2f(-0.234f, -0.144f);
    glVertex2f(-0.229f, -0.144f);
    glVertex2f(-0.234f, -0.144f);
    glVertex2f(-0.225f, -0.164f);
    glVertex2f(-0.207f, -0.179f);
    glVertex2f(-0.198f, -0.187f);
    glVertex2f(-0.194f, -0.183f);
    glVertex2f(-0.198f, -0.156f);
    glVertex2f(-0.170f, -0.171f);
    glVertex2f(-0.161f, -0.171f);
    glVertex2f(-0.158f, -0.163f);
    glVertex2f(-0.172f, -0.143f);
    glVertex2f(-0.156f, -0.139f);
    glVertex2f(-0.147f, -0.135f);
    glVertex2f(-0.150f, -0.127f);
    glVertex2f(-0.161f, -0.115f);
    glVertex2f(-0.143f, -0.111f);
    glVertex2f(-0.130f, -0.099f);
    glVertex2f(-0.123f, -0.096f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.096f, 0.075f);
    glVertex2f(-0.136f, 0.04f);
    glVertex2f(-0.160f, 0.024f);
    glVertex2f(-0.180f, 0.028f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.170f, -0.03f);
    glVertex2f(-0.175f, -0.002f);
    glVertex2f(-0.179f, -0.002f);
    glEnd();


    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.188f, -0.038f);
    glVertex2f(-0.181f, 0.006f);
    glVertex2f(-0.181f, 0.029f);
    glVertex2f(-0.186f, 0.057f);
    glVertex2f(-0.197f, 0.097f);
    glVertex2f(-0.204f, 0.143f);
    glVertex2f(-0.204f, 0.171f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(0.070f, 0.592f);
    glVertex2f(0.090f, 0.588f);
    glVertex2f(0.110f, 0.572f);
    glVertex2f(0.125f, 0.549f);
    glVertex2f(0.134f, 0.529f);
    glVertex2f(0.143f, 0.505f);
    glVertex2f(0.150f, 0.478f);
    glVertex2f(0.152f, 0.478f);
    glVertex2f(0.150f, 0.478f);
    glVertex2f(0.157f, 0.466f);
    glVertex2f(0.164f, 0.458f);
    glVertex2f(0.173f, 0.45f);
    glVertex2f(0.186f, 0.446f);
    glVertex2f(0.197f, 0.454f);
    glVertex2f(0.208f, 0.486f);
    glVertex2f(0.208f, 0.513f);
    glVertex2f(0.204f, 0.537f);
    glVertex2f(0.190f, 0.557f);
    glVertex2f(0.184f, 0.561f);
    glVertex2f(0.175f, 0.557f);
    glVertex2f(0.166f, 0.553f);
    glVertex2f(0.157f, 0.553f);
    
    
    glVertex2f(0.162f, 0.537f);
    glVertex2f(0.157f, 0.553f);
    glVertex2f(0.155f, 0.561f);
    glVertex2f(0.157f, 0.569f);
    glVertex2f(0.164f, 0.576f);
    glVertex2f(0.179f, 0.592f);
    glVertex2f(0.184f, 0.604f);
    glVertex2f(0.186f, 0.628f);
    glVertex2f(0.182f, 0.644f);
    glVertex2f(0.173f, 0.655f);
    glVertex2f(0.164f, 0.667f);
    glVertex2f(0.148f, 0.671f);
    glVertex2f(0.135f, 0.663f);
    glVertex2f(0.124f, 0.659f);
    glVertex2f(0.119f, 0.652f);
    glVertex2f(0.108f, 0.652f);
    

    glVertex2f(0.113f, 0.624f);
    glVertex2f(0.108f, 0.636f);
    glVertex2f(0.106f, 0.652f);
    glVertex2f(0.117f, 0.695f);
    glVertex2f(0.119f, 0.727f);
    glVertex2f(0.115f, 0.75f);
    glVertex2f(0.106f, 0.778f);
    glVertex2f(0.095f, 0.79f);
    glVertex2f(0.079f, 0.806f);
    glVertex2f(0.059f, 0.818f);
    glVertex2f(0.039f, 0.818f);
    glVertex2f(0.022f, 0.806f);
    glVertex2f(0.006f, 0.786f);
    glVertex2f(-0.010f, 0.754f);
    glVertex2f(-0.016f, 0.723f);
    glVertex2f(-0.016f, 0.699f);
    glVertex2f(-0.016f, 0.675f);
    glVertex2f(-0.014f, 0.648f);
    glVertex2f(0.002f, 0.612f);
    glVertex2f(0.017f, 0.596f);
    glVertex2f(0.033f, 0.576f);
    glVertex2f(0.045f, 0.584f);
    glVertex2f(0.059f, 0.588f);
    glEnd();
    
    
    
    glBegin(GL_LINE_STRIP);
    glLineWidth(2.0);
    glVertex2f(-0.020f, 0.286f);
    glVertex2f(-0.042f, 0.294f);
    glVertex2f(-0.058f, 0.298f);
    glVertex2f(-0.069f, 0.294f);
    glVertex2f(-0.080f, 0.282f);
    glVertex2f(-0.089f, 0.274f);
    
    glVertex2f(-0.086f, 0.274f);
    glVertex2f(-0.093f, 0.294f);
    glVertex2f(-0.093f, 0.314f);
    glVertex2f(-0.089f, 0.357f);
    glVertex2f(-0.078f, 0.389f);
    glVertex2f(-0.062f, 0.417f);
    glVertex2f(-0.044f, 0.429f);
    glVertex2f(-0.031f, 0.436f);
    glVertex2f(-0.009f, 0.433f);
    glVertex2f(0.009f, 0.421f);
    glVertex2f(0.031f, 0.401f);
    glVertex2f(0.042f, 0.385f);
    glVertex2f(0.049f, 0.369f);
    glVertex2f(0.056f, 0.353f);
    glVertex2f(0.056f, 0.346f);
    glVertex2f(0.062f, 0.361f);
    glVertex2f(0.074f, 0.369f);
    glVertex2f(0.089f, 0.373f);
    glVertex2f(0.102f, 0.373f);
    glVertex2f(0.111f, 0.369f);
    glVertex2f(0.118f, 0.353f);
    glVertex2f(0.116f, 0.334f);
    glVertex2f(0.111f, 0.326f);
    glVertex2f(0.116f, 0.29f);
    glVertex2f(0.111f, 0.255f);
    glVertex2f(0.102f, 0.219f);
    glVertex2f(0.085f, 0.172f);
    glVertex2f(0.074f, 0.156f);
    glVertex2f(0.060f, 0.144f);
    glVertex2f(0.051f, 0.136f);
    glVertex2f(0.038f, 0.132f);
    glVertex2f(0.022f, 0.132f);
    glVertex2f(0.005f, 0.14f);
    glVertex2f(-0.009f, 0.156f);
    glVertex2f(-0.015f, 0.172f);
    glVertex2f(-0.003f, 0.164f);
    glVertex2f(0.008f, 0.176f);
    glVertex2f(0.010f, 0.196f);
    glVertex2f(0.010f, 0.223f);
    glVertex2f(0.004f, 0.247f);
    glVertex2f(-0.007f, 0.263f);
    glVertex2f(-0.041f, 0.29f);
    glVertex2f(0.002f, 0.279f);
    glVertex2f(0.013f, 0.259f);
    glVertex2f(0.020f, 0.235f);
    glVertex2f(0.022f, 0.211f);
    glVertex2f(0.022f, 0.188f);
    glVertex2f(0.018f, 0.164f);
    glVertex2f(0.009f, 0.148f);
    glVertex2f(0.027f, 0.144f);
    glVertex2f(0.042f, 0.152f);
    glVertex2f(0.062f, 0.168f);
    glVertex2f(0.078f, 0.192f);
    glVertex2f(0.091f, 0.227f);
    glVertex2f(0.098f, 0.263f);
    glVertex2f(0.100f, 0.302f);
    glVertex2f(0.100f, 0.322f);
    glVertex2f(0.093f, 0.334f);
    glVertex2f(0.093f, 0.346f);
    
    
    glVertex2f(0.102f, 0.346f);
    glVertex2f(0.091f, 0.346f);
    glVertex2f(0.082f, 0.338f);
    glVertex2f(0.069f, 0.334f);
    glVertex2f(0.062f, 0.334f);
    
    
    glVertex2f(0.074f, 0.33f);
    glVertex2f(0.060f, 0.31f);
    glVertex2f(0.045f, 0.29f);
    glVertex2f(0.022f, 0.278f);
    glVertex2f(0.002f, 0.278f);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.029f, 0.429f);
    glVertex2f(-0.032f, 0.452f);
    glVertex2f(-0.025f, 0.472f);
    glVertex2f(-0.014f, 0.492f);
    glVertex2f(-0.003f, 0.508f);
    glVertex2f(0.020f, 0.508f);
    glVertex2f(0.028f, 0.492f);
    glVertex2f(0.037f, 0.472f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.030f, 0.404f);
    glVertex2f(0.027f, 0.432f);
    glVertex2f(0.032f, 0.464f);
    glVertex2f(0.047f, 0.495f);
    glVertex2f(0.074f, 0.507f);
    glVertex2f(0.096f, 0.503f);
    glVertex2f(0.112f, 0.48f);
    glVertex2f(0.123f, 0.46f);
    glVertex2f(0.125f, 0.428f);
    glVertex2f(0.121f, 0.397f);
    glVertex2f(0.112f, 0.373f);
    glVertex2f(0.110f, 0.373f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.104f, -0.573f);
    glVertex2f(0.091f, -0.569f);
    glVertex2f(0.078f, -0.577f);
    glVertex2f(0.071f, -0.593f);
    glVertex2f(0.074f, -0.59f);
    glVertex2f(0.069f, -0.613f);
    glVertex2f(0.081f, -0.637f);
    glVertex2f(0.114f, -0.645f);
    glVertex2f(0.127f, -0.645f);
    glVertex2f(0.161f, -0.665f);
    glVertex2f(0.212f, -0.688f);
    glVertex2f(0.252f, -0.688f);
    glVertex2f(0.272f, -0.669f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.286f, -0.685f);
    glVertex2f(0.275f, -0.669f);
    glVertex2f(0.268f, -0.661f);
    glVertex2f(0.255f, -0.657f);
    glVertex2f(0.248f, -0.646f);
    glVertex2f(0.250f, -0.63f);
    glVertex2f(0.266f, -0.634f);
    glVertex2f(0.281f, -0.65f);
    glVertex2f(0.286f, -0.669f);
    glVertex2f(0.286f, -0.685f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.276f, -0.636f);
    glVertex2f(0.260f, -0.613f);
    glVertex2f(0.244f, -0.609f);
    glVertex2f(0.220f, -0.613f);
    glVertex2f(0.202f, -0.621f);
    glVertex2f(0.178f, -0.621f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.284f, -0.65f);
    glVertex2f(0.291f, -0.65f);
    glVertex2f(0.293f, -0.646f);
    glVertex2f(0.287f, -0.618f);
    glVertex2f(0.273f, -0.59f);
    glVertex2f(0.258f, -0.582f);
    glVertex2f(0.242f, -0.578f);
    glVertex2f(0.213f, -0.59f);
    glVertex2f(0.178f, -0.594f);
    glVertex2f(0.149f, -0.59f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.153f, -0.601f);
    glVertex2f(0.144f, -0.577f);
    glVertex2f(0.139f, -0.538f);
    glVertex2f(0.135f, -0.486f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.296f, -0.652f);
    glVertex2f(0.302f, -0.664f);
    glVertex2f(0.302f, -0.636f);
    glVertex2f(0.298f, -0.617f);
    glVertex2f(0.287f, -0.605f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.116f, -0.497f);
    glVertex2f(0.121f, -0.528f);
    glVertex2f(0.119f, -0.568f);
    glVertex2f(0.116f, -0.592f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.118f, -0.582f);
    glVertex2f(0.101f, -0.57f);
    glVertex2f(0.083f, -0.574f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.159f, -0.618f);
    glVertex2f(-0.175f, -0.634f);
    glVertex2f(-0.181f, -0.653f);
    glVertex2f(-0.181f, -0.669f);
    glVertex2f(-0.175f, -0.661f);
    glVertex2f(-0.166f, -0.657f);
    glVertex2f(-0.159f, -0.661f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.133f, -0.701f);
    glVertex2f(-0.135f, -0.681f);
    glVertex2f(-0.133f, -0.665f);
    glVertex2f(-0.128f, -0.646f);
    glVertex2f(-0.117f, -0.642f);
    glVertex2f(-0.108f, -0.646f);
    glVertex2f(-0.106f, -0.661f);
    glVertex2f(-0.115f, -0.673f);
    glVertex2f(-0.126f, -0.689f);
    glVertex2f(-0.133f, -0.705f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.014f, -0.484f);
    glVertex2f(0.014f, -0.499f);
    glVertex2f(0.014f, -0.535f);
    glVertex2f(0.014f, -0.563f);
    glVertex2f(0.010f, -0.582f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.012f, -0.57f);
    glVertex2f(-0.024f, -0.59f);
    glVertex2f(-0.050f, -0.594f);
    glVertex2f(-0.086f, -0.598f);
    glVertex2f(-0.121f, -0.59f);
    glVertex2f(-0.141f, -0.59f);
    glVertex2f(-0.157f, -0.61f);
    glVertex2f(-0.157f, -0.642f);
    glVertex2f(-0.155f, -0.669f);
    glVertex2f(-0.146f, -0.685f);
    glVertex2f(-0.137f, -0.685f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.130f, -0.653f);
    glVertex2f(-0.130f, -0.63f);
    glVertex2f(-0.124f, -0.622f);
    glVertex2f(-0.097f, -0.622f);
    glVertex2f(-0.073f, -0.626f);
    glVertex2f(-0.044f, -0.622f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.119f, -0.689f);
    glVertex2f(-0.095f, -0.709f);
    glVertex2f(-0.073f, -0.701f);
    glVertex2f(-0.048f, -0.693f);
    glVertex2f(-0.021f, -0.673f);
    glVertex2f(0.012f, -0.646f);
    glVertex2f(0.034f, -0.642f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.016f, -0.634f);
    glVertex2f(0.041f, -0.642f);
    glVertex2f(0.056f, -0.634f);
    glVertex2f(0.065f, -0.622f);
    glVertex2f(0.067f, -0.59f);
    glVertex2f(0.061f, -0.57f);
    glVertex2f(0.045f, -0.567f);
    glVertex2f(0.034f, -0.567f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.034f, -0.578f);
    glVertex2f(0.030f, -0.543f);
    glVertex2f(0.027f, -0.503f);
    glVertex2f(0.030f, -0.484f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    
    glVertex2f(0.033f, 0.148f);
    glVertex2f(0.027f, 0.171f);
    glVertex2f(0.024f, 0.195f);
    glVertex2f(0.031f, 0.219f);
    glVertex2f(0.040f, 0.235f);
    glVertex2f(0.047f, 0.242f);
    glVertex2f(0.058f, 0.238f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    
    glVertex2f(0.047f, 0.2f);
    glVertex2f(0.052f, 0.228f);
    glVertex2f(0.065f, 0.256f);
    glVertex2f(0.079f, 0.264f);
    glVertex2f(0.096f, 0.264f);
    
    glEnd();

    glPointSize(8.0);
    glBegin(GL_POINTS);
    glVertex2f(0.020f, 0.444f);
    glVertex2f(0.075f, 0.437f);
    glEnd();
    
}


void Hen()
{
    glBegin(GL_POLYGON);
    glColor3ub(198,19,1);
    glVertex2f(0.070f, 0.592f);
    glVertex2f(0.090f, 0.588f);
    glVertex2f(0.110f, 0.572f);
    glVertex2f(0.125f, 0.549f);
    glVertex2f(0.134f, 0.529f);
    glVertex2f(0.143f, 0.505f);
    glVertex2f(0.150f, 0.478f);
    glVertex2f(0.152f, 0.478f);
    glVertex2f(0.150f, 0.478f);
    glVertex2f(0.157f, 0.466f);
    glVertex2f(0.164f, 0.458f);
    glVertex2f(0.173f, 0.45f);
    glVertex2f(0.186f, 0.446f);
    glVertex2f(0.197f, 0.454f);
    glVertex2f(0.208f, 0.486f);
    glVertex2f(0.208f, 0.513f);
    glVertex2f(0.204f, 0.537f);
    glVertex2f(0.190f, 0.557f);
    glVertex2f(0.184f, 0.561f);
    glVertex2f(0.175f, 0.557f);
    glVertex2f(0.166f, 0.553f);
    glVertex2f(0.157f, 0.553f);
    
    glVertex2f(0.162f, 0.537f);
    glVertex2f(0.157f, 0.553f);
    glVertex2f(0.155f, 0.561f);
    glVertex2f(0.157f, 0.569f);
    glVertex2f(0.164f, 0.576f);
    glVertex2f(0.179f, 0.592f);
    glVertex2f(0.184f, 0.604f);
    glVertex2f(0.186f, 0.628f);
    glVertex2f(0.182f, 0.644f);
    glVertex2f(0.173f, 0.655f);
    glVertex2f(0.164f, 0.667f);
    glVertex2f(0.148f, 0.671f);
    glVertex2f(0.135f, 0.663f);
    glVertex2f(0.124f, 0.659f);
    glVertex2f(0.119f, 0.652f);
    glVertex2f(0.108f, 0.652f);
    
    glVertex2f(0.113f, 0.624f);
    glVertex2f(0.108f, 0.636f);
    glVertex2f(0.106f, 0.652f);
    glVertex2f(0.117f, 0.695f);
    glVertex2f(0.119f, 0.727f);
    glVertex2f(0.115f, 0.75f);
    glVertex2f(0.106f, 0.778f);
    glVertex2f(0.095f, 0.79f);
    glVertex2f(0.079f, 0.806f);
    glVertex2f(0.059f, 0.818f);
    glVertex2f(0.039f, 0.818f);
    glVertex2f(0.022f, 0.806f);
    glVertex2f(0.006f, 0.786f);
    glVertex2f(-0.010f, 0.754f);
    glVertex2f(-0.016f, 0.723f);
    glVertex2f(-0.016f, 0.699f);
    glVertex2f(-0.016f, 0.675f);
    glVertex2f(-0.014f, 0.648f);
    glVertex2f(0.002f, 0.612f);
    glVertex2f(0.017f, 0.596f);
    glVertex2f(0.033f, 0.576f);
    glVertex2f(0.045f, 0.584f);
    glVertex2f(0.059f, 0.588f);
    glEnd();
    

    
    glColor3ub(253, 231, 157);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.104f, 0.031f);
    glVertex2f(0.117f, 0.023f);
    glVertex2f(0.128f, 0.043f);
    glVertex2f(0.130f, 0.086f);
    glVertex2f(0.128f, 0.11f);
    glVertex2f(0.146f, 0.086f);
    glVertex2f(0.159f, 0.086f);
    glVertex2f(0.168f, 0.086f);
    glVertex2f(0.170f, 0.098f);
    glVertex2f(0.164f, 0.11f);
    glVertex2f(0.182f, 0.096f);
    glVertex2f(0.190f, 0.096f);
    glVertex2f(0.193f, 0.103f);
    glVertex2f(0.164f, 0.182f);
    glVertex2f(0.155f, 0.222f);
    glVertex2f(0.155f, 0.305f);
    glVertex2f(0.159f, 0.417f);
    glVertex2f(0.150f, 0.48f);
    glVertex2f(0.127f, 0.547f);
    glVertex2f(0.116f, 0.57f);
    glVertex2f(0.094f, 0.586f);
    glVertex2f(0.074f, 0.594f);
    glVertex2f(0.052f, 0.59f);
    glVertex2f(0.030f, 0.578f);
    glVertex2f(0.005f, 0.554f);
    glVertex2f(-0.004f, 0.542f);
    glEnd();
    

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.20f, 0.0f);
    glVertex2f(0.027f, 0.526f);
    glVertex2f(0.005f, 0.538f);
    glVertex2f(-0.008f, 0.534f);
    glVertex2f(-0.017f, 0.526f);
    glVertex2f(-0.024f, 0.511f);
    glVertex2f(-0.028f, 0.495f);
    glVertex2f(-0.026f, 0.479f);
    glVertex2f(-0.026f, 0.475f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.132f, 0.495f);
    glVertex2f(0.116f, 0.522f);
    glVertex2f(0.101f, 0.538f);
    glVertex2f(0.085f, 0.546f);
    glVertex2f(0.074f, 0.546f);
    glVertex2f(0.050f, 0.534f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.209f, -0.346f);
    glVertex2f(0.187f, -0.365f);
    glVertex2f(0.176f, -0.373f);
    glVertex2f(0.163f, -0.35f);
    glVertex2f(0.176f, -0.373f);
    glVertex2f(0.174f, -0.401f);
    glVertex2f(0.167f, -0.425f);
    glVertex2f(0.152f, -0.448f);
    glVertex2f(0.161f, -0.44f);
    glVertex2f(0.174f, -0.444f);
    glVertex2f(0.172f, -0.452f);
    glVertex2f(0.167f, -0.468f);
    glVertex2f(0.156f, -0.464f);
    glVertex2f(0.156f, -0.48f);
    glVertex2f(0.147f, -0.484f);
    glVertex2f(0.136f, -0.48f);
    glVertex2f(0.132f, -0.468f);
    glVertex2f(0.121f, -0.492f);
    glVertex2f(0.114f, -0.492f);
    glVertex2f(0.105f, -0.484f);
    glVertex2f(0.112f, -0.468f);
    glVertex2f(0.101f, -0.484f);
    glVertex2f(0.089f, -0.488f);
    glVertex2f(0.083f, -0.48f);
    glVertex2f(0.085f, -0.46f);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.042f, 0.254f);
    glVertex2f(-0.069f, 0.012f);
    glVertex2f(0.009f, -0.134f);
    glVertex2f(0.009f, -0.134f);
    glVertex2f(0.151f, -0.035f);
    glVertex2f(0.149f, 0.348f);
    glVertex2f(0.116f, 0.546f);
    glVertex2f(0.014f, 0.546f);
    glVertex2f(-0.022f, 0.475f);
    glVertex2f(-0.029f, 0.4f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.102f, -0.467f);
    glVertex2f(0.084f, -0.459f);
    glVertex2f(0.068f, -0.443f);
    glVertex2f(0.059f, -0.42f);
    glVertex2f(0.059f, -0.392f);
    glVertex2f(0.057f, -0.376f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.064f, -0.429f);
    glVertex2f(0.040f, -0.445f);
    glVertex2f(0.022f, -0.449f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.016f, -0.401f);
    glVertex2f(0.042f, -0.409f);
    glVertex2f(0.060f, -0.405f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.056f, -0.437f);
    glVertex2f(0.056f, -0.457f);
    glVertex2f(0.049f, -0.468f);
    glVertex2f(0.036f, -0.457f);
    glVertex2f(0.042f, -0.464f);
    glVertex2f(0.040f, -0.48f);
    glVertex2f(0.033f, -0.484f);
    glVertex2f(0.022f, -0.472f);
    glVertex2f(0.018f, -0.48f);
    glVertex2f(0.009f, -0.484f);
    glVertex2f(0.002f, -0.48f);
    glVertex2f(-0.002f, -0.468f);
    glVertex2f(-0.009f, -0.472f);
    glVertex2f(-0.022f, -0.472f);
    glVertex2f(-0.022f, -0.464f);
    glVertex2f(-0.018f, -0.449f);
    glVertex2f(-0.009f, -0.449f);
    glVertex2f(-0.031f, -0.441f);
    glVertex2f(-0.042f, -0.425f);
    glVertex2f(-0.056f, -0.389f);
    glVertex2f(-0.056f, -0.366f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.013f, -0.385f);
    glVertex2f(-0.053f, -0.366f);
    glVertex2f(-0.087f, -0.322f);
    glVertex2f(-0.111f, -0.271f);
    glVertex2f(-0.127f, -0.204f);
    glVertex2f(-0.124f, -0.144f);
    glVertex2f(-0.109f, -0.148f);
    glVertex2f(-0.129f, -0.148f);
    glVertex2f(-0.133f, -0.125f);
    glVertex2f(-0.124f, -0.085f);
    glVertex2f(-0.113f, -0.057f);
    glVertex2f(-0.129f, -0.061f);
    glVertex2f(-0.113f, -0.01f);
    glVertex2f(-0.104f, 0.002f);
    glVertex2f(-0.113f, 0.002f);
    glVertex2f(-0.102f, 0.034f);
    glVertex2f(-0.087f, 0.053f);
    glVertex2f(-0.069f, 0.065f);
    glVertex2f(-0.058f, 0.069f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(-0.041f, 0.287f);
    glVertex2f(-0.048f, 0.2f);
    glVertex2f(-0.061f, 0.137f);
    glVertex2f(-0.077f, 0.101f);
    glVertex2f(-0.106f, 0.081f);
    glVertex2f(-0.101f, 0.073f);
    glVertex2f(-0.090f, 0.073f);
    glVertex2f(-0.077f, 0.077f);
    glVertex2f(-0.075f, 0.057f);
    glVertex2f(-0.066f, 0.057f);
    glVertex2f(-0.053f, 0.069f);
    glVertex2f(-0.057f, 0.053f);
    glVertex2f(-0.057f, 0.03f);
    glVertex2f(-0.048f, 0.022f);
    glVertex2f(-0.028f, 0.034f);
    glVertex2f(-0.019f, 0.042f);
    glVertex2f(-0.013f, 0.026f);
    glVertex2f(-0.010f, 0.026f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.283f, -0.01f);
    glVertex2f(0.197f, -0.081f);
    glVertex2f(0.170f, -0.117f);
    glVertex2f(0.150f, -0.157f);
    glVertex2f(0.141f, -0.2f);
    glVertex2f(0.141f, -0.247f);
    glVertex2f(0.157f, -0.287f);
    glVertex2f(0.173f, -0.295f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.177f, -0.236f);
    glVertex2f(0.170f, -0.267f);
    glVertex2f(0.173f, -0.295f);
    glVertex2f(0.186f, -0.323f);
    glVertex2f(0.208f, -0.342f);
    glVertex2f(0.228f, -0.338f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.230f, -0.275f);
    glVertex2f(0.221f, -0.299f);
    glVertex2f(0.224f, -0.323f);
    glVertex2f(0.228f, -0.342f);
    glVertex2f(0.259f, -0.354f);
    glVertex2f(0.288f, -0.342f);
    glVertex2f(0.315f, -0.303f);
    glVertex2f(0.321f, -0.263f);
    glVertex2f(0.315f, -0.236f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.288f, -0.311f);
    glVertex2f(0.290f, -0.291f);
    glVertex2f(0.288f, -0.279f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.270f, -0.307f);
    glVertex2f(0.286f, -0.275f);
    glVertex2f(0.295f, -0.244f);
    glVertex2f(0.293f, -0.208f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.295f, -0.244f);
    glVertex2f(0.310f, -0.232f);
    glVertex2f(0.335f, -0.216f);
    glVertex2f(0.353f, -0.18f);
    glVertex2f(0.370f, -0.141f);
    glVertex2f(0.379f, -0.109f);
    glVertex2f(0.379f, -0.125f);
    glVertex2f(0.386f, -0.141f);
    glVertex2f(0.395f, -0.125f);
    glVertex2f(0.397f, -0.101f);
    glVertex2f(0.404f, -0.113f);
    glVertex2f(0.413f, -0.117f);
    glVertex2f(0.424f, -0.097f);
    glVertex2f(0.424f, -0.074f);
    glVertex2f(0.417f, -0.054f);
    glVertex2f(0.428f, -0.054f);
    glVertex2f(0.428f, -0.046f);
    glVertex2f(0.408f, -0.01f);
    glVertex2f(0.379f, 0.017f);
    glVertex2f(0.326f, 0.053f);
    glVertex2f(0.268f, 0.085f);
    glVertex2f(0.217f, 0.096f);
    glVertex2f(0.184f, 0.092f);
    glVertex2f(0.166f, 0.081f);
    glVertex2f(0.155f, 0.065f);
    glVertex2f(0.150f, 0.053f);
    glVertex2f(0.150f, 0.033f);
    glVertex2f(0.170f, 0.005f);
    glVertex2f(0.210f, -0.014f);
    glVertex2f(0.237f, -0.03f);
    glVertex2f(0.244f, -0.042f);
    glVertex2f(0.255f, -0.034f);
    glVertex2f(0.257f, -0.014f);
    glVertex2f(0.264f, -0.006f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.28f, 0.10f);
    glVertex2f(-0.28f, 0.10f);
    glVertex2f(-0.224f, 0.147f);
    glVertex2f(-0.204f, 0.175f);
    glVertex2f(-0.197f, 0.202f);
    glVertex2f(-0.198f, 0.198f);
    glVertex2f(-0.201f, 0.218f);
    glVertex2f(-0.216f, 0.273f);
    glVertex2f(-0.225f, 0.325f);
    glVertex2f(-0.227f, 0.368f);
    glVertex2f(-0.218f, 0.4f);
    glVertex2f(-0.232f, 0.404f);
    glVertex2f(-0.263f, 0.376f);
    glVertex2f(-0.278f, 0.341f);
    glVertex2f(-0.281f, 0.309f);
    glVertex2f(-0.278f, 0.281f);
    glVertex2f(-0.272f, 0.265f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.3f, 0.27f);
    glVertex2f(-0.30f, 0.297f);
    glVertex2f(-0.280f, 0.297f);
    glVertex2f(-0.362f, 0.324f);
    glVertex2f(-0.396f, 0.32f);
    glVertex2f(-0.427f, 0.309f);
    glVertex2f(-0.456f, 0.289f);
    glVertex2f(-0.471f, 0.253f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.28f, 0.250f);
    glVertex2f(-0.340f, 0.273f);
    glVertex2f(-0.369f, 0.285f);
    glVertex2f(-0.404f, 0.285f);
    glVertex2f(-0.440f, 0.273f);
    glVertex2f(-0.462f, 0.258f);
    glVertex2f(-0.489f, 0.234f);
    glVertex2f(-0.504f, 0.202f);
    glVertex2f(-0.507f, 0.19f);
    glVertex2f(-0.473f, 0.198f);
    glVertex2f(-0.440f, 0.198f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.25f, 0.125f);
    glVertex2f(-0.365f, 0.218f);
    glVertex2f(-0.403f, 0.218f);
    glVertex2f(-0.430f, 0.202f);
    glVertex2f(-0.447f, 0.19f);
    glVertex2f(-0.458f, 0.171f);
    glVertex2f(-0.465f, 0.155f);
    glVertex2f(-0.461f, 0.139f);
    glVertex2f(-0.430f, 0.147f);
    glVertex2f(-0.392f, 0.143f);
    glVertex2f(-0.343f, 0.131f);
    glVertex2f(-0.314f, 0.115f);
    glVertex2f(-0.281f, 0.111f);
    glVertex2f(-0.252f, 0.123f);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(-0.25f, 0.25f);
    glVertex2f(-0.368f, 0.193f);
    glVertex2f(-0.357f, 0.24f);
    glVertex2f(-0.341f, 0.268f);
    glVertex2f(-0.324f, 0.288f);
    glVertex2f(-0.317f, 0.291f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.25f, 0.25f);
    glVertex2f(-0.316f, 0.255f);
    glVertex2f(-0.318f, 0.228f);
    glVertex2f(-0.325f, 0.208f);
    glVertex2f(-0.341f, 0.192f);
    glVertex2f(-0.321f, 0.204f);
    glVertex2f(-0.301f, 0.208f);
    glVertex2f(-0.281f, 0.204f);
    glVertex2f(-0.258f, 0.192f);
    glVertex2f(-0.245f, 0.168f);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(-0.343f, 0.133f);
    glVertex2f(-0.343f, 0.133f);
    glVertex2f(-0.327f, 0.081f);
    glVertex2f(-0.316f, 0.034f);
    glVertex2f(-0.303f, -0.021f);
    glVertex2f(-0.287f, -0.065f);
    glVertex2f(-0.267f, -0.1f);
    glVertex2f(-0.238f, -0.14f);
    glVertex2f(-0.234f, -0.144f);
    glVertex2f(-0.229f, -0.144f);
    glVertex2f(-0.234f, -0.144f);
    glVertex2f(-0.225f, -0.164f);
    glVertex2f(-0.207f, -0.179f);
    glVertex2f(-0.198f, -0.187f);
    glVertex2f(-0.194f, -0.183f);
    glVertex2f(-0.198f, -0.156f);
    glVertex2f(-0.170f, -0.171f);
    glVertex2f(-0.161f, -0.171f);
    glVertex2f(-0.158f, -0.163f);
    glVertex2f(-0.172f, -0.143f);
    glVertex2f(-0.156f, -0.139f);
    glVertex2f(-0.147f, -0.135f);
    glVertex2f(-0.150f, -0.127f);
    glVertex2f(-0.161f, -0.115f);
    glVertex2f(-0.143f, -0.111f);
    glVertex2f(-0.130f, -0.099f);
    glVertex2f(-0.123f, -0.096f);
    glEnd();


    glBegin(GL_POLYGON);
    glVertex2f(-0.10f, -0.03f);
    glVertex2f(-0.170f, -0.03f);
    glVertex2f(-0.175f, -0.002f);
    glVertex2f(-0.179f, -0.002f);
    glEnd();


    glBegin(GL_TRIANGLE_FAN);
    
    glVertex2f(-0.06f, 0.075f);
    glVertex2f(-0.096f, 0.075f);
    glVertex2f(-0.136f, 0.04f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.158f, 0.026f);
    glVertex2f(-0.138f, 0.038f);
    glVertex2f(-0.118f, 0.053f);
    glVertex2f(-0.098f, 0.069f);
    glVertex2f(-0.071f, 0.097f);
    glVertex2f(-0.100f, -0.069f);
    glVertex2f(-0.129f, -0.093f);
    glVertex2f(-0.133f, -0.105f);
    glVertex2f(-0.142f, -0.109f);
    glVertex2f(-0.149f, -0.113f);
    glVertex2f(-0.149f, -0.113f);
    glVertex2f(-0.191f, -0.049f);
    glVertex2f(-0.189f, -0.002f);
    glVertex2f(-0.180f, 0.03f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-0.208f, 0.105f);
    glVertex2f(-0.226f, 0.208f);
    glVertex2f(-0.201f, 0.129f);
    glVertex2f(-0.188f, 0.061f);
    glVertex2f(-0.177f, 0.022f);
    glVertex2f(-0.197f, -0.085f);
    glVertex2f(-0.257f, -0.081f);
    glVertex2f(-0.324f, 0.077f);
    glVertex2f(-0.324f, 0.077f);
    glVertex2f(-0.339f, 0.125f);
    glVertex2f(-0.388f, 0.18f);
    glVertex2f(-0.304f, 0.302f);
    glVertex2f(-0.279f, 0.295f);
    glVertex2f(-0.241f, 0.295f);
    glVertex2f(-0.204f, 0.235f);
    glVertex2f(-0.201f, 0.152f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(255,255,255);
    glVertex2f(0.031f, 0.391f);
    glVertex2f(0.004f, 0.343f);
    glVertex2f(-0.024f, 0.359f);
    glVertex2f(-0.031f, 0.403f);
    glVertex2f(-0.031f, 0.434f);
    glVertex2f(-0.030f, 0.434f);
    glVertex2f(-0.033f, 0.446f);
    glVertex2f(-0.028f, 0.466f);
    glVertex2f(-0.015f, 0.493f);
    glVertex2f(-0.004f, 0.509f);
    glVertex2f(0.014f, 0.509f);
    glVertex2f(0.030f, 0.501f);
    glVertex2f(0.036f, 0.486f);
    glVertex2f(0.036f, 0.474f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.029f, 0.399f);
    glVertex2f(0.029f, 0.422f);
    glVertex2f(0.031f, 0.45f);
    glVertex2f(0.038f, 0.474f);
    glVertex2f(0.049f, 0.497f);
    glVertex2f(0.067f, 0.509f);
    glVertex2f(0.089f, 0.505f);
    glVertex2f(0.107f, 0.489f);
    glVertex2f(0.120f, 0.466f);
    glVertex2f(0.124f, 0.43f);
    glVertex2f(0.118f, 0.387f);
    glVertex2f(0.111f, 0.371f);
    glVertex2f(0.073f, 0.312f);
    glVertex2f(0.036f, 0.323f);
    glEnd();
    
    
    glColor3ub(248,166,15);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.016f, 0.332f);
    glVertex2f(-0.029f, 0.288f);
    glVertex2f(-0.056f, 0.296f);
    glVertex2f(-0.074f, 0.292f);
    glVertex2f(0.013f, 0.335f);
    glVertex2f(-0.067f, 0.296f);
    glVertex2f(-0.087f, 0.28f);
    glVertex2f(-0.094f, 0.304f);
    glVertex2f(-0.089f, 0.363f);
    glVertex2f(-0.067f, 0.41f);
    glVertex2f(-0.034f, 0.434f);
    glVertex2f(0.004f, 0.426f);
    glVertex2f(0.035f, 0.395f);
    glVertex2f(0.053f, 0.363f);
    glVertex2f(0.053f, 0.351f);
    glVertex2f(0.055f, 0.304f);
    glVertex2f(0.033f, 0.276f);
    glVertex2f(0.004f, 0.276f);
    glVertex2f(-0.029f, 0.288f);
    glEnd();
    
    
    
    glColor3ub(249,168,7);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.026f, -0.605f);
    glVertex2f(0.021f, -0.466f);
    glVertex2f(0.013f, -0.486f);
    glVertex2f(0.015f, -0.545f);
    glVertex2f(0.015f, -0.569f);
    glVertex2f(0.008f, -0.577f);
    glVertex2f(-0.047f, -0.597f);
    glVertex2f(-0.101f, -0.597f);
    glVertex2f(-0.134f, -0.589f);
    glVertex2f(-0.150f, -0.597f);
    glVertex2f(-0.159f, -0.621f);
    glVertex2f(-0.176f, -0.632f);
    glVertex2f(-0.181f, -0.656f);
    glVertex2f(-0.181f, -0.668f);
    glVertex2f(-0.172f, -0.656f);
    glVertex2f(-0.161f, -0.66f);
    glVertex2f(-0.150f, -0.684f);
    glVertex2f(-0.136f, -0.684f);
    glVertex2f(-0.132f, -0.704f);
    glVertex2f(-0.127f, -0.688f);
    glVertex2f(-0.123f, -0.684f);
    glVertex2f(-0.105f, -0.704f);
    glVertex2f(-0.081f, -0.704f);
    glVertex2f(-0.047f, -0.692f);
    glVertex2f(-0.005f, -0.664f);
    glVertex2f(0.026f, -0.644f);
    glVertex2f(0.037f, -0.64f);
    glVertex2f(0.055f, -0.636f);
    glVertex2f(0.066f, -0.617f);
    glVertex2f(0.068f, -0.593f);
    glVertex2f(0.061f, -0.569f);
    glVertex2f(0.046f, -0.561f);
    glVertex2f(0.033f, -0.569f);
    glVertex2f(0.030f, -0.534f);
    glVertex2f(0.030f, -0.486f);
    glVertex2f(0.021f, -0.47f);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.062f, 0.186f);
    glVertex2f(0.013f, 0.209f);
    glVertex2f(-0.014f, 0.268f);
    glVertex2f(-0.032f, 0.288f);
    glVertex2f(-0.041f, 0.292f);
    glVertex2f(0.056f, 0.351f);
    glVertex2f(0.061f, 0.181f);
    glVertex2f(0.055f, 0.347f);
    glVertex2f(0.064f, 0.367f);
    glVertex2f(0.084f, 0.371f);
    glVertex2f(0.106f, 0.371f);
    glVertex2f(0.119f, 0.359f);
    glVertex2f(0.119f, 0.339f);
    glVertex2f(0.110f, 0.328f);
    glVertex2f(0.115f, 0.304f);
    glVertex2f(0.115f, 0.268f);
    glVertex2f(0.110f, 0.237f);
    glVertex2f(0.097f, 0.197f);
    glVertex2f(0.081f, 0.17f);
    glVertex2f(0.057f, 0.138f);
    glVertex2f(0.019f, 0.13f);
    glVertex2f(-0.001f, 0.146f);
    glVertex2f(-0.014f, 0.166f);
    glVertex2f(0.004f, 0.162f);
    glVertex2f(0.010f, 0.177f);
    glVertex2f(0.012f, 0.209f);
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.132f, -0.594f);
    glVertex2f(0.130f, -0.468f);
    glVertex2f(0.136f, -0.484f);
    glVertex2f(0.136f, -0.539f);
    glVertex2f(0.147f, -0.59f);
    glVertex2f(0.147f, -0.594f);
    glVertex2f(0.185f, -0.594f);
    glVertex2f(0.239f, -0.582f);
    glVertex2f(0.265f, -0.582f);
    glVertex2f(0.281f, -0.606f);
    glVertex2f(0.294f, -0.61f);
    glVertex2f(0.303f, -0.638f);
    glVertex2f(0.303f, -0.657f);
    glVertex2f(0.292f, -0.642f);
    glVertex2f(0.287f, -0.65f);
    glVertex2f(0.283f, -0.653f);
    glVertex2f(0.287f, -0.673f);
    glVertex2f(0.285f, -0.685f);
    glVertex2f(0.276f, -0.665f);
    glVertex2f(0.267f, -0.665f);
    glVertex2f(0.256f, -0.681f);
    glVertex2f(0.236f, -0.689f);
    glVertex2f(0.210f, -0.685f);
    glVertex2f(0.156f, -0.661f);
    glVertex2f(0.119f, -0.642f);
    glVertex2f(0.099f, -0.642f);
    glVertex2f(0.074f, -0.626f);
    glVertex2f(0.070f, -0.606f);
    glVertex2f(0.072f, -0.586f);
    glVertex2f(0.087f, -0.57f);
    glVertex2f(0.107f, -0.574f);
    glVertex2f(0.119f, -0.586f);
    glVertex2f(0.119f, -0.539f);
    glVertex2f(0.119f, -0.491f);
    glVertex2f(0.130f, -0.48f);
    glEnd();
    
    
    glColor3ub(249,0,0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.057f, 0.2f);
    glVertex2f(0.030f, 0.145f);
    glVertex2f(0.026f, 0.169f);
    glVertex2f(0.026f, 0.184f);
    glVertex2f(0.028f, 0.208f);
    glVertex2f(0.033f, 0.228f);
    glVertex2f(0.041f, 0.24f);
    glVertex2f(0.048f, 0.244f);
    glVertex2f(0.059f, 0.24f);
    glVertex2f(0.068f, 0.252f);
    glVertex2f(0.077f, 0.264f);
    glVertex2f(0.088f, 0.264f);
    glVertex2f(0.097f, 0.26f);
    glVertex2f(0.090f, 0.224f);
    glVertex2f(0.081f, 0.196f);
    glVertex2f(0.064f, 0.169f);
    glVertex2f(0.041f, 0.149f);
    glVertex2f(0.030f, 0.149f);
    glEnd();
}

void chickendrop()
{
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(224,145,40);
    glVertex2f(0.070f, 0.0f);
    glVertex2f(-0.123f, -0.1f);
    glVertex2f(-0.136f, -0.084f);
    glVertex2f(-0.156f, -0.088f);
    glVertex2f(-0.181f, -0.116f);
    glVertex2f(-0.161f, -0.12f);
    glVertex2f(-0.154f, -0.132f);
    glVertex2f(-0.174f, -0.136f);
    glVertex2f(-0.190f, -0.159f);
    glVertex2f(-0.172f, -0.167f);
    glVertex2f(-0.167f, -0.175f);
    glVertex2f(-0.183f, -0.195f);
    glVertex2f(-0.192f, -0.219f);
    glVertex2f(-0.192f, -0.246f);
    glVertex2f(-0.172f, -0.235f);
    glVertex2f(-0.179f, -0.27f);
    glVertex2f(-0.174f, -0.31f);
    glVertex2f(-0.170f, -0.325f);
    glVertex2f(-0.163f, -0.306f);
    glVertex2f(-0.152f, -0.333f);
    glVertex2f(-0.132f, -0.369f);
    glVertex2f(-0.103f, -0.401f);
    glVertex2f(-0.090f, -0.408f);
    glVertex2f(-0.092f, -0.373f);
    glVertex2f(-0.074f, -0.373f);
    glVertex2f(-0.054f, -0.389f);
    glVertex2f(-0.041f, -0.42f);
    glVertex2f(-0.039f, -0.432f);
    glVertex2f(-0.023f, -0.42f);
    glVertex2f(-0.014f, -0.381f);
    glVertex2f(-0.007f, -0.401f);
    glVertex2f(-0.001f, -0.381f);
    glVertex2f(-0.001f, -0.373f);
    glVertex2f(0.013f, -0.385f);
    glVertex2f(0.021f, -0.412f);
    glVertex2f(0.026f, -0.44f);
    glVertex2f(0.048f, -0.416f);
    glVertex2f(0.061f, -0.373f);
    glVertex2f(0.075f, -0.381f);
    glVertex2f(0.084f, -0.401f);
    glVertex2f(0.093f, -0.373f);
    glVertex2f(0.090f, -0.337f);
    glVertex2f(0.099f, -0.333f);
    glVertex2f(0.121f, -0.353f);
    glVertex2f(0.133f, -0.397f);
    glVertex2f(0.153f, -0.377f);
    glVertex2f(0.168f, -0.333f);
    glVertex2f(0.175f, -0.286f);
    glVertex2f(0.181f, -0.282f);
    glVertex2f(0.193f, -0.29f);
    glVertex2f(0.201f, -0.321f);
    glVertex2f(0.210f, -0.294f);
    glVertex2f(0.204f, -0.254f);
    glVertex2f(0.197f, -0.242f);
    glVertex2f(0.208f, -0.231f);
    glVertex2f(0.230f, -0.25f);
    glVertex2f(0.244f, -0.286f);
    glVertex2f(0.246f, -0.238f);
    glVertex2f(0.235f, -0.207f);
    glVertex2f(0.208f, -0.167f);
    glVertex2f(0.219f, -0.152f);
    glVertex2f(0.206f, -0.14f);
    glVertex2f(0.224f, -0.132f);
    glVertex2f(0.239f, -0.14f);
    glVertex2f(0.224f, -0.104f);
    glVertex2f(0.201f, -0.084f);
    glEnd();
    
    
    
    glColor3ub(250,213,96);
    glBegin(GL_POLYGON);
    glVertex2f(-0.127f, -0.007f);
    glVertex2f(-0.140f, 0.057f);
    glVertex2f(-0.153f, 0.108f);
    glVertex2f(-0.167f, 0.136f);
    glVertex2f(-0.176f, 0.14f);
    glVertex2f(-0.182f, 0.128f);
    glVertex2f(-0.182f, 0.096f);
    glVertex2f(-0.171f, 0.037f);
    glVertex2f(-0.156f, 0.005f);
    glVertex2f(-0.189f, 0.065f);
    glVertex2f(-0.213f, 0.084f);
    glVertex2f(-0.231f, 0.092f);
    glVertex2f(-0.247f, 0.076f);
    glVertex2f(-0.244f, 0.053f);
    glVertex2f(-0.222f, 0.005f);
    glVertex2f(-0.202f, -0.022f);
    glVertex2f(-0.218f, -0.003f);
    glVertex2f(-0.238f, 0.005f);
    glVertex2f(-0.249f, -0.003f);
    glVertex2f(-0.258f, -0.026f);
    glVertex2f(-0.253f, -0.046f);
    glVertex2f(-0.233f, -0.066f);
    glVertex2f(-0.207f, -0.078f);
    glVertex2f(-0.229f, -0.086f);
    glVertex2f(-0.238f, -0.105f);
    glVertex2f(-0.233f, -0.129f);
    glVertex2f(-0.220f, -0.145f);
    glVertex2f(-0.200f, -0.141f);
    glVertex2f(-0.189f, -0.129f);
    glVertex2f(-0.141f, -0.09f);
    glEnd();
    
    glColor3ub(220,0,0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.042f, 0.314f);
    glVertex2f(-0.051f, 0.314f);
    glVertex2f(-0.056f, 0.321f);
    glVertex2f(-0.056f, 0.337f);
    glVertex2f(-0.064f, 0.341f);
    glVertex2f(-0.067f, 0.357f);
    glVertex2f(-0.067f, 0.377f);
    glVertex2f(-0.060f, 0.389f);
    glVertex2f(-0.053f, 0.397f);
    glVertex2f(-0.062f, 0.408f);
    glVertex2f(-0.064f, 0.416f);
    glVertex2f(-0.060f, 0.44f);
    glVertex2f(-0.049f, 0.456f);
    glVertex2f(-0.038f, 0.452f);
    glVertex2f(-0.027f, 0.444f);
    glVertex2f(-0.031f, 0.464f);
    glVertex2f(-0.029f, 0.48f);
    glVertex2f(-0.018f, 0.495f);
    glVertex2f(-0.004f, 0.495f);
    glVertex2f(0.011f, 0.48f);
    glVertex2f(0.018f, 0.456f);
    glVertex2f(0.022f, 0.408f);
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glVertex2f(-0.127f, -0.007f);
    glVertex2f(-0.140f, 0.057f);
    glVertex2f(-0.153f, 0.108f);
    glVertex2f(-0.167f, 0.136f);
    glVertex2f(-0.176f, 0.14f);
    glVertex2f(-0.182f, 0.128f);
    glVertex2f(-0.182f, 0.096f);
    glVertex2f(-0.171f, 0.037f);
    glVertex2f(-0.156f, 0.005f);
    glVertex2f(-0.189f, 0.065f);
    glVertex2f(-0.213f, 0.084f);
    glVertex2f(-0.231f, 0.092f);
    glVertex2f(-0.247f, 0.076f);
    glVertex2f(-0.244f, 0.053f);
    glVertex2f(-0.222f, 0.005f);
    glVertex2f(-0.202f, -0.022f);
    glVertex2f(-0.218f, -0.003f);
    glVertex2f(-0.238f, 0.005f);
    glVertex2f(-0.249f, -0.003f);
    glVertex2f(-0.258f, -0.026f);
    glVertex2f(-0.253f, -0.046f);
    glVertex2f(-0.233f, -0.066f);
    glVertex2f(-0.207f, -0.078f);
    glVertex2f(-0.229f, -0.086f);
    glVertex2f(-0.238f, -0.105f);
    glVertex2f(-0.233f, -0.129f);
    glVertex2f(-0.220f, -0.145f);
    glVertex2f(-0.200f, -0.141f);
    glVertex2f(-0.189f, -0.129f);
    glVertex2f(-0.141f, -0.09f);
    
    glEnd();
    
    glColor3ub(247,203,50);
    glBegin(GL_POLYGON);
    glVertex2f(-0.036f, 0.066f);
    glVertex2f(-0.061f, 0.062f);
    glVertex2f(-0.092f, 0.042f);
    glVertex2f(-0.123f, 0.007f);
    glVertex2f(-0.136f, -0.029f);
    glVertex2f(-0.143f, -0.069f);
    glVertex2f(-0.143f, -0.08f);
    glVertex2f(-0.096f, -0.203f);
    glVertex2f(-0.023f, -0.258f);
    glVertex2f(0.037f, -0.262f);
    glVertex2f(0.113f, -0.223f);
    glVertex2f(0.146f, -0.171f);
    glVertex2f(0.164f, -0.128f);
    glVertex2f(0.175f, -0.041f);
    glVertex2f(0.173f, 0.046f);
    glVertex2f(0.164f, 0.09f);
    glVertex2f(-0.036f, 0.07f);
    glEnd();
    
    
    glColor3ub(250,213,96);
    glBegin(GL_POLYGON);
    glVertex2f(-0.076f, -0.184f);
    glVertex2f(-0.065f, -0.212f);
    glVertex2f(-0.061f, -0.224f);
    glVertex2f(-0.036f, -0.216f);
    glVertex2f(-0.016f, -0.196f);
    glVertex2f(0.015f, -0.153f);
    glVertex2f(0.028f, -0.109f);
    glVertex2f(0.028f, -0.07f);
    glVertex2f(0.015f, -0.026f);
    glVertex2f(-0.005f, -0.002f);
    glVertex2f(0.006f, -0.01f);
    glVertex2f(-0.023f, 0.006f);
    glVertex2f(-0.043f, 0.002f);
    glVertex2f(-0.067f, -0.018f);
    glVertex2f(-0.103f, -0.066f);
    glVertex2f(-0.134f, -0.133f);
    glVertex2f(-0.114f, -0.125f);
    glVertex2f(-0.103f, -0.121f);
    glVertex2f(-0.116f, -0.149f);
    glVertex2f(-0.123f, -0.176f);
    glVertex2f(-0.119f, -0.184f);
    glVertex2f(-0.101f, -0.184f);
    glVertex2f(-0.090f, -0.184f);
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex2f(0.093f, 0.339f);
    glVertex2f(0.135f, 0.241f);
    glVertex2f(0.155f, 0.181f);
    glVertex2f(0.171f, 0.122f);
    glVertex2f(0.171f, 0.102f);
    glVertex2f(0.166f, 0.09f);
    glVertex2f(0.157f, 0.082f);
    glVertex2f(0.151f, 0.027f);
    glVertex2f(0.135f, 0.007f);
    glVertex2f(0.122f, 0.011f);
    glVertex2f(0.113f, 0.035f);
    glVertex2f(0.113f, 0.043f);
    glVertex2f(0.084f, -0.012f);
    glVertex2f(0.068f, -0.016f);
    glVertex2f(0.055f, -0.001f);
    glVertex2f(0.055f, 0.023f);
    glVertex2f(0.031f, -0.005f);
    glVertex2f(0.008f, -0.008f);
    glVertex2f(0.000f, -0.001f);
    glVertex2f(-0.005f, 0.039f);
    glVertex2f(-0.023f, 0.035f);
    glVertex2f(-0.032f, 0.043f);
    glVertex2f(-0.036f, 0.059f);
    glVertex2f(-0.032f, 0.102f);
    glVertex2f(-0.025f, 0.15f);
    glVertex2f(-0.029f, 0.193f);
    glVertex2f(-0.038f, 0.264f);
    glVertex2f(-0.043f, 0.327f);
    glVertex2f(-0.032f, 0.375f);
    glVertex2f(-0.012f, 0.399f);
    glVertex2f(0.020f, 0.407f);
    glVertex2f(0.044f, 0.395f);
    glVertex2f(0.060f, 0.379f);
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glVertex2f(-0.127f, -0.007f);
    glVertex2f(-0.140f, 0.057f);
    glVertex2f(-0.153f, 0.108f);
    glVertex2f(-0.167f, 0.136f);
    glVertex2f(-0.176f, 0.14f);
    glVertex2f(-0.182f, 0.128f);
    glVertex2f(-0.182f, 0.096f);
    glVertex2f(-0.171f, 0.037f);
    glVertex2f(-0.156f, 0.005f);
    glVertex2f(-0.189f, 0.065f);
    glVertex2f(-0.213f, 0.084f);
    glVertex2f(-0.231f, 0.092f);
    glVertex2f(-0.247f, 0.076f);
    glVertex2f(-0.244f, 0.053f);
    glVertex2f(-0.222f, 0.005f);
    glVertex2f(-0.202f, -0.022f);
    glVertex2f(-0.218f, -0.003f);
    glVertex2f(-0.238f, 0.005f);
    glVertex2f(-0.249f, -0.003f);
    glVertex2f(-0.258f, -0.026f);
    glVertex2f(-0.253f, -0.046f);
    glVertex2f(-0.233f, -0.066f);
    glVertex2f(-0.207f, -0.078f);
    glVertex2f(-0.229f, -0.086f);
    glVertex2f(-0.238f, -0.105f);
    glVertex2f(-0.233f, -0.129f);
    glVertex2f(-0.220f, -0.145f);
    glVertex2f(-0.200f, -0.141f);
    glVertex2f(-0.189f, -0.129f);
    glVertex2f(-0.141f, -0.09f);
    
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(224,145,40);
    glVertex2f(0.1f, -0.35f);
    glVertex2f(0.186f, -0.076f);
    glVertex2f(0.168f, -0.088f);
    glVertex2f(0.157f, -0.144f);
    glVertex2f(0.139f, -0.187f);
    glVertex2f(0.124f, -0.199f);
    glVertex2f(0.106f, -0.238f);
    glVertex2f(0.106f, -0.215f);
    glVertex2f(0.119f, -0.187f);
    glVertex2f(0.135f, -0.163f);
    glVertex2f(0.117f, -0.163f);
    glVertex2f(0.095f, -0.195f);
    glVertex2f(0.079f, -0.238f);
    glVertex2f(0.064f, -0.227f);
    glVertex2f(0.050f, -0.235f);
    glVertex2f(0.041f, -0.258f);
    glVertex2f(0.039f, -0.238f);
    
    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(224,145,40);
    glVertex2f(-0.121f, -0.179f);
    glVertex2f(-0.126f, -0.171f);
    glVertex2f(-0.121f, -0.147f);
    glVertex2f(-0.106f, -0.124f);
    glVertex2f(-0.135f, -0.135f);
    glVertex2f(-0.121f, -0.1f);
    glVertex2f(-0.133f, -0.084f);
    glVertex2f(-0.153f, -0.088f);
    glVertex2f(-0.173f, -0.104f);
    glVertex2f(-0.170f, -0.1f);
    glVertex2f(-0.160f, -0.31f);
    glVertex2f(-0.013f, -0.249f);
    glVertex2f(-0.015f, -0.25f);
    glVertex2f(-0.024f, -0.222f);
    glVertex2f(-0.037f, -0.207f);
    glVertex2f(-0.037f, -0.21f);
    glVertex2f(-0.057f, -0.226f);
    glVertex2f(-0.084f, -0.187f);
    glVertex2f(-0.088f, -0.187f);
    glVertex2f(-0.104f, -0.187f);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(224,145,40);
    glVertex2f(0.0f, -0.30f);
    glVertex2f(0.041f, -0.258f);
    glVertex2f(0.039f, -0.238f);
    glVertex2f(0.046f, -0.211f);
    glVertex2f(0.033f, -0.227f);
    glVertex2f(0.026f, -0.258f);
    glVertex2f(0.021f, -0.235f);
    glVertex2f(0.024f, -0.199f);
    glVertex2f(0.013f, -0.227f);
    glVertex2f(0.008f, -0.254f);
    glVertex2f(0.001f, -0.231f);
    glVertex2f(0.004f, -0.187f);
    glVertex2f(-0.016f, -0.25f);
    glVertex2f(-0.025f, -0.219f);
    

    glEnd();
    
    
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(222,147,39);
    glVertex2f(0.097f, 0.387f);
    glVertex2f(0.086f, 0.312f);
    glVertex2f(0.053f, 0.328f);
    glVertex2f(0.057f, 0.368f);
    glVertex2f(0.064f, 0.383f);
    glVertex2f(0.097f, 0.407f);
    glVertex2f(0.110f, 0.407f);
    glVertex2f(0.097f, 0.387f);
    glEnd();
    
   
}

void chickendropline()
{
    glLineWidth(2.2);
    glColor3ub(222,147,39);//different color
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.127f, -0.007f);
    glVertex2f(-0.140f, 0.057f);
    glVertex2f(-0.153f, 0.108f);
    glVertex2f(-0.167f, 0.136f);
    glVertex2f(-0.176f, 0.14f);
    glVertex2f(-0.182f, 0.128f);
    glVertex2f(-0.182f, 0.096f);
    glVertex2f(-0.171f, 0.037f);
    glVertex2f(-0.156f, 0.005f);
    glVertex2f(-0.189f, 0.065f);
    glVertex2f(-0.213f, 0.084f);
    glVertex2f(-0.231f, 0.092f);
    glVertex2f(-0.247f, 0.076f);
    glVertex2f(-0.244f, 0.053f);
    glVertex2f(-0.222f, 0.005f);
    glVertex2f(-0.202f, -0.022f);
    glVertex2f(-0.218f, -0.003f);
    glVertex2f(-0.238f, 0.005f);
    glVertex2f(-0.249f, -0.003f);
    glVertex2f(-0.258f, -0.026f);
    glVertex2f(-0.253f, -0.046f);
    glVertex2f(-0.233f, -0.066f);
    glVertex2f(-0.207f, -0.078f);
    glVertex2f(-0.229f, -0.086f);
    glVertex2f(-0.238f, -0.105f);
    glVertex2f(-0.233f, -0.129f);
    glVertex2f(-0.220f, -0.145f);
    glVertex2f(-0.200f, -0.141f);
    glVertex2f(-0.189f, -0.129f);
    glVertex2f(-0.141f, -0.09f);
    
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(0.093f, 0.339f);
    glVertex2f(0.135f, 0.241f);
    glVertex2f(0.155f, 0.181f);
    glVertex2f(0.171f, 0.122f);
    glVertex2f(0.171f, 0.102f);
    glVertex2f(0.166f, 0.09f);
    glVertex2f(0.157f, 0.082f);
    glVertex2f(0.151f, 0.027f);
    glVertex2f(0.135f, 0.007f);
    glVertex2f(0.122f, 0.011f);
    glVertex2f(0.113f, 0.035f);
    glVertex2f(0.113f, 0.043f);
    glVertex2f(0.084f, -0.012f);
    glVertex2f(0.068f, -0.016f);
    glVertex2f(0.055f, -0.001f);
    glVertex2f(0.055f, 0.023f);
    glVertex2f(0.031f, -0.005f);
    glVertex2f(0.008f, -0.008f);
    glVertex2f(0.000f, -0.001f);
    glVertex2f(-0.005f, 0.039f);
    glVertex2f(-0.023f, 0.035f);
    glVertex2f(-0.032f, 0.043f);
    glVertex2f(-0.036f, 0.059f);
    glVertex2f(-0.032f, 0.102f);
    glVertex2f(-0.025f, 0.15f);
    glVertex2f(-0.029f, 0.193f);
    glVertex2f(-0.038f, 0.264f);
    glVertex2f(-0.043f, 0.327f);
    glVertex2f(-0.032f, 0.375f);
    glVertex2f(-0.012f, 0.399f);
    glVertex2f(0.020f, 0.407f);
    glVertex2f(0.044f, 0.395f);
    glVertex2f(0.060f, 0.379f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(0.097f, 0.383f);
    glVertex2f(0.095f, 0.352f);
    glVertex2f(0.086f, 0.312f);
    glVertex2f(0.050f, 0.328f);
    glVertex2f(0.057f, 0.364f);
    glVertex2f(0.061f, 0.379f);
    glVertex2f(0.081f, 0.399f);
    glVertex2f(0.104f, 0.407f);
    glVertex2f(0.110f, 0.407f);
    glVertex2f(0.050f, 0.328f);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(-0.011f, 0.325f);
    glVertex2f(-0.004f, 0.318f);
    glVertex2f(0.004f, 0.325f);
    glVertex2f(0.009f, 0.341f);
    glVertex2f(0.009f, 0.349f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glVertex2f(0.027f, 0.365f);
    glVertex2f(0.036f, 0.365f);
    glVertex2f(0.040f, 0.373f);
    glVertex2f(0.040f, 0.385f);
    glEnd();

    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(-0.042f, 0.314f);
    glVertex2f(-0.051f, 0.314f);
    glVertex2f(-0.056f, 0.321f);
    glVertex2f(-0.056f, 0.337f);
    glVertex2f(-0.064f, 0.341f);
    glVertex2f(-0.067f, 0.357f);
    glVertex2f(-0.067f, 0.377f);
    glVertex2f(-0.060f, 0.389f);
    glVertex2f(-0.053f, 0.397f);
    glVertex2f(-0.062f, 0.408f);
    glVertex2f(-0.064f, 0.416f);
    glVertex2f(-0.060f, 0.44f);
    glVertex2f(-0.049f, 0.456f);
    glVertex2f(-0.038f, 0.452f);
    glVertex2f(-0.027f, 0.444f);
    glVertex2f(-0.031f, 0.464f);
    glVertex2f(-0.029f, 0.48f);
    glVertex2f(-0.018f, 0.495f);
    glVertex2f(-0.004f, 0.495f);
    glVertex2f(0.011f, 0.48f);
    glVertex2f(0.018f, 0.456f);
    glVertex2f(0.022f, 0.408f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(-0.108f, -0.185f);
    glVertex2f(-0.124f, -0.181f);
    glVertex2f(-0.088f, -0.185f);
    glVertex2f(-0.092f, -0.182f);
    glVertex2f(-0.114f, -0.186f);
    glVertex2f(-0.123f, -0.178f);
    glVertex2f(-0.123f, -0.162f);
    glVertex2f(-0.112f, -0.131f);
    glVertex2f(-0.103f, -0.123f);
    glVertex2f(-0.123f, -0.131f);
    glVertex2f(-0.137f, -0.131f);
    glVertex2f(-0.117f, -0.083f);
    glVertex2f(-0.085f, -0.036f);
    glVertex2f(-0.045f, 0.0f);
    glVertex2f(-0.017f, 0.008f);
    glVertex2f(0.017f, -0.028f);
    glVertex2f(0.028f, -0.079f);
    glVertex2f(0.023f, -0.131f);
    glVertex2f(-0.001f, -0.174f);
    glVertex2f(-0.030f, -0.21f);
    glVertex2f(-0.057f, -0.221f);
    glEnd();
    
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(0.164f, 0.089f);
    glVertex2f(0.173f, 0.042f);
    glVertex2f(0.175f, -0.017f);
    glVertex2f(0.171f, -0.092f);
    glVertex2f(0.151f, -0.168f);
    glVertex2f(0.137f, -0.191f);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glColor3ub(0,0,0);
    glVertex2f(-0.120f, -0.098f);
    glVertex2f(-0.133f, -0.082f);
    glVertex2f(-0.158f, -0.086f);
    glVertex2f(-0.178f, -0.11f);
    glVertex2f(-0.187f, -0.122f);
    glVertex2f(-0.167f, -0.118f);
    glVertex2f(-0.153f, -0.134f);
    glVertex2f(-0.175f, -0.138f);
    glVertex2f(-0.191f, -0.161f);
    glVertex2f(-0.171f, -0.173f);
    glVertex2f(-0.184f, -0.201f);
    glVertex2f(-0.189f, -0.232f);
    glVertex2f(-0.189f, -0.244f);
    glVertex2f(-0.173f, -0.232f);
    glVertex2f(-0.178f, -0.268f);
    glVertex2f(-0.175f, -0.307f);
    glVertex2f(-0.169f, -0.331f);
    glVertex2f(-0.160f, -0.3f);
    glVertex2f(-0.147f, -0.339f);
    glVertex2f(-0.124f, -0.379f);
    glVertex2f(-0.100f, -0.398f);
    glVertex2f(-0.087f, -0.406f);
    glVertex2f(-0.093f, -0.371f);
    glVertex2f(-0.069f, -0.379f);
    glVertex2f(-0.047f, -0.398f);
    glVertex2f(-0.038f, -0.438f);
    glVertex2f(-0.022f, -0.418f);
    glVertex2f(-0.015f, -0.402f);
    glVertex2f(-0.013f, -0.379f);
    glVertex2f(-0.004f, -0.406f);
    glVertex2f(0.000f, -0.383f);
    glVertex2f(0.000f, -0.371f);
    glVertex2f(0.018f, -0.394f);
    glVertex2f(0.022f, -0.418f);
    glVertex2f(0.027f, -0.442f);
    glVertex2f(0.045f, -0.422f);
    glVertex2f(0.056f, -0.398f);
    glVertex2f(0.062f, -0.375f);
    glVertex2f(0.080f, -0.383f);
    glVertex2f(0.085f, -0.402f);
    glVertex2f(0.093f, -0.371f);
    glVertex2f(0.093f, -0.335f);
    glVertex2f(0.105f, -0.331f);
    glVertex2f(0.120f, -0.359f);
    glVertex2f(0.133f, -0.398f);
    glVertex2f(0.156f, -0.371f);
    glVertex2f(0.171f, -0.327f);
    glVertex2f(0.173f, -0.288f);
    glVertex2f(0.180f, -0.284f);
    glVertex2f(0.198f, -0.307f);
    glVertex2f(0.202f, -0.327f);
    glVertex2f(0.213f, -0.288f);
    glVertex2f(0.207f, -0.252f);
    glVertex2f(0.200f, -0.24f);
    glVertex2f(0.213f, -0.236f);
    glVertex2f(0.233f, -0.26f);
    glVertex2f(0.245f, -0.288f);
    glVertex2f(0.245f, -0.24f);
    glVertex2f(0.238f, -0.209f);
    glVertex2f(0.211f, -0.169f);
    glVertex2f(0.218f, -0.153f);
    glVertex2f(0.205f, -0.138f);
    glVertex2f(0.227f, -0.134f);
    glVertex2f(0.242f, -0.141f);
    glVertex2f(0.211f, -0.09f);
    glVertex2f(0.191f, -0.074f);
    glVertex2f(0.169f, -0.086f);
    
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    glVertex2f(0.186f, -0.076f);
    glVertex2f(0.168f, -0.088f);
    glVertex2f(0.157f, -0.144f);
    glVertex2f(0.139f, -0.187f);
    glVertex2f(0.124f, -0.199f);
    glVertex2f(0.106f, -0.238f);
    glVertex2f(0.106f, -0.215f);
    glVertex2f(0.119f, -0.187f);
    glVertex2f(0.135f, -0.163f);
    glVertex2f(0.117f, -0.163f);
    glVertex2f(0.095f, -0.195f);
    glVertex2f(0.079f, -0.238f);
    glVertex2f(0.064f, -0.227f);
    glVertex2f(0.050f, -0.235f);
    glVertex2f(0.041f, -0.258f);
    glVertex2f(0.039f, -0.238f);
    glVertex2f(0.046f, -0.211f);
    glVertex2f(0.033f, -0.227f);
    glVertex2f(0.026f, -0.258f);
    glVertex2f(0.021f, -0.235f);
    glVertex2f(0.024f, -0.199f);
    glVertex2f(0.013f, -0.227f);
    glVertex2f(0.008f, -0.254f);
    glVertex2f(0.001f, -0.231f);
    glVertex2f(0.004f, -0.187f);
    glVertex2f(-0.016f, -0.25f);
    glVertex2f(-0.025f, -0.219f);
    

    glVertex2f(-0.036f, -0.207f);
    glVertex2f(-0.030f, -0.242f);
    glVertex2f(-0.059f, -0.242f);
    glVertex2f(-0.067f, -0.203f);
    glVertex2f(-0.087f, -0.183f);
    glVertex2f(-0.110f, -0.183f);
    glVertex2f(-0.121f, -0.179f);
    glVertex2f(-0.123f, -0.155f);
    glVertex2f(-0.110f, -0.124f);
    glVertex2f(-0.130f, -0.132f);
    glVertex2f(-0.134f, -0.132f);
    glEnd();

}
