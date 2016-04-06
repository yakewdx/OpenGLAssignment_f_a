//
//  Object.hpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#pragma once


#include "universal_setting.h"
#include <stdio.h>
#include "PlayGround.h"
#include <vector>

typedef int Name;

enum debug_state {
    PRINT_NONE   =     0,
    PRINT_POS    =     1<<0,
    PRINT_NAME   =     1<<1,
    PRINT_MATRIX =     1<<2,
    PRINT_ALL    =     ~0
};


class Object {
private:
    
    debug_state state;
    void debug_print_pos();
    void debug_print_name();
    void debug_print_matrix();
    void debug_print(int frame = 1);
    
    
protected:
    
    CMatrix mat;                    //当前变换矩阵
    Vec3F pos;                      //相对参考系的位置
    Name name;                      //名字
    int timer;                      //定时器
    Object * ref;                   //参考系
    Object * world;                 //世界
    bool selected;                  //是否被选中
    std::vector<Object *> children; //子节点列表
    
    virtual void drawObject(const float time){}
    virtual void initObject(){}
    
    
public:
    
    void removeChild(Object * child);
    void addChild(Object * child){children.push_back(child);}
    void setIsSelected(bool _selected){selected = _selected;}
    bool isSelected(){return selected;}
    Object * getDescendantByName(Name name);
    
    Vec3F getWorldCoordinate();
    Vec3F getPosition();
    void setPosition(Vec3F);
    void setReference(Object * _ref);
    Object * getReference(){return ref;}
    Name getName(){return name;}
    void setWorld(Object * obj) {world = obj;}

    
    Object();
    ~Object();
    
    void setDebugState(debug_state);
    void update(const float time);
    void updateChildren(const float time);
    
    virtual void updateObject(const float time){}
    
    void draw(const float time, GLenum type);
    void drawChildren(const float time, GLenum type);
    void setMatrix(CMatrix _mat){mat = _mat;};
    CMatrix getMatrix(){return mat;}
    
    
};
