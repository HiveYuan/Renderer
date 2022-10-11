//
//  math.hpp
//  Renderer
//
//  Created by Yuan Liu on 10/11/22.
//

#ifndef math_hpp
#define math_hpp

#include <stdio.h>
#include <iostream>
#include <cmath>

template<class T>
struct Vec2 {
    union {
        struct {T x, y;};
        struct {T u, v;};
        T mRawData[2];
    };
    
    Vec2():x(0),y(0) {}
    Vec2(T _x, T _y):x(_x), y(_y) {}
    
    inline Vec2<T> operator+(float f) const { return Vec2<T>(x + f, y + f);}
    inline Vec2<T> operator-(float f) const { return Vec2<T>(x - f, y - f);}
    inline Vec2<T> operator*(float f) const { return Vec2<T>(x * f, y * f);}
    inline Vec2<T> operator/(float f) const { return Vec2<T>(x / f, y / f);}

    inline Vec2<T> operator+(const Vec2<T>& V) const { return Vec2<T>(x + V.x, y + V.y);}
    inline Vec2<T> operator-(const Vec2<T>& V) const { return Vec2<T>(x - V.x, y - V.y);}
    inline T operator*(const Vec2<T>& V) const { return x * V.x + y * V.y;}
    
    template<class > friend std::ostream& operator<<(std::ostream& s, const Vec2<T>& V);
    
};

template<class T>
struct Vec3 {
    union {
        struct {T x, y, z;};
        struct {T u, v, w;};
        struct {T ivert, iuv, inorm;};
        T mRawData[3];
    };
    
    Vec3():x(0),y(0), z(0) {}
    Vec3(T _x, T _y, T _z):x(_x), y(_y), z(_z) {}
    
    inline Vec3<T> operator+(float f) const { return Vec3<T>(x + f, y + f, z + f);}
    inline Vec3<T> operator-(float f) const { return Vec3<T>(x - f, y - f, z - f);}
    inline Vec3<T> operator*(float f) const { return Vec3<T>(x * f, y * f, z * f);}
    inline Vec3<T> operator/(float f) const { return Vec3<T>(x / f, y / f, z / f);}

    inline Vec3<T> operator+(const Vec3<T>& V) const { return Vec3<T>(x + V.x, y + V.y, z + V.z);}
    inline Vec3<T> operator-(const Vec3<T>& V) const { return Vec3<T>(x - V.x, y - V.y, z - V.z);}
    inline T operator*(const Vec3<T>& V) const { return x * V.x + y * V.y + z * V.z;}
    inline Vec3<T> operator^(const Vec3<T>& V) const { return Vec3<T>(y * V.z - z  * V.y, z * V.x - x * V.z, x * V.y - y * V.x);}
    
    inline float norm2() const { return x*x + y*y + z*z; }
    inline float norm() const { return std::sqrt(this->norm2());}
    inline Vec3<T>& normalize(T l = 1) { (*this) = (*this) * l / this->norm(); return *this; }
    
    template<class > friend std::ostream& operator<<(std::ostream& s, const Vec3<T>& V);
    
};

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template<class T>
std::ostream& operator<<(std::ostream& s, const Vec2<T>& V)
{
    s << "(" << V.x << ", " << V.y << ")";
    return s;
}

template<class T>
std::ostream& operator<<(std::ostream& s, const Vec3<T>& V)
{
    s << "(" << V.x << ", " << V.y << ", " << V.z << ")";
    return s;
}

#endif /* math_hpp */
