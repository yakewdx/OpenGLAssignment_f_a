//
//  universal_setting.h
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifndef universal_setting_h
#define universal_setting_h


#ifdef __APPLE__
#include<GLUT/glut.h>
#include<Opengl/gl.h>
#endif


// 我也不造你这应该包含啥= =自己改一下……
#ifdef __WIN32__
#include<GLUT/glut.h>

#endif

#include "Matrix.h"
#include "Vec3.h"


const double pi = 3.1415926535;

#define __GL__DEBUG__

#endif /* universal_setting_h */
