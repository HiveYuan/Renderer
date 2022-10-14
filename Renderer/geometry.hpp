//
//  geometry.hpp
//  Renderer
//
//  Created by Yuan Liu on 10/10/22.
//

#ifndef geometry_hpp
#define geometry_hpp

#include <stdio.h>
//#include <stdlib.h>
#include "math.hpp"
#include "tgaimage.h"

#endif /* geometry_hpp */

void line2D(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color);

void triangleByInterpolate2D(Vec2i v0, Vec2i v1, Vec2i v2, TGAImage& image, TGAColor color);

void triangle2D(Vec3f* vertices, std::vector<float>& zBuffer, TGAImage& image, TGAColor color);

Vec3f barycentric2D(Vec3f *pts, const Vec2i& P);
