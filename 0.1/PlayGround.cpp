//
//  PlayGround.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#include "PlayGround.hpp"
#include "Object.hpp"
#include "Sun.hpp"
#include "Earth.hpp"
#include "Moon.hpp"
#include "ViewController.hpp"
#include "Trajectory.hpp"

PlayGround * PlayGround::ground;


PlayGround::PlayGround(){
    
    time = 0.0f;
    
    controller = new ViewController();
    controller->setKeyboardInputHandler(new naiveKeyboardInputHandler());
    controller->setPlayGround(this);
    
}

void draw_test(GLenum type) {
    static float time = 0;
    time += 0.5f;
    
    static CMatrix mat = CMatrix::IDENTITY();
    Vec3F vec(0,0,0);
    
    
    //glPushMatrix();
    glLoadIdentity();
    
//    glPushMatrix();
//    glLoadIdentity();
//    
//    // 对第一个茶壶的变换
//    glRotatef(time, 0, 0, 1);
//    glTranslatef(10.0f, 0, 0);
//    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
//    vec = mat.MulPoint(vec);
//    std::cout << "1: " << vec << std::endl;      // 这一帧第一个茶壶的坐标
//    
//    vec = {0,0,0};
//    
//    // 对第二个茶壶的变换
//    glRotatef(time*3, 0, 0, 1);
//    glTranslatef(10.0f, 0, 0);
//    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
//    vec = mat.MulPoint(vec);
//    std::cout << "2: " << vec << std::endl;      // 这一帧第二个茶壶的坐标
//    
//    vec = vec * -1;
//    mat.SetTrans(vec);
//    //std::cout << vec << std::endl;
//    
//    glPopMatrix();
    vec = mat.MulPoint(Vec3F(0,0,0));
    vec = vec * -1;
    mat.SetTrans(vec);
    glLoadMatrixf(mat);
    std::cout<<mat<<std::endl;
    
    glRotatef(time, 0, 0, 1);
    glTranslatef(10.0f, 0, 0);
    //glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    glColor3f(0.3, 0.4, 0.5);
    glutSolidTeapot(5.0f);
    glRotatef(time*3, 0, 0, 1);
    glTranslatef(10.0f, 0, 0);
    glutSolidTeapot(3.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    //std::cout<<mat<<std::endl;
    //glPopMatrix();
    
}


void PlayGround::display() {
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // 创建透视效果视图
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-75, 75, -50, 50, -50, 50);
    gluPerspective(50.0f, 1.5f, 1.0f, 150.0f);
    glMatrixMode(GL_MODELVIEW);
    drawScene(GL_RENDER);
    //draw_test(GL_RENDER);
    glFlush();
    glutSwapBuffers();
    getPlayGround()->updateTime();
}

void PlayGround::reshape(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0f, 1.5f, 1.0f, 150.0f);
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);  // 注意默认的reshape函数中的glViewport函数设置.
}


PlayGround * PlayGround::getPlayGround() {
    if (ground == nullptr) {
        ground = new PlayGround();
    }
    return ground;
}

void PlayGround::addObject(Object * obj) {
    vec.push_back(obj);
}

void PlayGround::drawScene(GLenum type) {
    getPlayGround()->controller->setView();
    for (std::vector<Object *>::iterator it = getPlayGround()->vec.begin(); it != getPlayGround()->vec.end();it++)
    {
        (*it)->update(getPlayGround()->getTime());
    }
    for (std::vector<Object *>::iterator it = getPlayGround()->vec.begin(); it != getPlayGround()->vec.end();it++)
    {
        if (type == GL_SELECT) {
            glPushName((*it)->getName());
        }
        (*it)->draw();
        if (type == GL_SELECT) {
            glPopName();
        }
    }
}




void PlayGround::keyboardFunc(unsigned char key, int x, int y) {
    getPlayGround()->controller->onKeyPushed(key, x, y);
    display();
}

void PlayGround::mouseFunc(int button, int state, int x, int y) {
    //getPlayGround()->controller->onMouseClicked(button, state, x, y);  暂时不使用
    if (button == GLUT_LEFT_BUTTON) {               //鼠标左键
        if (state == GLUT_DOWN) {
            int s = selectFunc(x, y);
            for (std::vector<Object *>::iterator it = getPlayGround()->vec.begin(); it != getPlayGround()->vec.end();it++)
            {
                if ((*it)->getName() == s) {
                    //getPlayGround()->controller->setFollow((*it));
                    (*it)->setIsSelected(true);
                }
                else (*it)->setIsSelected(false);
            }
            display();
        }
    } else if (button == GLUT_RIGHT_BUTTON) {       //鼠标右键
        if (state == GLUT_DOWN) {
            int s = selectFunc(x, y);
            for (std::vector<Object *>::iterator it = getPlayGround()->vec.begin(); it != getPlayGround()->vec.end();it++)
            {
                if ((*it)->getName() == s) {
                    getPlayGround()->controller->setFollow((*it));
                    //(*it)->setIsSelected(true);
                }
                (*it)->setIsSelected(false);
            }
            display();
        }
    }
}

int PlayGround::selectFunc(int x, int y) {
    GLuint selectBuff[32]={0};                  //创建一个保存选择结果的数组
    GLint hits, viewport[4];
    
    glGetIntegerv(GL_VIEWPORT, viewport);       //获得viewport
    glSelectBuffer(64, selectBuff);             //告诉OpenGL初始化selectbuffer
    glRenderMode(GL_SELECT);                    //进入选择模式
    
    glInitNames();                              //初始化名字栈
    
    
    glMatrixMode(GL_PROJECTION);                //进入投影阶段准备拾取
    glPushMatrix();                             //保存以前的投影矩阵
    glLoadIdentity();                           //载入单位矩阵
    
    gluPickMatrix( x,                           // 设定我们选择框的大小，建立拾取矩阵，就是上面的公式
                  viewport[3]-y,                // viewport[3]保存的是窗口的高度，窗口坐标转换为OpenGL坐标
                  2,2,                          // 选择框的大小为2，2
                  viewport                      // 视口信息，包括视口的起始位置和大小
                  );
    
    //glOrtho(-75, 75, -50, 50, -50, 50);         //拾取矩阵乘以投影矩阵，这样就可以让选择框放大为和视体一样大
    gluPerspective(50.0f, 1.5f, 1.0f, 150.0f);
    glMatrixMode(GL_MODELVIEW);
    
    drawScene(GL_SELECT);                       // 该函数中渲染物体，并且给物体设定名字
    
    //glMatrixMode(GL_PROJECTION);
    glPopMatrix();                              // 返回正常的投影变换
    
    hits = glRenderMode(GL_RENDER);             // 从选择模式返回正常模式,该函数返回选择到对象的个数
    std::cout << hits << " hit(s)" << std::endl;
    GLuint selected;
    if(hits > 0) {                              //	选择结果处理
        selected = selectBuff[3];
        return selected;
    }
    else return -1;
    
    
    
    
    
}
void PlayGround::removeObject(Object * obj) {
    int size = (int)vec.size();
    int count = 0;
    int num = 0;
    for (std::vector<Object *>::iterator it = vec.begin(); it != vec.end();)
    {
        if (*it == obj)
        {
            vec.erase(it++);
            num++;
        }
        else
        {
            it++;
        }
        count++;
        if (count + num >= size) {
            break;
        }
    }

}

void PlayGround::initSetting(){
    
    glClearColor(0.0,0.0,0.0,1.0);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST); // Make round points, not square points
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);  // Antialias the lines
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    
    world = new Object();
    removeObject(world);
    controller->setWorldOrigin(world);
    
}

void PlayGround::initObjects() {
    
}

void PlayGround::arrangeObjects() {
    
    Sun * sun = new Sun();
    sun->setReference(world);

    Trajectory * trajectory_earth = new Trajectory(30);
    Trajectory * trajectory_moon = new Trajectory(6);
    
    Earth * earth = new Earth();
    trajectory_earth->setCelBody(earth);
    
    Moon * moon = new Moon();
    trajectory_moon->setCelBody(moon);
    
    moon->setReference(earth);
    trajectory_moon->setReference(earth);
 
    
    controller->setFollow(sun);
    
    
}

const float & PlayGround::getTime() {
    return time;
}

void PlayGround::updateTime() {
    time += 1.0f;
}

void PlayGround::onTimer(int value) {
    display();
}

GLboolean PlayGround::init(int argc, char * argv[]) {
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(960,640);
    glutInitWindowPosition(150,150);
    glutCreateWindow("rotate sphere");
    glutDisplayFunc(PlayGround::display);
    glutReshapeFunc(PlayGround::reshape);
    glutIdleFunc(PlayGround::display);
    glutKeyboardFunc(PlayGround::keyboardFunc);
    glutMouseFunc(PlayGround::mouseFunc);
    getPlayGround()->initSetting();
    getPlayGround()->arrangeObjects();
    glutMainLoop();
    return EXIT_SUCCESS;
}