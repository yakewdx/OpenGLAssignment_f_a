//
//  ViewController.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#pragma once

#include <iostream>
#include "universal_setting.h"
#include "Object.h"


class Object;

class KeyboardInputHandler {
public:
    virtual CMatrix handle(unsigned char key, int x, int y) = 0;
    ~KeyboardInputHandler(){}
};

class naiveKeyboardInputHandler: public KeyboardInputHandler {
    
    float
    ex = 0.0f,
    ey = 0.0f,
    ez = 60.0f,
    cx = 0.0f,
    cy = 0.0f,
    cz = 0.0f,
    ux = 0.0f,
    uy = 0.0f,
    uz = 0.0f;
    
public:
    CMatrix handle (unsigned char key, int x, int y) override;
};

class MouseInputHandler {
public:
    virtual CMatrix handle(int button, int state, int x, int y) = 0;
    ~MouseInputHandler(){}
};


class ViewController {
private:
    KeyboardInputHandler * KIH;
    MouseInputHandler * MIH;
    CMatrix view;
    Object * world_origin;
    Object * follow;
    PlayGround * playground;
    Vec3F previous;
    
public:
    void setPlayGround(PlayGround * _playground){playground = _playground;}
    void setView(Vec3F origin = Vec3F(0,0,0));
    void changeView(CMatrix mat);
    CMatrix getView(){return view;}
    void setWorldOrigin(Object * obj);
    void setFollow(Object * obj);

    ViewController(): KIH(nullptr), MIH(nullptr), view(CMatrix::IDENTITY()), previous(Vec3F(0,0,0)), follow(nullptr){}
    void setKeyboardInputHandler(KeyboardInputHandler * kih) {KIH = kih;}
    void setMouseInputHandler(MouseInputHandler * mih) {MIH = mih;}
    
    void onKeyPushed(unsigned char key, int x, int y){
        
        if (KIH == nullptr) {
            std::cout << "the keyboard input handler is not set yet, \n"
                      << "which means the keyboard input will not be handled.\n";
            return;
        }
        view = KIH->handle(key, x, y);
        setView();
    }
    
    void onMouseClicked(int button, int state, int x, int y){
        
        if (MIH == nullptr) {
            std::cout << "the mouse input handler is not set yet, \n"
            << "which means the mouse input will not be handled.\n";
            return;
        }
        
        MIH->handle(button, state, x, y);
        setView();
    }
    
};

