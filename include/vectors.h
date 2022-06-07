//
// Created by Blake on 6/4/2022.
//

#ifndef _VECTORS_H
#define _VECTORS_H

#include <cmath>


template <typename T> struct Vector2D{


    T x,y;

    //default constructor
    inline Vector2D(): x(0), y(0){}
    //parameterized constructor
    inline Vector2D(T _x, T _y): x(_x), y(_y){}
    //vector addition
    inline Vector2D<T> operator+(const Vector2D<T>& v) const{return Vector2D<T>(x + v.x, y+ v.y);}
    //vector subtraction
    inline Vector2D<T> operator-(const Vector2D<T>& v)const {return Vector2D<T>(x - v.x, y + v.y);}
    //vector scaling
    inline Vector2D<T> operator*(const float s) const{return Vector2D<T>(s * x, s * y);}
    //dot product
    inline T operator*(const Vector2D<T>& v) const {return (x * v.x + y * v.y);}
    //insertion operator overload
    template <typename X> friend std::ostream& operator<<(std::ostream& s, Vector2D<X>& v);
};

template <typename T> struct Vector3D{

    T x,y,z;


    //default constructor
    inline Vector3D(): x(0), y(0), z(0){}
    //parameterized constructor
    inline Vector3D(T _x, T _y, T _z): x(_x), y(_y), z(_z){}
    //vector addition
    inline Vector3D<T> operator+(const Vector3D<T>& v) const{return Vector3D<T>(x + v.x, y+ v.y, z + v.z);}
    //vector subtraction
    inline Vector3D<T> operator-(const Vector3D<T>& v)const {return Vector3D<T>(x - v.x, y + v.y, z - v.z);}
    //cross product
    inline Vector3D<T> operator^(const Vector3D<T>& v)const {return Vector3D<T>(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);}
    //vector scaling
    inline Vector3D<T> operator*(const float s) const{return Vector3D<T>(s * x, s * y, s * z);}
    //dot product
    inline T operator*(const Vector3D<T>& v) const {return (x * v.x + y * v.y + z * v.z);}
    //norm of vector
    float norm() const{return std::sqrt(x*x + y*y + z*z);}
    //normalize vector
    inline Vector3D<T> & normalize(T length = 1){*this = (*this) * (length / norm()); return *this;}
    //insertion operator overload
    template <typename X> friend std::ostream& operator<<(std::ostream& s, Vector3D<X>& v);
};

typedef Vector2D<int> Vec2i;
typedef Vector2D<float> Vec2f;
typedef Vector3D<int> Vec3i;
typedef Vector3D<float> Vec3f;

template <typename X>
std::ostream& operator<<(std::ostream& s, Vector2D<X>& v){
    s << "(" << v.x << ", " << v.y << ")\n";
}

template <typename X>
std::ostream & operator<<(std::ostream& s, Vector3D<X>& v){
    s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
}
#endif //_VECTORS_H
