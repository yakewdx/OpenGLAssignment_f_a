//
//  universal_setting.h
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//
#pragma once



#ifdef _WIN32
#include<gl/glut.h>
#include "stdafx.h"
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

#include "Matrix.h"
#include "Vec3.h"


const double pi = 3.1415926535;

#define __GL__DEBUG__
