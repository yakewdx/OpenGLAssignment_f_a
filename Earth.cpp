//
//  Earth.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifdef _WIN32
#include "stdafx.h"
#endif


#include "Earth.h"
#include "universal_setting.h"

void Earth::initObject() {
    
    //initialize
    glColor3f(0.3f, 0.2f, 1.0f);
    size = 4.0f;
    revoRadius = 30.0f;
    revoArgularVelocity = 1.0f;

}

