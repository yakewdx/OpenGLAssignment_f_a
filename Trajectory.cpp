//
//  Trajectory.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//
#ifdef _WIN32
#include "stdafx.h"
#endif

#include "Trajectory.h"
#include "universal_setting.h"
#include "CelBody.h"

void Trajectory::initObject() {
    
    // do nothing
    lineWidth = 2.0f;
    
}

Trajectory::Trajectory(float r) {
    radius = r;
}

void Trajectory::drawObject(const float time) {
    
    glPushMatrix();
    glLineWidth(lineWidth);
    glBegin(GL_LINE_LOOP);
    if (celbody->getRevoAngularVelocity() > 0) {
        for (int i = 0; i < 100; i++) {
            glColor3f(1.0f, i*0.01, i*0.01);
            
            glVertex3f(radius*cos(2*pi / 100 * i ), radius*sin(2*pi / 100 * i), 0);
        }
    } else {
        for (int i = 0; i < 100; i++) {
            glColor3f(1.0f, 1 - i*0.01, 1 - i*0.01);
            glVertex3f(radius*cos(2*pi / 100 * i ), radius*sin(2*pi / 100 * i), 0);
        }
    }
    
    glEnd();
    
    glPopMatrix();
    
}

void Trajectory::updateObject(const float time) {
    
    glRotatef(time * celbody->getRevoAngularVelocity(), 0, 0, 1);
    // do nothing
    
}