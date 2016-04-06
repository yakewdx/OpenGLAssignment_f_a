//
//  Moon.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifndef Moon_hpp
#define Moon_hpp

#include <stdio.h>
#include "CelBody.hpp"

class Moon : public CelBody{
    
public:
    void initObject() override;
    void drawObject() override;
    void updateObject(const float time) override;
};

#endif /* Moon_hpp */
