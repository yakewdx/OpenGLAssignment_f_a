#pragma once

//#include "stdafx.h"
#include<GLUT/glut.h>
#include<iostream>
#include<math.h>
#include<cstring>
#include <cstdlib>

GLfloat spin = 0;
GLdouble _x = 0;

int selected = 0;

const GLfloat pi = 3.1415926;
GLfloat ex = 0.0f,
ey = 0.0f,
ez = -20.0f,
cx = 0.0f,
cy = 0.0f,
cz = 0.0f,
ux = 0.0f,
uy = 1.0f,
uz = 0.0f;


void init()
{
    
    glClearColor(0.3,0.3,0.3,1.0);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
}

static GLfloat angle = 0.1f;

void setView() {
    
}
void draw(GLenum mode) {
    
    GLfloat R_moon = 3.0f;
    
    glPushMatrix();
    
    glTranslatef(ex, ey, ez);
    
    glRotatef(cx, 1.0, 0, 0);
    glRotatef(cy, 0.0, 1.0, 0);
    glRotatef(cz, 0, 0, 1.0);
    
    if (selected >= 3) {
        glTranslatef(-R_moon, 0.0f, 0.0f);
        glRotatef(angle, 0.0f, 1.0f, 0.0f);
        glRotatef(angle * -0.3, -1.0f, 1.0f, 0.0f);
    }
    if (selected >= 2) {
        glRotatef(angle, 0.0, 1.0f, 0);
        glTranslatef(-15.0f, 0.0f, 0.0f);
        //glRotatef(angle * -0.03, -1.0f, 1.0f, 0.0f);
        
    }
    
    
    {
        glPushMatrix();
        
        GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_light_ambient[]  = {1.0f, 0.6f, 0.6f, 1.0f};
        GLfloat sun_light_diffuse[]  = {1.0f, 0.6f, 0.6f, 1.0f};
        GLfloat sun_light_specular[] = {0.6f, 0.6f, 0.6f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
        glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
        
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
        
        GLfloat sun_mat_ambient[]  = {1.0f, .8f, .8f, 1.0f};
        GLfloat sun_mat_diffuse[]  = {1.0f, .8f, .8f, 1.0f};
        GLfloat sun_mat_specular[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_emission[] = {0.5f, 0.0f, 0.0f, 1.0f};
        GLfloat sun_mat_shininess  = 0.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,   sun_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   sun_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  sun_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,  sun_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, sun_mat_shininess);
        
        
        
        
        //glRotatef(angle * 0.03, -1.0f, 1.0f, 0.0f);
        
        if (mode == GL_SELECT) {
            glPushName(1);
        }
        glutSolidSphere(8.0, 40, 32);
        if (mode == GL_SELECT) {
            glPopName();
        }
        
        
    }
    
    
    // 定义地球的材质并绘制地球
    {
        GLfloat earth_mat_ambient[]  = {0.0f, 0.0f, 0.5f, 1.0f};
        GLfloat earth_mat_diffuse[]  = {0.0f, 0.0f, 0.5f, 1.0f};
        GLfloat earth_mat_specular[] = {0.0f, 0.0f, 1.0f, 1.0f};
        GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat earth_mat_shininess  = 30.0f;
        
        
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,   earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,  earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
        
        
        glDisable(GL_LIGHTING);
        
        glPushMatrix();
        //glTranslatef(15.0f, 0.0f, 0.0f);
        glColor3f(0.3, 0.3, 1.0);
        
        if (mode == GL_SELECT) {
            glPushName(-1);
        }
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 100; i++) {
            GLfloat R = 15.0f;
            glVertex3f(R*cos(2*pi / 100 * i ), 0, R*sin(2*pi / 100 * i));
        }
        glEnd();
        
        
        glPopMatrix();
        
        
        {
            for (int i = 0; i < 30; i++) {
                glPushMatrix();
                glPointSize(9 - i*0.3);
                glColor3f(0.3, 0.3, 1.0 - (GLfloat)i / 42);
                glTranslatef(15.0f, 0.0f, 0.0f);
                glRotatef(angle - 5 - i, 0.0f, -1.0f, 0.0f);
                
                glBegin(GL_POINTS);
                glVertex3f(0, 0, 0);
                glEnd();
                glPopMatrix();
            }
        }
        
        if (mode == GL_SELECT) {
            glPopName();
        }
        glEnable(GL_LIGHTING);
        
        if (selected == 0) {
            glRotatef(angle, 0.0f, -1.0f, 0.0f);
            glTranslatef(15.0f, 0.0f, 0.0f);
        }
        if (selected ==2) {
            glTranslatef(15.0f, 0.0f, 0.0f);
            glRotatef(angle, 0.0f, -1.0f, 0.0f);
        }
        
        
        
        glPushMatrix();
        
        glRotatef(-angle, 0, -1, 0);
        //glRotatef(-angle * 0.03, -1.0f, 1.0f, 0.0f);
        
        
        glRotatef(angle * 0.3, -1.0f, 1.0f, 0.0f);
        
        if (mode == GL_SELECT) {
            glPushName(2);
        }
        glutSolidSphere(2.0, 40, 32);
        if (mode == GL_SELECT) {
            glPopName();
        }
        glPopMatrix();
        
    }
    
    {
        GLfloat earth_mat_ambient[]  = {0.5f, 0.5f, 0.0f, 1.0f};
        GLfloat earth_mat_diffuse[]  = {0.5f, 0.5f, 0.0f, 1.0f};
        GLfloat earth_mat_specular[] = {1.0f, 0.0f, 1.0f, 1.0f};
        GLfloat earth_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat earth_mat_shininess  = 30.0f;
        
        glMaterialfv(GL_FRONT, GL_AMBIENT,   earth_mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   earth_mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  earth_mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION,  earth_mat_emission);
        glMaterialf (GL_FRONT, GL_SHININESS, earth_mat_shininess);
        
        glDisable(GL_LIGHTING);
        
        glPushMatrix();
        glColor3f(0.3, 0.3, 1.0);
        
        if (mode == GL_SELECT) {
            glPushName(-1);
        }
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 100; i++) {
            
            glVertex3f(R_moon*cos(2*pi / 100 * i ), 0, R_moon*sin(2*pi / 100 * i));
        }
        glEnd();
        glPopMatrix();
        
        for (int i = 0; i < 30; i++) {
            glPushMatrix();
            glPointSize(3 - i*0.1);
            glColor3f(0.6, 0.6, 1.0 - (GLfloat)i / 20);
            glRotatef(angle - 5 - i, 0.0f, -1.0f, 0.0f);
            glTranslatef(R_moon, 0.0f, 0.0f);
            
            glBegin(GL_POINTS);
            
            glVertex3f(0, 0, 0);
            
            glEnd();
            
            glPopMatrix();
        }
        
        if (mode == GL_SELECT) {
            glPopName();
        }
        glEnable(GL_LIGHTING);
        
        glPushMatrix();
        glRotatef(angle, 0.0f, -1.0f, 0.0f);
        glTranslatef(R_moon, 0.0f, 0.0f);
        
        glPushMatrix();
        
        glRotatef(-angle, 0.0f, -1.0f, 0.0f);
        glRotatef(-angle * 0.3, -1.0f, 1.0f, 0.0f);
        glRotatef(-angle, 0, -1, 0);
        //glRotatef(-angle * 0.03, -1.0f, 1.0f, 0.0f);
        
        if (selected >= 2) {
            //glRotatef(-angle * -0.03, -1.0f, 1.0f, 0.0f);
            glRotatef(-angle, 0.0, 1.0f, 0);
            //glTranslatef(15.0f, 0.0f, 0.0f);
        }
        if (selected >= 3) {
            glRotatef(-angle * -0.3, -1.0f, 1.0f, 0.0f);
            glRotatef(-angle, 0.0f, 1.0f, 0.0f);
            //glTranslatef(R_moon, 0.0f, 0.0f);
        }
        if (mode == GL_SELECT) {
            glPushName(-1);
        }
        //glRectf(-2, -2, 2, 2);
        if (mode == GL_SELECT) {
            glPopName();
        }
        glPopMatrix();
        
        if (mode == GL_SELECT) {
            glPushName(3);
        }
        glutSolidSphere(0.3f, 40, 32);
        if (mode == GL_SELECT) {
            glPopName();
        }
        glPopMatrix();
    }
    
    
    glPopMatrix();
    
    glPopMatrix();
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // 创建透视效果视图
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0f, 1.5f, 1.0f,80.0f);
    glMatrixMode(GL_MODELVIEW);
    
    draw(GL_RENDER);
    glFlush();
    glutSwapBuffers();
    
}

void Angle(){
    
    angle += 1.0f;
    display();
}


void reshape(int w,int h)
{
    glViewport(0.0,0.0,(GLsizei) w,(GLsizei) h);
}
void keyboardFunc(unsigned char key,int x,int y)
{
    
    switch(key)
    {
        case 'a':
            ex -= 1;
            std::cout << "ex changed -" << std::endl;
            std::cout << ex << std::endl;
            break;
        case 'd':
            ex += 1;
            std::cout << "ex changed +" << std::endl;
            std::cout << ex << std::endl;
            break;
        case 'w':
            ey += 1;
            std::cout << "ey changed" << std::endl;
            std::cout << ey << std::endl;
            break;
        case 's':
            ey -= 1;
            std::cout << "ey changed" << std::endl;
            std::cout << ey << std::endl;
            break;
        case 'z':
            ez += 1;
            std::cout << "ez changed" << std::endl;
            std::cout << ez << std::endl;
            break;
        case 'x':
            ez -= 1;
            std::cout << "ez changed" << std::endl;
            std::cout << ez << std::endl;
            break;
            
        case 'f':
            cx -= 1;
            std::cout << "cx changed" << std::endl;
            std::cout << cx << std::endl;
            break;
        case 'h':
            cx += 1;
            std::cout << "cx changed" << std::endl;
            std::cout << cx << std::endl;
            break;
        case 't':
            cy += 1;
            std::cout << "cy changed" << std::endl;
            std::cout << cy << std::endl;
            break;
        case 'g':
            cy -= 1;
            std::cout << "cy changed" << std::endl;
            std::cout << cy << std::endl;
            break;
        case 'v':
            cz += 1;
            std::cout << "cz changed" << std::endl;
            std::cout << cz << std::endl;
            break;
        case 'b':
            cz -= 1;
            std::cout << "cz changed" << std::endl;
            std::cout << cz << std::endl;
            break;
        case 'j':
            ux -= 1;
            std::cout << "ux changed" << std::endl;
            std::cout << ux << std::endl;
            break;
        case 'l':
            ux += 1;
            std::cout << "ux changed" << std::endl;
            std::cout << ux << std::endl;
            break;
        case 'i':
            uy += 1;
            std::cout << "uy changed" << std::endl;
            std::cout << uy << std::endl;
            break;
        case 'k':
            uy -= 1;
            std::cout << "uy changed" << std::endl;
            std::cout << uy << std::endl;
            break;
        case 'm':
            uz += 1;
            std::cout << "uz changed" << std::endl;
            std::cout << uz << std::endl;
            break;
        case ',':
            uz -= 1;
            std::cout << "uz changed" << std::endl;
            std::cout << uz << std::endl;
            break;
    }
    if(spin<360)
        spin +=360;
    else if(spin>=360)
        spin -=360;
    reshape(960, 640);
    glLoadIdentity();
}


void processSelect(GLuint *selectBuff) {
    printf("%d\n", selectBuff[0]);
}


void SelectObject(GLint x, GLint y)
{
    GLuint selectBuff[32]={0};//创建一个保存选择结果的数组
    GLint hits, viewport[4];
    
    glGetIntegerv(GL_VIEWPORT, viewport); //获得viewport
    glSelectBuffer(64, selectBuff);	//告诉OpenGL初始化selectbuffer
    glRenderMode(GL_SELECT);	//进入选择模式
    
    glInitNames();	//初始化名字栈
    //glPushName(0);	//在名字栈中放入一个初始化名字，这里为‘0’
    
    
    glMatrixMode(GL_PROJECTION);	//进入投影阶段准备拾取
    glPushMatrix();		//保存以前的投影矩阵
    glLoadIdentity();	//载入单位矩阵
    //setView();
    
    
    gluPickMatrix( x,			// 设定我们选择框的大小，建立拾取矩阵，就是上面的公式
                  viewport[3]-y,	// viewport[3]保存的是窗口的高度，窗口坐标转换为OpenGL坐标
                  2,2,				// 选择框的大小为2，2
                  viewport			// 视口信息，包括视口的起始位置和大小
                  );
    
    //glOrtho(-45.0,45.0,-30.0,30.0,-100.0,100.0);		//拾取矩阵乘以投影矩阵，这样就可以让选择框放大为和视体一样大
    gluPerspective(120.0f, 1.5f, 1.0f,80.0f);
    
    
    draw(GL_SELECT);	// 该函数中渲染物体，并且给物体设定名字
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();	// 返回正常的投影变换
    hits = glRenderMode(GL_RENDER);	// 从选择模式返回正常模式,该函数返回选择到对象的个数
    std::cout << hits << " hit(s)" << std::endl;
    GLuint selected_prev = selected;
    if(hits > 0)
        selected = selectBuff[3];	//	选择结果处理
    else selected = 0;
    printf("selected = %d\n", selected);
}

void mouseFunc(int button,int state,int x,int y)
{
    if(state==GLUT_DOWN){
        SelectObject(x, y);
    }
}

int main(int argc,char *argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(960,640);
    glutInitWindowPosition(150,150);
    glutCreateWindow("rotate sphere");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(Angle);
    glutKeyboardFunc(keyboardFunc);
    glutMouseFunc(mouseFunc);
    init();
    glutMainLoop();
    return EXIT_SUCCESS;
}

