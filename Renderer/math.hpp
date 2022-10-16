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
#include <vector>
#include <cassert>

template<class T>
struct Vec2 {
    union {
        struct {T x, y;};
        struct {T u, v;};
        T mRawData[2];
    };
    
    Vec2():x(0),y(0) {}
    Vec2(T _x, T _y):x(_x), y(_y) {}
    template <class u> Vec2<T>(const Vec2<u> &v);
    
    Vec2<T>& operator=(const Vec2<T>& v) {
        if(this != &v)
        {
            this->x = v.x;
            this->y = v.y;
        }
        return *this;
    }
    inline Vec2<T> operator+(float f) const { return Vec2<T>(x + f, y + f);}
    inline Vec2<T> operator-(float f) const { return Vec2<T>(x - f, y - f);}
    inline Vec2<T> operator*(float f) const { return Vec2<T>(x * f, y * f);}
    inline Vec2<T> operator/(float f) const { return Vec2<T>(x / f, y / f);}
    inline T operator[](int i) const { return mRawData[i]; }

    inline Vec2<T> operator+(const Vec2<T>& V) const { return Vec2<T>(x + V.x, y + V.y);}
    inline Vec2<T> operator-(const Vec2<T>& V) const { return Vec2<T>(x - V.x, y - V.y);}
    inline T operator*(const Vec2<T>& V) const { return x * V.x + y * V.y;}
    inline T dot(const Vec2<T>& V) const { return (*this) * V; }
    
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
    
    Vec3():x(T()),y(T()), z(T()) {}
    Vec3(T _x, T _y, T _z):x(_x), y(_y), z(_z) {}
    template <class u> Vec3<T>(const Vec3<u> &v);
    
    Vec3<T>& operator=(const Vec3<T>& v) {
        if(this != &v)
        {
            this->x = v.x;
            this->y = v.y;
            this->z = v.z;
        }
        return *this;
    }
    
    inline Vec3<T> operator+(float f) const { return Vec3<T>(x + f, y + f, z + f);}
    inline Vec3<T> operator-(float f) const { return Vec3<T>(x - f, y - f, z - f);}
    inline Vec3<T> operator*(float f) const { return Vec3<T>(x * f, y * f, z * f);}
    inline Vec3<T> operator/(float f) const { return Vec3<T>(x / f, y / f, z / f);}

    inline Vec3<T> operator+(const Vec3<T>& V) const { return Vec3<T>(x + V.x, y + V.y, z + V.z);}
    inline Vec3<T> operator-(const Vec3<T>& V) const { return Vec3<T>(x - V.x, y - V.y, z - V.z);}
    inline T operator*(const Vec3<T>& V) const { return x * V.x + y * V.y + z * V.z;}
    inline Vec3<T> operator^(const Vec3<T>& V) const { return Vec3<T>(y * V.z - z  * V.y, z * V.x - x * V.z, x * V.y - y * V.x);}
    inline T operator[](int i) const { return mRawData[i]; }
    
    inline T dot(const Vec3<T>& V) const { return (*this) * V; }
    inline Vec3<T> cross(const Vec3<T> V) const { return (*this) ^ V; }
    
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

const int DEFAULT_DIMENSION = 4;

class Matrix {
private:
    std::vector<std::vector<float>> mElements;
    int mRows, mCols;
public:
    Matrix(int r = DEFAULT_DIMENSION, int c = DEFAULT_DIMENSION);
    ~Matrix();
    
    inline int getnRows() const { return mRows; };
    inline int getnCols() const { return mCols; };
    
    inline float getElement(int r, int c) const { return mElements[r][c]; }
    
    static Matrix identity(int d = DEFAULT_DIMENSION);
    
    std::vector<float>& operator[](const int i) { return mElements[i]; };
    Matrix operator*(const Matrix& b);
//    template<typename T> Matrix operator*(const Vec3<T> v);
    Matrix transpose();
    Matrix inverse();
    
    friend std::ostream& operator<<(std::ostream& s, const Matrix& m);
};

#endif /* math_hpp */
