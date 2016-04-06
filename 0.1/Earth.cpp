//
//  Earth.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#include "Earth.hpp"
#include "universal_setting.h"

void Earth::initObject() {
    
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
    
    //initialize
    glColor3f(0.3f, 0.2f, 1.0f);
    size = 4.0f;
    revoRadius = 30.0f;
    revoArgularVelocity = 1.0f;

}

void Earth::drawObject() {
    if (selected) {
        glColor3f(1.0, 1.0, 1.0);
        glutWireCube(size * 2);
        glColor3f(0.3f, 0.2f, 1.0f);
    }
    static float _time = 0.0f;
    glRotatef(_time, 0, 1, 1);
    glutWireSphere(size, 30, 30);
    //glRotatef(_time, 0, 1, 1);
    _time += 1.0f;
}

void Earth::updateObject(const float time) {
    glRotated(time * revoArgularVelocity, 0, 0, 1);
    glTranslatef(revoRadius, 0, 0);
    glRotated(-time * revoArgularVelocity, 0, 0, 1);
    //glRotatef(time, 0, 1, 1);
}