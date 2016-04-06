//
//  Sun.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#ifndef Sun_hpp
#define Sun_hpp

#include <stdio.h>

#include "CelBody.hpp"

class Sun : public CelBody {
    
public:
    
    void initObject() override;
    void drawObject() override;
    void updateObject(const float time) override;
};


#endif /* Sun_hpp */
