//
//  Trajectory.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifndef Trajectory_hpp
#define Trajectory_hpp

#include <stdio.h>

#include "Object.hpp"

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
    void drawObject() override;
    void initObject() override;
    void updateObject(const float time) override;
};


#endif /* Trajectory_hpp */
