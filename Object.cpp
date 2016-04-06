//
//  Object.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifdef _WIN32
#include "stdafx.h"
#endif


#include "Object.h"
#include <iostream>


void Object::setDebugState(debug_state _state) {
    this->state = _state;
}

void Object::removeChild(Object *child) {
    int size = (int)children.size();
    int count = 0;
    for (std::vector<Object *>::iterator it = children.begin(); it != children.end();)
    {
        if (*it == child)
        {
            children.erase(it++);
            break;
        }
        else
        {
            it++;
        }
        count++;
        if (count >= size) {
            break;
        }
    }
}

void Object::setReference(Object * _ref) {
    if (ref) {
        ref->removeChild(this);
    }
    ref = _ref;
    ref->addChild(this);
    setWorld(ref->world);
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

Object * Object::getDescendantByName(Name name) {
    static Object * res = nullptr;
    if (this->name == name) {
        return this;
    }
    Object * obj = nullptr;
    for (std::vector<Object *>::iterator it = children.begin(); it != children.end();it++)
    {
        if (obj = (*it)->getDescendantByName(name))
        {
            break;
        }
    }
    return obj;
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
        glGetFloatv(GL_MODELVIEW_MATRIX, mat);
        Vec3F p1(0,0,0);
        p1 = mat.MulPoint(p1);
        p = p + p1;
        glPopMatrix();
        obj = obj->getReference();
    }
    return p;
}

// update itself
void Object::update(const float time) {
    
    CMatrix m0 = CMatrix::IDENTITY();
    if (ref) m0 = ref->getMatrix();
    else m0 = getMatrix();
    glLoadMatrixf(m0);
    updateObject(time);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat);
    setPosition(world->getMatrix().GetInverse()*mat.MulPoint(Vec3F(0,0,0)));
    
    
    for (std::vector<Object *>::iterator it = children.begin(); it != children.end();it++)
    {
//        CMatrix m0 = CMatrix::IDENTITY();
//        if ((*it)->ref) m0 = (*it)->ref->getMatrix();
//        glLoadMatrixf(m0);
//        (*it)->updateObject(time);
//        glGetFloatv(GL_MODELVIEW, (*it)->mat);
//        setPosition((*it)->world->getMatrix().GetInverse()*(*it)->mat.MulPoint(Vec3F(0,0,0)));
        (*it)->update(time);
    }
    //updateChildren(time);
}

void Object::updateChildren(const float time) {
    
    for (std::vector<Object *>::iterator it = children.begin(); it != children.end();it++)
    {
        (*it)->update(time);
    }
    
}

void Object::draw(const float time, GLenum type){
    
    if (type == GL_SELECT) {
        glPushName(this->getName());
    }
#ifdef __GL__DEBUG__
    debug_print();
#endif
    glPushMatrix();
    glLoadMatrixf(mat);
    initObject();
    drawObject(time);
    glPopMatrix();
    if (type == GL_SELECT) {
        glPopName();
    }

    
    for (std::vector<Object *>::iterator it = children.begin(); it != children.end();it++)
    {
//        if (type == GL_SELECT) {
//            glPushName((*it)->getName());
//        }
//#ifdef __GL__DEBUG__
//        (*it)->debug_print();
//#endif
//        glPushMatrix();
//        glLoadMatrixf((*it)->mat);
//        (*it)->initObject();
//        (*it)->drawObject(time);
//        glPopMatrix();
//        if (type == GL_SELECT) {
//            glPopName();
//        }
        (*it)->draw(time, type);
    }

   // draw(time, type);
}

void Object::drawChildren(const float time, GLenum type) {
    
    

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
    this->ref = nullptr;//PlayGround::getPlayGround()->world;
    //this->world = this;
    this->state = PRINT_NONE;
    timer = 0;
    //PlayGround::getPlayGround()->addObject(this);
    //world = PlayGround::getPlayGround()->world;
}

Object::~Object() {
    //PlayGround::getPlayGround()->removeObject(this);
}