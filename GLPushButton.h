//
//  GLPushButton.h
//  OpenGLTest
//
//  Created by 王冬晓 on 16/4/6.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifndef GLPushButton_h
#define GLPushButton_h

#include <stdio.h>
#include "Object.h"

class GLPushButton: public Object {
    void initObject() override;
    void updateObject(const float time) override;
    void drawObject(const float time) override;
};
#endif /* GLPushButton_h */
