#include <glut/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.141592654

float fTranslate;
float fRotate=0;
float fScale = 1.0f;	// set inital scale value to 1.0f

//bool bPersp = true;
bool bAnim = false;
bool bWire = false;
bool run=false;
int wHeight = 0;
int wWidth = 0;
GLint num = 10;

float eye[] = { 0, 0.5, -2};
float center[] = { 0, -4, 10 };
float move_x, move_y, move_z;
GLint number[10000];
bool Open = false;      // 从上面展开
bool OutClose = false;  // 闭合，结束状态在管道外部/内部
bool OutOpen = false;   // 从下面展开，然后平移
int stage = 0;
int flag = 0;
int flag2 = 0;
int s = 0;
double positionY = 3.078;

int change = 0;     // when [time] have a change
int changeTime = 1000;

void drawBarrier();
void drawCoin();
void drawGrid(int num, int offset, bool barrier, bool coin)
{
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(20, 0, 0);
    
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 20, 0);
    
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 20);
    glEnd();
    
    glPushMatrix();
    // decide where the grid is

    if (Open == true)       // open the tube
    {
        //        if (OutClose == true) Open = false;     // 下一个状态：管道闭合
//        if (flag > 4*num) stage++;          // adjust the speed
//        if (flag <= 4*num) flag++;
//        else flag = 0;
        
        double DeltaX82 = 2*(cos(((36-(0.036*stage))/180)*PI)-cos((36.0/180)*PI));
        double DeltaY82 = 2*(sin((36.0/180)*PI)-sin(((36-(0.036*stage))/180)*PI));
        double DeltaX73 = 2*(cos(((72-(0.072*stage))/180)*PI)-cos((72.0/180)*PI));
        double DeltaY73 = 2*(sin((72.0/180)*PI)-sin(((72-(0.072*stage))/180)*PI));
        double DeltaX64 = 2*(cos(((108-(0.108*stage))/180)*PI)-cos((108.0/180)*PI));
        double DeltaY64 = 2*(sin((108.0/180)*PI)-sin(((108-(0.108*stage))/180)*PI));
        double DeltaX55 = 2*(cos(((144-(0.144*stage))/180)*PI)-cos((144.0/180)*PI));
        double DeltaY55 = 2*(sin((144.0/180)*PI)-sin(((144-(0.144*stage))/180)*PI));
        
        if (num == 9)
        {
            if (stage < 1000)
            {
                glRotatef(36*num, 0, 0, 1);         // 绕z轴转
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.036*stage, 0, 0, 1);    // 绕自己轴转
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glTranslatef(-2, -3.078, offset*5);
            }
            
        }
        else if (num == 8)
        {
            if (stage < 1000)
            {
                glTranslatef(-DeltaX82, -DeltaY82, 0);      // 微平移来进行衔接
                glRotatef(36*num, 0, 0, 1);             // 绕z轴旋转
                glTranslatef(1, -3.078, offset*5);      // 平移
                glRotatef(0.072*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(-1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(-4, -3.078, offset*5);
            }
        }
        else if (num == 7)
        {
            if (stage < 1000)
            {
                glTranslatef(-DeltaX82-DeltaX73, -DeltaY82-DeltaY73, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.108*stage, 0, 0, 1);
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glTranslatef(-6, -3.078, offset*5);
            }
        }
        else if (num == 6)
        {
            if (stage < 1000)
            {
                glTranslatef(-DeltaX82-DeltaX73-DeltaX64, -DeltaY82-DeltaY73-DeltaY64, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.144*stage, 0, 0, 1);
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glTranslatef(-8, -3.078, offset*5);
            }
        }
        else if (num == 5)      // put 5 on the left part (with 4,3,2,1)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX82+DeltaX73+DeltaX64+DeltaX55, -DeltaY82-DeltaY73-DeltaY64-DeltaY55, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.180*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glTranslatef(10, -3.078, offset*5);
            }
        }
        else if (num == 4)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX82+DeltaX73+DeltaX64, -DeltaY82-DeltaY73-DeltaY64, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.144*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glTranslatef(8, -3.078, offset*5);
            }
        }
        else if (num == 3)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX82+DeltaX73, -DeltaY82-DeltaY73, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.108*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glTranslatef(6, -3.078, offset*5);
            }
        }
        else if (num == 2)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX82, -DeltaY82, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);      // 平移
                glRotatef(-0.072*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(4, -3.078, offset*5);
            }
        }
        else if (num == 1)
        {
            if (stage < 1000)
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.036*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glTranslatef(2, -3.078, offset*5);
            }
        }
        else
        {
            glRotatef(36*num, 0, 0, 1);
            glTranslatef(0, -3.078, offset*5);
        }
        
    }
    else if (OutClose == true)      // 结束状态是在管道外走
    {
        //        if (OutOpen == true) OutClose = false;  // 下一个状态是从下面展开
//        if (flag > 4*num) stage--;          // adjust the speed
//        if (flag <= 4*num) flag++;
//        else flag = 0;
        
        double DeltaX82 = 2*(cos(((36-(0.036*stage))/180)*PI)-cos((36.0/180)*PI));
        double DeltaY82 = 2*(sin((36.0/180)*PI)-sin(((36-(0.036*stage))/180)*PI));
        double DeltaX73 = 2*(cos(((72-(0.072*stage))/180)*PI)-cos((72.0/180)*PI));
        double DeltaY73 = 2*(sin((72.0/180)*PI)-sin(((72-(0.072*stage))/180)*PI));
        double DeltaX64 = 2*(cos(((108-(0.108*stage))/180)*PI)-cos((108.0/180)*PI));
        double DeltaY64 = 2*(sin((108.0/180)*PI)-sin(((108-(0.108*stage))/180)*PI));
        double DeltaX55 = 2*(cos(((144-(0.144*stage))/180)*PI)-cos((144.0/180)*PI));
        double DeltaY55 = 2*(sin((144.0/180)*PI)-sin(((144-(0.144*stage))/180)*PI));
        
        if (num == 9)
        {
            if (stage > 0)
            {
                glRotatef(36*num, 0, 0, 1);         // 绕z轴转
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.036*stage, 0, 0, 1);    // 绕自己轴转
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
            
        }
        else if (num == 8)
        {
            if (stage > 0)
            {
                glTranslatef(-DeltaX82, -DeltaY82, 0);      // 微平移来进行衔接
                glRotatef(36*num, 0, 0, 1);             // 绕z轴旋转
                glTranslatef(1, -3.078, offset*5);      // 平移
                glRotatef(0.072*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(-1, 0, 0);      // 平移
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 7)
        {
            if (stage > 0)
            {
                glTranslatef(-DeltaX82-DeltaX73, -DeltaY82-DeltaY73, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.108*stage, 0, 0, 1);
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 6)
        {
            if (stage > 0)
            {
                glTranslatef(-DeltaX82-DeltaX73-DeltaX64, -DeltaY82-DeltaY73-DeltaY64, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.144*stage, 0, 0, 1);
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 5)      // put 5 on the left part (with 4,3,2,1)
        {
            if (stage > 0)
            {
                glTranslatef(DeltaX82+DeltaX73+DeltaX64+DeltaX55, -DeltaY82-DeltaY73-DeltaY64-DeltaY55, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.180*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 4)
        {
            if (stage > 0)
            {
                glTranslatef(DeltaX82+DeltaX73+DeltaX64, -DeltaY82-DeltaY73-DeltaY64, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.144*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 3)
        {
            if (stage > 0)
            {
                glTranslatef(DeltaX82+DeltaX73, -DeltaY82-DeltaY73, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.108*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 2)
        {
            if (stage > 0)
            {
                glTranslatef(DeltaX82, -DeltaY82, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);      // 平移
                glRotatef(-0.072*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(1, 0, 0);      // 平移
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else if (num == 1)
        {
            if (stage > 0)
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.036*stage, 0, 0, 1);
                glTranslatef(1, 0, 0);
            }
            else
            {
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(0, -3.078, offset*5);
            }
        }
        else
        {
            glRotatef(36*num, 0, 0, 1);
            glTranslatef(0, -3.078, offset*5);
        }
        
    }
    else if (OutOpen == true)       // open from the bottom
    {
//        if (flag > 4*num) stage++;          // adjust the speed
//        if (flag <= 4*num) flag++;
//        else flag = 0;
        
        if (stage >= 1000)
            if (flag == 7)
                if (positionY > -3.078) positionY -= 0.0005;
        
        double DeltaX73 = 2*(cos(((36-(0.036*stage))/180)*PI)-cos((36.0/180)*PI));
        double DeltaY73 = 2*(sin((36.0/180)*PI)-sin(((36-(0.036*stage))/180)*PI));
        double DeltaX82 = 2*(cos(((72-(0.072*stage))/180)*PI)-cos((72.0/180)*PI));
        double DeltaY82 = 2*(sin((72.0/180)*PI)-sin(((72-(0.072*stage))/180)*PI));
        double DeltaX91 = 2*(cos(((108-(0.108*stage))/180)*PI)-cos((108.0/180)*PI));
        double DeltaY91 = 2*(sin((108.0/180)*PI)-sin(((108-(0.108*stage))/180)*PI));
        double DeltaX00 = 2*(cos(((144-(0.144*stage))/180)*PI)-cos((144.0/180)*PI));
        double DeltaY00 = 2*(sin((144.0/180)*PI)-sin(((144-(0.144*stage))/180)*PI));
        
        if (num == 4)
        {
            if (stage < 1000)
            {
                glRotatef(36*num, 0, 0, 1);         // 绕z轴转
                glTranslatef(1, -3.078, offset*5);
                glRotatef(0.036*stage, 0, 0, 1);    // 绕自己轴转
                glTranslatef(-1, 0, 0);
            }
            else
            {
                glTranslatef(2, positionY, offset*5);
            }
            
        }
        else if (num == 6)
        {
            if (stage < 1000)
            {
                glRotatef(36*num, 0, 0, 1);         // 绕z轴转
                glTranslatef(-1, -3.078, offset*5);
                glRotatef(-0.036*stage, 0, 0, 1);    // 绕自己轴转
                glTranslatef(1, 0, 0);
            }
            else
            {
                glTranslatef(-2, positionY, offset*5);
            }
        }
        else if (num == 3)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX73, DeltaY73, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);      // 平移
                glRotatef(0.072*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(-1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(4, positionY, offset*5);
            }
        }
        else if (num == 7)
        {
            if (stage < 1000)
            {
                glTranslatef(-DeltaX73, DeltaY73, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);      // 平移
                glRotatef(-0.072*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(-4, positionY, offset*5);
            }
        }
        else if (num == 2)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX73+DeltaX82, DeltaY73+DeltaY82, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);      // 平移
                glRotatef(0.108*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(-1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(6, positionY, offset*5);
            }
        }
        else if (num == 8)
        {
            if (stage < 1000)
            {
                glTranslatef(-DeltaX73-DeltaX82, DeltaY73+DeltaY82, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);      // 平移
                glRotatef(-0.108*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(-6, positionY, offset*5);
            }
        }
        else if (num == 1)
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX73+DeltaX82+DeltaX91, DeltaY73+DeltaY82+DeltaY91, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);      // 平移
                glRotatef(0.144*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(-1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(8, positionY, offset*5);
            }
        }
        else if (num == 9)
        {
            if (stage < 1000)
            {
                glTranslatef(-DeltaX73-DeltaX82-DeltaX91, DeltaY73+DeltaY82+DeltaY91, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(-1, -3.078, offset*5);      // 平移
                glRotatef(-0.144*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(-8, positionY, offset*5);
            }
        }
        else if (num == 0)      // with 1,2,3,4
        {
            if (stage < 1000)
            {
                glTranslatef(DeltaX73+DeltaX82+DeltaX91+DeltaX00, DeltaY73+DeltaY82+DeltaY91+DeltaY00, 0);
                glRotatef(36*num, 0, 0, 1);
                glTranslatef(1, -3.078, offset*5);      // 平移
                glRotatef(0.180*stage, 0, 0, 1);        // 绕自己轴转
                glTranslatef(-1, 0, 0);      // 平移
            }
            else
            {
                glTranslatef(10, positionY, offset*5);
            }
        }
        else
        {
            glRotatef(36*num, 0, 0, 1);
            glTranslatef(0, -positionY, offset*5);
        }
 
    }

    else
    {
        glRotatef(36*num, 0, 0, 1);
        glTranslatef(0, -3.078, offset*5);
    }
    
/*
    glColor3f(1, 1, 1);         // 方块
    glBegin(GL_QUADS);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 5);
    glVertex3f(-1, 0, 5);
    glEnd();
*/
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, -0.1, -2.5);
    glScalef(2, 0.2, 5);
    glutWireCube(1);
    glPopMatrix();
    
    glColor3f(0, 0, 0);         // 格子
    glBegin(GL_LINES);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 0, 5);
    glVertex3f(1, 0, 5);
    glVertex3f(-1, 0, 5);
    glVertex3f(-1, 0, 5);
    glVertex3f(-1, 0, 0);
    glEnd();
    
    if(barrier)
        drawBarrier();
 
    if(coin)
        drawCoin();
    glPopMatrix();
}

void drawBarrier()
{
    glColor3f(1, 0, 1);
    
    glPushMatrix();

    glTranslatef(0, 0.5, 2.5);
    glScalef(1.5, 1, 4);
    glutWireCube(1);
    
    glPopMatrix();
}

void drawCoin()
{
    GLUquadric* quad, *top, *bottom;
    quad = gluNewQuadric();
    top = gluNewQuadric();
    bottom = gluNewQuadric();
    
    glColor3f(0.8f, 0.5f, 0.2f);
    glPushMatrix();
    
    glTranslatef(0, 0.5, 2.5);
    gluCylinder(quad, 0.5, 0.5, 0.1, 20, 20);
    
    glPushMatrix();
    glTranslatef(0, 0.05, 0);
    gluDisk(bottom, 0, 0.5, 20, 1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, -0.05, 0);
    gluDisk(top, 0, 0.5, 20, 1);
    glPopMatrix();
    
    glPopMatrix();
}

void updateView(int width, int height)
{
    glViewport(0, 0, width, height);
    // Reset The Current Viewport
    
    glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
    glLoadIdentity();									// Reset The Projection Matrix
    
    float whRatio = (GLfloat)width / (GLfloat)height;
//    if (bPersp) {
        gluPerspective(90.0f, whRatio, 0.1f, 1000.0f);
        //glFrustum(-3, 3, -3, 3, 3,100);
//    }
//    else {
//        glOrtho(-10*whRatio, 10*whRatio, -10, 10, -100, 100);
//    }
    
    glMatrixMode(GL_MODELVIEW);     // Select The Modelview Matrix
}

void reshape(int width, int height)
{
    if (height == 0)										// Prevent A Divide By Zero By
    {
        height = 1;										// Making Height Equal One
    }
    
    wHeight = height;
    wWidth = width;
    
    updateView(wWidth, wHeight);
}

void idle()
{
    glutPostRedisplay();
}




void key(unsigned char k, int x, int y)
{
    switch (k)
    {
        case 27:
        case 'q': {exit(0); break; }
//        case 'p': {bPersp = !bPersp; break; }
            
        case ' ': {bAnim = !bAnim; break; }
        case 'o': {bWire = !bWire; break; }
            
        case 'a': {
            fRotate-=36;
            break;
        }
        case 'd': {
            fRotate+=36;
            break;
        }
/*
        case 'w': {
            eye[1] -= 0.2f;
            center[1] -= 0.2f;
            break;
        }
        case 's': {
            eye[1] += 0.2f;
            center[1] += 0.2f;
            break;
        }
*/
        case 'z': {
            eye[2] -= 0.2f;
            center[2] -= 0.2f;
            break;
        }
        case 'c': {
            eye[2] += 0.2f;
            center[2] += 0.2f;
            break;
        }
            
            //change the color of the light0
        case 'r': {
            run=!run;
            
            break;
        }
/*
        case 'm': {
            stage = 0;
            flag = 0;
            OutClose = false;
            OutOpen = false;
            Open = true;
            break;
        }
        case 'n': {
            stage = 1000;
            flag = 0;
            Open = false;
            OutOpen = false;
            OutClose = true;
            break;
        }
        case 'b': {
            stage = 0;
            flag = 0;
            Open = false;
            OutClose = false;
            OutOpen = true;
            positionY = 3.078;
            break;
        }
*/
            
    }
    
    updateView(wWidth, wHeight);
}

#define MAXNUM 5000
int barrierChance[MAXNUM];
int coinChance[MAXNUM];
bool isBarrier = false;
bool isCoin = false;

void redraw()
{
    int i;
    srand((unsigned int)time(0));
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();									// Reset The Current Modelview Matrix
    
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              0, 1, 0);
    
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    
    glRotatef(fRotate, 0, 0, 1.0f);
    
    //    glScalef(0.2, 0.2, 0.2);
    
    flag2 += 1;
    if (flag2 > 30) flag2 = 0;

    for (int q=0;q<num;q++)         // number of cylinders
    {
        if (Open && flag == 1) stage++;
        else if (OutClose && flag == 1) stage--;
        else if (OutOpen && flag == 1) stage++;
        flag++;
        if (flag > 10) flag = 0;
        
        if(barrierChance[q] == 0)
        {
            barrierChance[q] = (rand() % (10 - 1 + 1)) + 1;
        }
        if(coinChance[q]==0)
        {
            if(q == 0 || (q != 0 && coinChance[q -1] == barrierChance[q]))
            {
                coinChance[q] = (rand() % (10 - 1 + 1)) + 1;
                if(coinChance[q] == barrierChance[q])
                {
                    coinChance[q] += 1;
                    if(coinChance[q] == 11)
                        coinChance[q] = 1;
                }
            }
            else
                coinChance[q] = coinChance[q - 1];
        }
        for (i=0;i<10;i++)
        {
            if(i + 1 == barrierChance[q])
            {
                isBarrier = true;
            }
            if(i + 1 == coinChance[q])
            {
                isCoin = true;
            }
            drawGrid(i, q, isBarrier, isCoin);
            isBarrier = false;
            isCoin = false;
        }
    }

    // change mode
    if (run)
    {
        change++;
        if (change == changeTime)
        {
            change = 0;
            //srand((unsigned int)time(0));
            changeTime = random() % 500 + 500;
            
            // change
            if (!Open && !OutOpen && !OutClose)     // 在管道里面
            {
                if (random() % 2 == 0)
                {
                    stage = 0;
                    flag = 0;
                    Open = true;
                }
                else
                {
                    positionY = 3.078;
                    flag = 0;
                    stage = 0;
                    OutOpen = true;
                }
            }
            else if (Open)      // 展开状态
            {
                Open = false;
                stage = 1000;
                flag = 0;
                OutClose = true;    // 关闭，在管道里面
            }
            else if (OutOpen)   // 展开
            {
                OutOpen = false;
                stage = 1000;
                flag = 0;
                OutClose = true;    // 关闭
            }
            else if (OutClose)
            {
                OutClose = false;
                if (random() % 2 == 0)
                {
                    stage = 0;
                    flag = 0;
                    Open = true;
                }
                else
                {
                    positionY = 3.078;
                    flag = 0;
                    stage = 0;
                    OutOpen = true;
                }
            }
        }
    }
    
    //    GLUquadricObj *qobj;
    //    GLUquadricObj *qobj2;
    //    qobj = gluNewQuadric();
    //    qobj2 = gluNewQuadric();
    //
    //    GLfloat line[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //    GLfloat clear[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //    glPushMatrix();
    //
    //    //gluQuadricDrawStyle(qobj, GLU_LINE); /* flat shaded */
    //    //gluQuadricNormals(qobj, GLU_FLAT);
    //    glColor3f(1,1,1);
    //    gluQuadricDrawStyle(qobj, GLU_FILL); // all polygons wireframe
    //    gluCylinder(qobj, 10, 10, 10*num, 10,num);
    //
    //    glPopMatrix();
    //
    //
    //    glColor3f(0,0,0);
    //    gluQuadricDrawStyle(qobj2, GLU_LINE);
    //
    //
    //    gluCylinder(qobj2, 10, 10,10*num, 10,num);
    //
    //    // barriers
    //    for (int i=0;i<num/2;i++)
    //    {
    //        if (number[0] == 0)         // set random positions
    //        {
    //            srand((int)time(0));
    //            for (int j=0;j<num/2;j++) number[j] = rand() % 10 + 1;
    //        }
    //        move_x = 0;
    //        move_y = 0;
    //        move_z = i*10;      // position in z axis
    //        Draw_barrier(i);
    //    }
    //
    
    if (run) {
        if (flag2 == 10) num=num+1;
        eye[2] += 0.1f;
        center[2] += 0.1f;
        //        if (number[num/2] == 0)
        //        {
        //            number[num/2] = rand() % 10 + 1;
        //        }
    }
    //
    
    
    if (bAnim) fRotate += 0.1f;
    
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1280, 697);
    int windowHandle = glutCreateWindow("Tube");
    
    glutDisplayFunc(redraw);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    
    glutIdleFunc(idle);
    
    glutMainLoop();
    return 0;
}
