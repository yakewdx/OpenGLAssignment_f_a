//
//  Trajectory.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#pragma once

#include <stdio.h>

#include "Object.h"

class CelBody;
class Trajectory : public Object{
    
private:
    
    float radius;
    float lineWidth;
    float speed;
    CelBody * celbody;
    
public:
    
    void setCelBody(CelBody * _celbody) {celbody = _celbody;}
    Trajectory(float r);
    void drawObject(const float time) override;
    void initObject() override;
    void updateObject(const float time) override;
};

