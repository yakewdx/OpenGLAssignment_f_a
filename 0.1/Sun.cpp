//
//  Sun.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#include "Sun.hpp"
#include "universal_setting.h"

void Sun::initObject() {


    
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
    
    GLfloat sun_light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat sun_light_ambient[]  = {1.0f, 0.6f, 0.6f, 1.0f};
    GLfloat sun_light_diffuse[]  = {1.0f, 0.6f, 0.6f, 1.0f};
    GLfloat sun_light_specular[] = {0.6f, 0.6f, 0.6f, 1.0f};
    
    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  sun_light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  sun_light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);
    glColor3f(1.0f, 0.2f, 0.3f);
    
    // initial setting
    size = 10;
    
}


void Sun::drawObject() {
    //glutSolidSphere(size, 40, 40);
    if (selected) {
        glColor3f(1.0, 1.0, 1.0);
        glutWireCube(size*2);
        glColor3f(1.0f, 0.2f, 0.3f);
    }
    glutWireSphere(size, 40, 40);
}

void Sun::updateObject(const float time) {
    
    static CMatrix mat;
    glGetFloatv(GL_MODELVIEW, mat);
    //glTranslatef(0, 0, 60);

}