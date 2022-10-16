//
//  math.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/11/22.
//

#include "math.hpp"

template<> template<>
Vec2<float>::Vec2(const Vec2<int>& v) : x(v.x), y(v.y) {}

template<> template<>
Vec2<int>::Vec2(const Vec2<float>& v) : x(int(v.x + .5)), y(int(v.y + .5)) {}

template<> template<>
Vec3<float>::Vec3(const Vec3<int>& v) : x(v.x), y(v.y), z(v.z) {}

template<> template<>
Vec3<int>::Vec3(const Vec3<float>& v) : x(int(v.x + .5)), y(int(v.y + .5)), z(int(v.z + .5)) {}

Matrix::Matrix(int r, int c)
    :mRows(r), mCols(c), mElements(std::vector<std::vector<float>>(r, std::vector<float>(c, 0.f)))
{
    
}

Matrix::~Matrix()
{
    
}

Matrix Matrix::identity(int d)
{
    Matrix id(d, d);
    for(int i = 0; i < d; ++i)
        id[i][i] = 1;
    return id;
}

Matrix Matrix::operator*(const Matrix& b)
{
    assert(this->mCols == b.getnRows());
    int m = this->mRows, n = b.getnCols(), p = this->mCols;
    Matrix ans(m, n);
    for(int i = 0; i < m; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            for(int k = 0; k < p; ++k)
            {
                ans[i][j] += (*this)[i][k] * b.mElements[k][j];
            }
        }
    }
    return ans;
}

//template<typename T>
//Matrix Matrix::operator*(const Vec3<T> v)
//{
//    assert(this->mCols == 3);
//    for(int i = 0; i < mRows; ++i)
//    {
//        for(int j = 0; j < mCols; ++j)
//        {
//            
//        }
//    }
//}

Matrix Matrix::transpose()
{
    Matrix ans(mCols, mRows);
    for(int i = 0; i < mCols; ++i)
    {
        for(int j = 0; j < mRows; ++j)
        {
            ans[i][j] = (*this)[j][i];
        }
    }
    return ans;
}

Matrix Matrix::inverse()
{
    assert(false);
    return (*this);
}

std::ostream& operator<<(std::ostream& s, const Matrix& m)
{
    for(std::vector<float> row : m.mElements)
    {
        for(float& num : row)
        {
            s << num << '\t';
        }
        s << std::endl;
    }
    return s;
}
