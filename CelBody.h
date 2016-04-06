//
//  CelBody.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#pragma once

#include <stdio.h>
#include "Object.h"
#include "Vec3.h"

class CelBody : public Object {

protected:
    float size;
    float revoRadius;
    float revoArgularVelocity;
    float rotationArgularVelocity;
    Vec3F rotatingShaft;
//    float
    
public:
    
    CelBody();
    
    void setRevoRadius(float _revoRadius){revoRadius = _revoRadius;}
    float getRevoRadius(){return revoRadius;}
    
    void setRevoArgularVelocity(float _revoAngularVelocity){revoArgularVelocity = _revoAngularVelocity;}
    float getRevoAngularVelocity(){return revoArgularVelocity;}
    
    void setRotationArgularVelocity(float _rotationArgularVelocity){rotationArgularVelocity = _rotationArgularVelocity;}
    float getRotationArgularVelocity(){return rotationArgularVelocity;}
    
    void setSize(float _size){size = _size;}
    float getSize(){return size;}
    
    void drawObject(const float time) override;
    void updateObject(const float time) override;
    
};


