//
//  main.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/10/22.
//

#include <iostream>
#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);


int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);
    image.set(52, 41, red);
    return image.write_tga_file("output.tga");
}
