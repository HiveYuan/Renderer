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
#include "model.hpp"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const int width  = 800;
const int height = 800;


int main(int argc, char** argv) {
    TGAImage image(width, height, TGAImage::RGB);
    
    Model* head = new Model("obj/african_head.obj");
    int nf = head->getFacesCnt();
    
    for(int i = 0; i < nf; ++i)
    {
        std::vector<int> face = head->getFace(i);
        for(int j = 0; j < 3; ++j)
        {
            Vec3 v0 = head->getVertex(face[j % 3]);
            Vec3 v1 = head->getVertex(face[(j + 1) % 3]);
            int x0 = (v0.x + 1.0) * width / 2.0;
            int y0 = (v0.y + 1.0) * height / 2.0;
            int x1 = (v1.x + 1.0) * width / 2.0;
            int y1 = (v1.y + 1.0) * height / 2.0;
            line(x0, y0, x1, y1, image, white);
        }
    }
    
    image.write_tga_file("output.tga");
    delete head;
    return 0;
}
