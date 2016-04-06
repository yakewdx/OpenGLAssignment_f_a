#pragma once

//#include "stdafx.h"
#include<GLUT/glut.h>
#include<iostream>
#include<GLUT/glut.h>
#include<cstring>
#include"Vec3.h"
using namespace std;
typedef struct EyePoint  
{  
	GLfloat x;  
	GLfloat y;  
	GLfloat z;  
}EYEPOINT;  
EYEPOINT Eye;  
GLint WinWidth;  
GLint WinHeight;
#define MAX_CHAR   128
double vecpoint[100];
int vecN;
void drawString(const char* str) {
    static int isFirstCall = 1;
    static GLuint lists;
	int len=strlen(str);
	int i=0;
    if( isFirstCall ) 
	{                    
         isFirstCall = 0;   
         lists = glGenLists(MAX_CHAR);
         //wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
     }
     // 调用每个字符对应的显示列表，绘制每个字符
    for(i=0;i<len;i++)
         glCallList(lists + str[i]);
}
void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);//清除颜色
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	char pos[100];
	float a,b,c;
	a=Eye.x;
	b=Eye.y;
	c=Eye.z;
	sprintf(pos,"%.3lf,%.3lf,%.3lf",a,b,c);
	//glRasterPos2f(5.0f, 5.0f);
	drawString(pos);
	glRasterPos3f(5.0f, 0.0f,-0.2f);
    drawString("X");
	glRasterPos3f(0.0f, 5.0f,0.0f);
    drawString("Y");
	glRasterPos3f(0.0f, 0.2f,5.0f);
    drawString("Z");
	glRasterPos3f(0.0f, 0.2f,-0.2f);
    drawString("0");
	glLineWidth(3.0);
	glBegin(GL_LINES);
	glColor3f(1.0f,0.0f,0.0f);
	glVertex3d(-5.0,0.0,0.0);
	glVertex3d(5.0,0.0,0.0);
	//箭头


	glVertex3d(4.3,0.0,0.3);
	glVertex3d(5.0,0.0,0.0);
	glVertex3d(4.3,0.0,-0.3);
	glVertex3d(5.0,0.0,0.0);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3d(0.0,-5.0,0.0);
	glVertex3d(0.0,5.0,0.0);

	glVertex3d(0.0,4.3,0.3);
	glVertex3d(0.0,5.0,0.0);
	glVertex3d(0.0,4.3,-0.3);
	glVertex3d(0.0,5.0,0.0);
	
	glColor3f(0.0f,0.0f,1.0f);
	glVertex3d(0.0,0.0,-5.0);
	glVertex3d(0.0,0.0,5.0);

	glVertex3d(0.0,0.3,4.3);
	glVertex3d(0.0,0.0,5.0);
	glVertex3d(0.0,-0.3,4.3);
	glVertex3d(0.0,0.0,5.0);
	int j=0;
	for(int i=0;i<vecN;i++)//循环显示输入的向量
	{
		if(i!=vecN-1)glColor3f(0.5f,0.5f,0.5f);
		else glColor3f(1.0f,1.0f,1.0f);
		glVertex3d(vecpoint[j],vecpoint[j+1],vecpoint[j+2]);
		j=j+3;
		glVertex3d(0.0,0.0,0.0);
	}
	glColor3f(0.5f,0.5f,0.5f);
	glEnd();
	glFlush();
}

void reshape(int w,int h)
{
	GLfloat nRange = 5.0f;
    glViewport(0,0,w,h);
	 WinWidth  = w;  
    WinHeight = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w <= h)
        glOrtho(-nRange,nRange,-nRange*h/w,nRange*h/w,-1000,1000);
    else
        glOrtho(-nRange*w/h,nRange*w/h,-nRange,nRange,-1000,1000);
    gluLookAt(Eye.x,  Eye.y,  Eye.z,  0.0f,  0.0f,  0.0f,  0.0f,  0.0f,  1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void OnKeyboard(int key, int x, int y)  
{  
    switch(key)  
    {  
    case GLUT_KEY_LEFT:  
        Eye.x -= 2.0f;  
        break;  
    case GLUT_KEY_RIGHT:  
        Eye.x += 2.0f;  
        break;  
    case GLUT_KEY_DOWN:  
        Eye.y -= 2.0f;  
        break;  
    case GLUT_KEY_UP:  
        Eye.y += 2.0f;  
        break;  
	case GLUT_KEY_F1:  
        Eye.z -= 2.0f;  
        break;  
    case GLUT_KEY_F2:  
        Eye.z += 2.0f;
		break;
#ifdef _WIN32
	case VK_ESCAPE:
		exit(0);
		break;
#endif
#ifdef __APPLE__
    case 27:
        exit(0);
        break;
#endif
    }

	reshape(WinWidth, WinHeight);
    glutPostRedisplay();  
}
void displaymain(int argc, char **argv,int N,double *point)
{
	int i;
	vecN=N;
	for(i=0;i<3*N;i++)
	{
		vecpoint[i]=point[i];
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100,100); 
	glutInitWindowSize(500,500);
	glutCreateWindow("向量显示"); 
	glutReshapeFunc(reshape);
	glutDisplayFunc(&myDisplay); 
	glutSpecialFunc(OnKeyboard); 
	Eye.x = 60.0f;                   //初始化眼睛的坐标  
    Eye.y = 30.0f;  
    Eye.z = 30.0f;
	//init();
	glutMainLoop();
}
