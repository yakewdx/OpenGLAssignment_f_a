#pragma once
/***************************************************
Vector class


****************************************************/
#include<cmath>
#include<iostream> 

class CMatrix;

template <typename T>
class Vec3
{
public:
    friend class CMatrix;
    
	///<summary>default constructor which creates vector(0,0,0).</summary>
	Vec3():x(0),y(0),z(0) {}

	///<summary>constructor</summary>
	Vec3(T _x, T _y, T _z):x(_x),y(_y),z(_z) {}

	///<summary>copy constructor</summary>
	Vec3(const Vec3<T> &v):x(v.x),y(v.y),z(v.z) {}
	
    
    T getX()
	{
		return x;
	}
    
    void setX(T _x)
    {
        x = _x;
    }
    
	T getY()
	{
		return y;
	}
    
    void setY(T _y)
    {
        y = _y;
    }
    
	T getZ()
	{
		return z;
	}
    
    void setZ(T _z)
    {
        z = _z;
    }
	bool isEqual(const Vec3<T> &rh);

	Vec3<T> operator=(const Vec3<T> &rh);

	///<summary>override operator ==</summary>
	template <typename Type>
	friend bool operator==(const Vec3<Type> &lh, const Vec3<Type> &rh);

	template <typename Type>
	friend bool operator!=(const Vec3<Type> &lh, const Vec3<Type> &rh);

	///<summary>friend function that overrides operator +</summary>
	///<param name="lh">left hand</param>
	///<param name="rh">right hand</param>
	template <typename Type>
	friend Vec3<Type> operator+(const Vec3<Type> &lh, const Vec3<Type> &rh);


	template <typename Type>
	friend Vec3<Type> operator-(const Vec3<Type> &lh, const Vec3<Type> &rh);

	// 数乘
	template <typename Type>
	friend Vec3<Type> operator*(const double tn, const Vec3<Type> &v);

	// 数乘
	template <typename Type>
	friend Vec3<Type> operator*(const Vec3<Type> &v, const double tn);

	// 除法
	template <typename Type>
	friend Vec3<Type> operator/(const Vec3<Type> &v, const double tn);

	// 点积
	template <typename Type>
	friend Type innerProduct(const Vec3<Type> &lh, const Vec3<Type> &rh);
	
	// 叉积
	template <typename Type>
	friend Vec3<Type> crossProduct(const Vec3<Type> &lh, const Vec3<Type> &rh);

	template <typename Type>
	friend std::ostream& operator<<(std::ostream& os, const Vec3<Type> &v);

	template <typename Type>
	friend std::istream& operator>>(std::istream& is, Vec3<Type> &v);

	// 获取该向量的单位向量，而不改变其本身
	Vec3<T> getNormalizedVector();

	// 将该向量单位化
	void normalize();

	///<summary>向量投影</summary>
	///<param name="lh">源向量</param>
	///<param name="rh">目标方向</param>
	template <typename Type>
	friend Vec3<Type> project(const Vec3<Type> lh, const Vec3<Type> rh);

	double length() const;

	T addup();

	virtual ~Vec3() {};

private:

	T x, y, z;

};

template <typename T>
std::ostream & operator<<(std::ostream& os, const Vec3<T> &v) {
	os << "x:" << v.x << " y:" << v.y << " z:" << v.z;
	return os;
}

template <typename T>
std::istream & operator>>(std::istream& is, Vec3<T> &v) {
	is >> v.x;
	is >> v.y;
	is >> v.z;
	return is;
}

template<typename T>
bool Vec3<T>::isEqual(const Vec3<T> &rh) {
	Vec3<T> v(*this - rh);
	return abs(v.addup()) < 1e-6;
}


template<typename T>
Vec3<T> operator-(const Vec3<T> &lh, const Vec3<T> &rh) {
	Vec3<T> vec;
	vec.x = lh.x - rh.x;
	vec.y = lh.y - rh.y;
	vec.z = lh.z - rh.z;
	return vec;
}

template<typename T>
Vec3<T> Vec3<T>::operator=(const Vec3<T> &rh) {
	x = rh.x;
	y = rh.y;
	z = rh.z;
	return *this;
}


template <typename T>
Vec3<T> operator+(const Vec3<T> &lh, const Vec3<T> &rh) {
	Vec3<T> vec;
	vec.x = lh.x + rh.x;
	vec.y = lh.y + rh.y;
	vec.z = lh.z + rh.z;
	return vec;
}

template <typename T>
bool operator==(const Vec3<T> &lh, const Vec3<T> &rh) {
	Vec3<T> v(lh - rh);
	return abs(v.addup()) < 1e-6;
}

template <typename T>
bool operator!=(const Vec3<T> &lh, const Vec3<T> &rh) {
	return !(lh == rh);
}

template <typename T>
Vec3<T> operator*(const double tn, const Vec3<T> &v) {
	Vec3<T> vec;
	vec.x = (T)(tn * v.x);
	vec.y = (T)(tn * v.y);
	vec.z = (T)(tn * v.z);
	return vec;
}

template<typename T>
Vec3<T> operator*(const Vec3<T> &v, const double tn) {
	return tn * v;
}

template <typename T>
Vec3<T> operator/(const Vec3<T> &v, const double tn) {
	return v * (1 / tn);
}

template<typename T>
T innerProduct(const Vec3<T> &lh, const Vec3<T> &rh) {
	return lh.x * rh.x + lh.y * rh.y + lh.z * rh.z;
}

template<typename T>
double Vec3<T>::length() const {
	return sqrt(x * x + y * y + z * z);
}

template<typename T>
T Vec3<T>::addup() {
	return x + y + z;
}

template <typename T>
Vec3<T> crossProduct(const Vec3<T> &lh, const Vec3<T> &rh) {
	return Vec3<T>(lh.y * rh.z - lh.z * rh.y, lh.z * rh.x - lh.x * rh.z, lh.x * rh.y - lh.y * rh.x);
}

template <typename T>
Vec3<T> Vec3<T>::getNormalizedVector() {
	double len = length();
	return Vec3<T>((*this) / len);
}

template <typename T>
void Vec3<T>::normalize() {
	*this = *this / length();
}

template <typename T>
Vec3<T> project(const Vec3<T> lh, const Vec3<T> rh) {
	double length = lh.length();
	//Vec3<T> t = innerProduct(lh, rh) * rh;

	return Vec3<T>((innerProduct(lh, rh) * rh) / (length * length));
}


typedef Vec3<int> Vec3I;
typedef Vec3<float> Vec3F;
typedef Vec3<double> Vec3D;
