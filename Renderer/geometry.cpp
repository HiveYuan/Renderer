//
//  geometry.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/10/22.
//

#include "geometry.hpp"
#include "tgaimage.h"

void line2D(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color)
{
    // steep check
    bool steep = false;
    if(std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    
    // direction check
    if(x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    
    // optimization
    int dx = x1 - x0;
    int dy = std::abs(y1 - y0);
    int derror = dy * 2;
    int error = 0;
    int y = y0;
    
    for(int x = x0; x <= x1; ++x)
    {
        if(steep)
        {
            image.set(y, x, color);
        }else{
            image.set(x, y, color);
        }
        
        error += derror;
        if(error > dx)
        {
            y += (y1 > y0? 1 : -1);
            error -= dx * 2;
        }
    }
}

/* old school method
 * for each line, get left, right bound by interpolation
 * then color the pixel between left and right
 */
void triangleByInterpolate2D(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, TGAColor color)
{
    //sort vertices in ascending order by y coordinates
    if(v0.y > v1.y) std::swap(v0, v1);
    if(v0.y > v2.y) std::swap(v0, v2);
    if(v1.y > v2.y) std::swap(v1, v2);
    
//    line2D(v0.x, v0.y, v1.x, v1.y, image, color);
//    line2D(v2.x, v2.y, v1.x, v1.y, image, color);
//    line2D(v0.x, v0.y, v2.x, v2.y, image, color);
    // horizontal sweepline
    
    // upper half of triangle
    for(int y = v0.y; y < v1.y; ++y)
    {
        // interpolate to get left,right bound
        float t = (y - v0.y) / (float)(std::abs(v1.y - v0.y) == 0? 1 : (v1.y - v0.y)); // in case divided by 0!
        float left = v0.x * (1 - t) + v1.x * t;
        t = (y - v0.y) / (float)(v2.y - v0.y);
        float right = v0.x * (1 - t) + v2.x * t;
        if(left > right) std::swap(left, right);
        
        // coloring pixels in triangle
        for (int x = std::ceil(left); x < right; ++x) {
            image.set(x, y, color);
        }
    }
    
    // lower half of triangle
    for(int y = v1.y; y <= v2.y; ++y)
    {
        // interpolate to get left,right bound
        float t = (y - v1.y) / (float)(std::abs(v2.y - v1.y) == 0? 1 : (v2.y - v1.y)); // in case divided by 0!
        float left = v1.x * (1 - t) + v2.x * t;
        t = (y - v0.y) / (float)(v2.y - v0.y);
        float right = v0.x * (1 - t) + v2.x * t;
        if(left > right) std::swap(left, right);
        
        // coloring pixels in triangle
        for (int x =ceil(left); x < right; ++x) {
            image.set(x, y, color);
        }
    }
}

void triangle2D(Vec3f* vertices, std::vector<float>& zBuffer, TGAImage& image, TGAColor color)
{
    // get bounding box of triangle
    Vec2f bboxmin = Vec2f(image.width() - 1, image.height() - 1);
    Vec2f bboxmax = Vec2f(0.0, 0.0);
    
    for(int i = 0; i < 3; ++i)
    {
        bboxmin.x = std::max(0.0f, std::min(bboxmin.x, vertices[i].x));
        bboxmin.y = std::max(0.0f, std::min(bboxmin.y, vertices[i].y));
        
        bboxmax.x = std::min(float(image.width() - 1), std::max(bboxmax.x, vertices[i].x));
        bboxmax.y = std::min(float(image.height() - 1), std::max(bboxmax.y, vertices[i].y));
    }
    
    // sweep the bounding box
    for(int x = bboxmin.x; x <= bboxmax.x; ++x)
    {
        for(int y = bboxmin.y; y < bboxmax.y; ++y)
        {
            Vec3f bcCoord = barycentric2D(vertices, Vec2i(x, y));
            if(bcCoord.x < 0 || bcCoord.y < 0 || bcCoord.z < 0) continue;
            float curZ = 0;
            for(int i = 0; i < 3; ++i) curZ += bcCoord[i] * vertices[i].z;
            if(curZ > zBuffer[x + y * image.width()])
            {
                zBuffer[x + y * image.width()] = curZ;
                image.set(x, y, color);
            }
        }
    }
}

Vec3f barycentric2D(Vec3f *pts, const Vec2i& P)
{
    Vec3f v = Vec3f(pts[1].x - pts[0].x, pts[2].x - pts[0].x, pts[0].x - P.x) ^ Vec3f(pts[1].y - pts[0].y, pts[2].y - pts[0].y, pts[0].y - P.y);
    
//   // degenerate case: P is on boundary of triagnle
    if(std::abs(v.z) < 1e-6)
        // then return any Vec with at least one negative component
        return Vec3f(-1, -1, -1);
    return Vec3f(1.0 - (v.x + v.y) / v.z, v.x / v.z, v.y / v.z);
}
