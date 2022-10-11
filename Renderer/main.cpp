//
//  main.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/10/22.
//

#include <iostream>
#include "tgaimage.h"
#include "geometry.hpp"
#include "math.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


int main(int argc, char** argv) {
//    TGAImage image(100, 100, TGAImage::RGB);
//    line(13, 20, 80, 40, image, white);
//    line(20, 13, 40, 80, image, red);
//    return image.write_tga_file("output.tga");
    
    Vec3f v1(1.2, 3.7, 6.5);
    Vec3f v2(4.6, 5.8, 7.1);
    std::cout << (v1.norm()) << std::endl;
    
    return 0;
}
