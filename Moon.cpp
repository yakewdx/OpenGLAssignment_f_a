//
//  Moon.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifdef _WIN32
#include "stdafx.h"
#endif


#include "Moon.h"
#include "universal_setting.h"

void Moon::initObject() {
    
    glColor3f(1.0f, 1.0f, 0.5f);
    size = 1.5f;
    revoRadius = 6.0f;
    revoArgularVelocity = -2.0f;
}

