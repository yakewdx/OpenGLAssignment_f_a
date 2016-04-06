//
//  Moon.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#include "Moon.hpp"
#include "universal_setting.h"

void Moon::initObject() {
    
    GLfloat moon_mat_ambient[]  = {0.5f, 0.5f, 0.0f, 1.0f};
    GLfloat moon_mat_diffuse[]  = {0.5f, 0.5f, 0.0f, 1.0f};
    GLfloat moon_mat_specular[] = {1.0f, 0.0f, 1.0f, 1.0f};
    GLfloat moon_mat_emission[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat moon_mat_shininess  = 30.0f;
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   moon_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   moon_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  moon_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION,  moon_mat_emission);
    glMaterialf (GL_FRONT, GL_SHININESS, moon_mat_shininess);
    glColor3f(1.0f, 1.0f, 0.5f);
    size = 1.5f;
    revoRadius = 6.0f;
    revoArgularVelocity = -2.0f;
}

void Moon::drawObject() {
    
    if (selected) {
        glColor3f(1.0, 1.0, 1.0);
        glutWireCube(size * 2);
        glColor3f(1.0f, 1.0f, 0.5f);
    }
    
    glutSolidSphere(size, 20, 20);
    
}

void Moon::updateObject(const float time) {
    glRotatef(time * revoArgularVelocity, 0, 0, 1);
    glTranslatef(revoRadius, 0, 0);
    glRotatef(-time * revoArgularVelocity, 0, 0, 1);
}