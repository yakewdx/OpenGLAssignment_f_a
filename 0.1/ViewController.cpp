//
//  ViewController.cpp
//  OpenGLTest
//
//  Created by 王冬晓 on 16/3/29.
//  Copyright © 2016年 王冬晓. All rights reserved.
//

#include "ViewController.hpp"
#include "Object.hpp"

void ViewController::setView(Vec3F origin) {
    view = KIH->handle(0, 0, 0);
    
    Object * _follow = follow;

    // 更新摄像机的世界坐标
    Vec3F p = previous + _follow->getWorldCoordinate();
    
    p = p * -1;

    CMatrix res = CMatrix::IDENTITY();
    res.SetTrans(p);
    res = view * res;
    
    world_origin->setMatrix(res);

    
}

void ViewController::changeView(CMatrix mat) {
    view = mat;
}

void ViewController::setWorldOrigin(Object * obj){
    world_origin = obj;
}


// 保证原视角不变，每次改变跟随对象时记录原来物体的世界坐标
void ViewController::setFollow(Object * obj) {
    
    previous = previous + follow->getWorldCoordinate();
    follow = obj;
    previous = previous - follow->getWorldCoordinate();
    
}

CMatrix naiveKeyboardInputHandler::handle(unsigned char key, int x, int y) {
    switch(key)
    {
        case 'a':
            ex -= 1;
            std::cout << "ex changed -" << std::endl;
            std::cout << ex << std::endl;
            break;
        case 'd':
            ex += 1;
            std::cout << "ex changed +" << std::endl;
            std::cout << ex << std::endl;
            break;
        case 'w':
            ey += 1;
            std::cout << "ey changed" << std::endl;
            std::cout << ey << std::endl;
            break;
        case 's':
            ey -= 1;
            std::cout << "ey changed" << std::endl;
            std::cout << ey << std::endl;
            break;
        case 'z':
            ez += 1;
            std::cout << "ez changed" << std::endl;
            std::cout << ez << std::endl;
            break;
        case 'x':
            ez -= 1;
            std::cout << "ez changed" << std::endl;
            std::cout << ez << std::endl;
            break;
            
        case 'f':
            cx -= 1;
            std::cout << "cx changed" << std::endl;
            std::cout << cx << std::endl;
            break;
        case 'h':
            cx += 1;
            std::cout << "cx changed" << std::endl;
            std::cout << cx << std::endl;
            break;
        case 't':
            cy += 1;
            std::cout << "cy changed" << std::endl;
            std::cout << cy << std::endl;
            break;
        case 'g':
            cy -= 1;
            std::cout << "cy changed" << std::endl;
            std::cout << cy << std::endl;
            break;
        case 'v':
            cz += 1;
            std::cout << "cz changed" << std::endl;
            std::cout << cz << std::endl;
            break;
        case 'b':
            cz -= 1;
            std::cout << "cz changed" << std::endl;
            std::cout << cz << std::endl;
            break;
        case 'j':
            ux -= 1;
            std::cout << "ux changed" << std::endl;
            std::cout << ux << std::endl;
            break;
        case 'l':
            ux += 1;
            std::cout << "ux changed" << std::endl;
            std::cout << ux << std::endl;
            break;
        case 'i':
            uy += 1;
            std::cout << "uy changed" << std::endl;
            std::cout << uy << std::endl;
            break;
        case 'k':
            uy -= 1;
            std::cout << "uy changed" << std::endl;
            std::cout << uy << std::endl;
            break;
        case 'm':
            uz += 1;
            std::cout << "uz changed" << std::endl;
            std::cout << uz << std::endl;
            break;
        case ',':
            uz -= 1;
            std::cout << "uz changed" << std::endl;
            std::cout << uz << std::endl;
            break;
    }
    glPushMatrix();
    glLoadIdentity();

    gluLookAt(ex, ey, ez, cx, cy, cz, 0, 1, 0);
    CMatrix mat;
    glGetFloatv(GL_MODELVIEW, mat);
    glPopMatrix();
    
    return mat;
}