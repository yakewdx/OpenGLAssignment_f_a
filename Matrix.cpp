
#ifdef _WIN32
#include "stdafx.h"
#endif

#include "Matrix.h"
#include "Vec3.h"
#include <cstring>
#include <cmath>


CMatrix CMatrix::ZERO() {
    CMatrix mat;
    return mat;
}

CMatrix CMatrix::IDENTITY() {
    CMatrix mat;
    mat.m00 = 1;
    mat.m11 = 1;
    mat.m22 = 1;
    mat.m33 = 1;
    return mat;
}

// setter
void CMatrix:: Set(float *val){
    int i = 0;
    float *f = &m00;
    for (; i < 16; i++) {
        f[i] = val[i];
    }
}

// 设置为单位矩阵
void CMatrix::identity(){
    float *f = (float *)this;
    memset(f, 0, sizeof(float) * 16);
    m00 = 1;
    m11 = 1;
    m22 = 1;
    m33 = 1;
}

// 设置某一行
void CMatrix::SetRow(int i, Vec3F p){
    if (i <= 3) {
        float * f = &m00;
        f[i] = p.x;
        f[4 + i] = p.y;
        f[8 + i] = p.z;
    }
}

// 获取某一行
Vec3F CMatrix::GetRow(int i) {
    if (i <= 3) {
        float * f = &m00;
        return Vec3F(f[i], f[4+i], f[8+i]);
    } else {
        return Vec3F(0,0,0);
    }
}

// 设置某一列
void CMatrix::SetCol(int i, Vec3F p){
    if (i <= 3) {
        float * f = &m00 + i * 4;
        f[0] = p.x;
        f[1] = p.y;
        f[2] = p.z;
    }
}

// 获取某一列
Vec3F CMatrix::GetCol(int i) {
    if (i <= 3) {
        float * f = &m00 + i * 4;
        return Vec3F(f[0], f[1], f[2]);
    } else {
        return Vec3F(0,0,0);
    }

}

// 赋值
CMatrix & CMatrix::operator=(const CMatrix& p){
    float *f1 = &m00;
    const float *f2 = &p.m00;
    
    for (int i = 0; i < 16; i++) {
        f1[i] = f2[i];
    }
    return *this;
}

// 重载操作符 数乘
CMatrix CMatrix::operator *(float d){
    float *f1 = &m00;
    CMatrix mat;
    float *f2 = &mat.m00;
    for (int i = 0; i < 16; i++) {
        f2[i] = f1[i] * d;
    }
    return mat;
}

// 矩阵乘法
CMatrix CMatrix::operator *(const CMatrix &p){
    CMatrix mat;
    float *f1 = &m00, *f3 = &mat.m00;
    const float *f2 = &p.m00;
    // f3[i][j] = SIGMA( f1[i][k] * f2[k][j] )
    // f3[j*4+i] = for k=1:4 --> f1[k*4+i] * f2[j*4+k]
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            f3[j*4+i] = 0;
            for (int k = 0;  k < 4; k++) {
                f3[j*4+i] += f1[k*4+i] * f2[j*4+k];
            }
        }
    }
    return mat;
}

// 矩阵乘以向量
Vec3F CMatrix::operator*(const Vec3F &p){
    Vec3F vec;
    vec.x = p.x * m00 + p.y * m01 + p.z * m02;
    vec.y = p.x * m10 + p.y * m11 + p.z * m12;
    vec.z = p.x * m20 + p.y * m21 + p.z * m22;
    return vec;
}

// 矩阵乘以点
Vec3F CMatrix::MulPoint(const Vec3F &p){
    Vec3F vec;
    vec.x = p.x * m00 + p.y * m01 + p.z * m02 + m03;
    vec.y = p.x * m10 + p.y * m11 + p.z * m12 + m13;
    vec.z = p.x * m20 + p.y * m21 + p.z * m22 + m23;
    return vec;
}

// 转置
void CMatrix::Transpose(){
    *this = getTranspose();
}

// 转置
CMatrix CMatrix::getTranspose() {
    CMatrix mat;
    float *f1 = &m00;
    float *f2 = &mat.m00;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <4; j++) {
            f2[j*4+i] = f1[i*4+j];
        }
    }
    return mat;
}


#define _X_X (axis.x * axis.x)
#define _X_Y (axis.x * axis.y)
#define _X_Z (axis.x * axis.z)
#define _Y_Y (axis.y * axis.y)
#define _Y_Z (axis.y * axis.z)
#define _Z_Z (axis.z * axis.z)
#define _X axis.x
#define _Y axis.y
#define _Z axis.z
#define OMC (1 - cos(theta))
#define COS (cos(theta))
#define SIN (sin(theta))
// 设置为旋转矩阵
void CMatrix::SetRotate(double theta, Vec3F axis){
    identity();
    m00 = _X_X * OMC + COS;         m01 = _X_Y * OMC - _Z * SIN;    m02 = _X_Z * OMC + _Y * SIN;
    m10 = _X_Y * OMC + _Z * SIN;    m11 = _Y_Y * OMC + COS;         m12 = _Y_Z * OMC - _X * SIN;
    m20 = _X_Z * OMC - _Y * SIN;    m21 = _Y_Z * OMC + _X * SIN;    m22 = _Z_Z * OMC + COS;
}

// 设置为平移矩阵
void CMatrix::SetTrans(Vec3F trans){
    identity();
    m03 = trans.x;
    m13 = trans.y;
    m23 = trans.z;
}

// 设置为缩放矩阵
void CMatrix::SetScale(Vec3F p){
    identity();
    m00 = p.x;
    m11 = p.y;
    m22 = p.z;
}



float CMatrix::det() {
    float *f = &m00;
    float res = 0;
    for (int i = 0; i < 4; i++) {
        res += f[i] * cofactor(i, 0);
    }
    return res;
}

// 求逆
float CMatrix::Inverse(){
    float det = this->det();
    if (fabs(det - 0) < 1e-6) {
        return 0;
    } else {
        *this = GetInverse();
        return det;
    }
}

// 获取逆矩阵
CMatrix CMatrix::GetInverse(){
    // 求行列式
    if (fabs(this->det() - 0) < 1e-6) {
        return CMatrix::ZERO();
    } else {
        CMatrix mat;
        float _det = det();
        float * f = &mat.m00;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                f[j*4 + i] = cofactor(j, i)/_det;
            }
        }
        return mat;
    }
}

float CMatrix::cofactor(int i, int j) {
    float * f = &m00;
    int a[3]; // 行
    int b[3]; // 列
    int flag = 0;
    for (int m = 0; m < 4; m++) {
        if (m == i) {
            continue;
        } else {
            a[flag] = m;
            flag++;
        }
        
    }
    flag = 0;
    for (int n = 0; n < 4; n++) {
        if (n == j) {
          continue;
        } else {
            b[flag] = n;
            flag++;
        }
        
    }
    int factor = 1;
    if ((i + j)%2 >0) {
        factor = -1;
    }
    
    // positive
    float c = 0;
    for (int i = 0; i < 3; i++) {
        float tmp = 1;
        for (int j = 0; j < 3; j++) {
            tmp *= f[a[j] + b[(i+j)%3] * 4];
        }
        c +=  tmp;
    }
    
    // negative
    for (int i = 0; i < 3; i++) {
        float tmp = 1;
        for (int j = 0; j < 3; j++) {
            tmp *= f[a[2-j] + b[(i+j)%3] * 4];
        }
        c -=  tmp;
    }
    return factor * c;
}

CMatrix::CMatrix(){
    float *f = (float *)this;
    memset(f, 0, sizeof(float) * 16);
}
CMatrix::~CMatrix(){}

std::ostream & operator << (std::ostream & os, CMatrix mat) {
    os << mat.m00 << " " << mat.m01 << " " << mat.m02 << " " << mat.m03 << std::endl
       << mat.m10 << " " << mat.m11 << " " << mat.m12 << " " << mat.m13 << std::endl
       << mat.m20 << " " << mat.m21 << " " << mat.m22 << " " << mat.m23 << std::endl
    << mat.m30 << " " << mat.m31 << " " << mat.m32 << " " << mat.m33 << std::endl;
    return os;
}

std::istream & operator>>(std::istream &i, CMatrix & mat) {
    i >> mat.m00 >> mat.m01 >> mat.m02 >> mat.m03 >> mat.m10 >> mat.m11 >> mat.m12 >> mat.m13 >>
    mat.m20 >> mat.m21 >> mat.m22 >> mat.m23 >> mat.m30 >> mat.m31 >> mat.m32 >> mat.m33;
    return i;
}