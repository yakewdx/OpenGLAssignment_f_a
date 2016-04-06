#pragma once

#include "Vec3.h"
#include <iostream>

//class Vec3F;

class CMatrix
{
public:
    
    static CMatrix ZERO();
    static CMatrix IDENTITY();
    
    float m00, m10, m20, m30,
          m01, m11, m21, m31,
          m02, m12, m22, m32,
          m03, m13, m23, m33;
    
    // setter
    void Set(float *val);
    
    // 重载float*
    operator float*(){return &m00;}
    
    // 设置为单位矩阵
    void identity();
    
    // 设置某一行
    void SetRow(int i, Vec3F p);
    
    // 获取某一行
    Vec3F GetRow(int i);
    
    // 设置某一列
    void SetCol(int i, Vec3F p);
    
    // 获取某一列
    Vec3F GetCol(int i);
    
    // 赋值
    CMatrix & operator=(const CMatrix& p);
    
    // 重载操作符 数乘
    CMatrix operator *(float d);
    
    // 矩阵乘法
    CMatrix operator *(const CMatrix &p);
    
    // 矩阵乘以向量
    Vec3F operator*(const Vec3F &p);
    
    // 矩阵乘以点
    Vec3F MulPoint(const Vec3F &p);
    
    // 转置
    void Transpose();
    
    // 转置
    CMatrix getTranspose();
    
    // 设置为旋转矩阵
    void SetRotate(double theta, Vec3F axis);
    
    // 设置为平移矩阵
    void SetTrans(Vec3F trans);
    
    // 设置为缩放矩阵
    void SetScale(Vec3F p);
    
    // 求逆
    float Inverse();
    
    // 求行列式
    float det();
    
    // 代数余子式
    float cofactor(int i, int j);
    // 获取逆矩阵
    CMatrix GetInverse();
    CMatrix();
	~CMatrix();
    
    friend std::istream & operator>>(std::istream &i, CMatrix & mat);
    friend std::ostream & operator << (std::ostream & os, CMatrix mat);
    
};

