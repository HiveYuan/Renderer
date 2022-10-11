//
//  geometry.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/10/22.
//

#include "geometry.hpp"
#include "tgaimage.h"

void line(int x0, int y0, int x1, int y1, TGAImage& image, const TGAColor& color)
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
