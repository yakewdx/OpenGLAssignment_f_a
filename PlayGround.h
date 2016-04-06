//
//  PlayGround.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "universal_setting.h"
#include <vector>

class Object;
class ViewController;

class PlayGround {
private:
    ViewController * controller;
    static PlayGround * ground;
    //std::vector<Object *> vec;
    PlayGround();
    ~PlayGround(){}
    float time;
    
public:
    
    Object * world;
    void arrangeObjects();
    void initSetting();
    void addObject(Object *);
    //void removeObject(Object *);
    const float & getTime();
    void updateTime();
    void initObjects();
    
    static void onTimer(int value);
    static PlayGround * getPlayGround();
    static GLboolean init(int argc, char * argv[]);
    static void display();
    static void reshape(int w, int h);
    static void idleFunc();
    static void keyboardFunc(unsigned char key, int x, int y);
    static void mouseFunc(int button, int state, int x, int y);
    static int selectFunc(int x, int y);
    static void drawScene(GLenum type);
    
};

