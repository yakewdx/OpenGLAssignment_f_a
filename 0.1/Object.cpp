//
//  Object.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#include "Object.hpp"
#include <iostream>


void Object::setDebugState(debug_state _state) {
    this->state = _state;
}

void Object::debug_print(int frame) {
    if (frame == 0) {
        frame = 1;
    }
    
    ++timer;
    
    if (timer % frame == 0) {
        if (state & PRINT_POS) {
            debug_print_pos();
        }
        if (state & PRINT_NAME) {
            debug_print_name();
        }
        if (state & PRINT_MATRIX) {
            debug_print_matrix();
        }
    }
    
}

Vec3F Object::getWorldCoordinate() {
    Vec3F p(0,0,0);
    Object * obj = this;
    while (obj && obj != world) {
        float time = PlayGround::getPlayGround()->getTime();
        glPushMatrix();
        glLoadIdentity();
        obj->updateObject(time);
        CMatrix mat;
        glGetFloatv(GL_MODELVIEW, mat);
        Vec3F p1(0,0,0);
        p1 = mat.MulPoint(p1);
        p = p + p1;
        glPopMatrix();
        obj = obj->getReference();
    }
    return p;
}

// 
void Object::update(const float time) {
    
//    CMatrix m0 = ref->getMatrix();
//    //std::cout << m0 << std::endl;
//    Vec3F v = m0.MulPoint(Vec3F(0,0,0));
//    CMatrix m1;
//    m1.SetTrans(v);
//    glLoadMatrixf(m1);
//    updateObject(time);
//    glGetFloatv(GL_MODELVIEW, mat);
//    m1 = world->getMatrix().GetInverse()*mat;
//    setPosition(m1.MulPoint(Vec3F(0,0,0)));
//    setMatrix(mat);
    
    CMatrix m0 = ref->getMatrix();
    glLoadMatrixf(m0);
    updateObject(time);
    glGetFloatv(GL_MODELVIEW, mat);
    setPosition(world->getMatrix().GetInverse()*mat.MulPoint(Vec3F(0,0,0)));
    
}


void Object::draw(){
    
#ifdef __GL__DEBUG__
    debug_print();
#endif
    glPushMatrix();
    glLoadMatrixf(mat);
    initObject();
    drawObject();
    glPopMatrix();
}

void Object::debug_print_matrix() {
    std::cout << getMatrix() << std::endl;
}

void Object::debug_print_pos() {
    std::cout << getPosition() << std::endl;
}
void Object::debug_print_name() {
    std::cout << "Name: " << name << std::endl;
}

Vec3F Object::getPosition() {
    return pos;
    //return Vec3F(mat.m03, mat.m13, mat.m23);
}

void Object::setPosition(Vec3F v) {
    pos = v;
}

Object::Object() {
    selected = false;
    static Name n = 0;
    this->name = ++n;
    this->mat = CMatrix::IDENTITY();
    this->ref = PlayGround::getPlayGround()->world;
    //this->world = this;
    this->state = PRINT_NONE;
    timer = 0;
    PlayGround::getPlayGround()->addObject(this);
    world = PlayGround::getPlayGround()->world;
}

Object::~Object() {
    PlayGround::getPlayGround()->removeObject(this);
}