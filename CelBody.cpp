//
//  CelBody.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifdef _WIN32
#include "stdafx.h"
#endif

#include "CelBody.h"

CelBody::CelBody() {
    size = 0.0f;
    revoRadius = 0.0f;
    revoArgularVelocity = 0.0f;
    rotationArgularVelocity = 0.0f;
    rotatingShaft = Vec3F(0,0,0);
}

void CelBody:: drawObject(const float time) {
    if (selected) {
        glColor3f(1.0, 1.0, 1.0);
        glutWireCube(size*2);
        //glColor3f(1.0f, 0.2f, 0.3f);
        initObject();
    }
    glRotatef(time, rotatingShaft.getX(), rotatingShaft.getY(), rotatingShaft.getZ());
    glutSolidSphere(size, 40, 40);
}
void CelBody:: updateObject(const float time) {
    glRotatef(time * revoArgularVelocity, 0, 0, 1);
    glTranslatef(revoRadius, 0, 0);
    glRotatef(-time * revoArgularVelocity, 0, 0, 1);
}