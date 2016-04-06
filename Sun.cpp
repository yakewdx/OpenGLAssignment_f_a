//
//  Sun.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//
#ifdef _WIN32
#include "stdafx.h"
#endif


#include "Sun.h"
#include "universal_setting.h"

void Sun::initObject() {

    glColor3f(1.0f, 0.2f, 0.3f);
    
    // initial setting
    size = 10;
    
    revoRadius = 0.0f;
    revoArgularVelocity = 1.0f;
    rotatingShaft = Vec3F(0,1,1);
}

