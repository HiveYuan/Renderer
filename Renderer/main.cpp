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

const TGAColor white    = TGAColor(255, 255, 255, 255);
const TGAColor red      = TGAColor(255, 0,   0,   255);
const TGAColor green    = TGAColor(0, 255,   0,   255);
const int width  = 800;
const int height = 800;

void testHeadWireFrame();
void testTriangleByInterpolate2D();
void testTriangleByBCCoords2D();
void testHeadMesh();

int main(int argc, char** argv) {
    testHeadMesh();
    return 0;
}

void testHeadWireFrame()
{
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
            line2D(x0, y0, x1, y1, image, white);
        }
    }

    image.write_tga_file("head_wireframe.tga");
    delete head;
}

void testHeadMesh()
{
    TGAImage image_bc(width, height, TGAImage::RGB);
    TGAImage image_intp(width, height, TGAImage::RGB);
    Model* head = new Model("obj/african_head.obj");
    int nf = head->getFacesCnt();
    Vec3f light_dir(0, 0, -1);
    std::vector<float> zBuffer(image_bc.width()*image_bc.height(), std::numeric_limits<float>::min());
    
    for(int i = 0; i < nf; ++i)
    {
        std::vector<int> face = head->getFace(i);
        Vec3f screenVertices[3];
        Vec3f worldVertices[3];
        for(int j = 0; j < 3; ++j)
        {
            Vec3f v = head->getVertex(face[j]);
            worldVertices[j] = v;
            screenVertices[j] = Vec3f((v.x + 1.0) * width / 2.0, (v.y + 1.0) * height / 2.0, (v.z + 1.0) * width / 2.0);
        }
        Vec3f normal = ((worldVertices[2] - worldVertices[0]) ^ (worldVertices[1] - worldVertices[0])).normalize();
        float intensity = normal * light_dir;
        // face culling
        if(intensity > 0)
        {
            TGAColor color(intensity * 255, intensity * 255, intensity * 255);
            triangle2D(screenVertices, zBuffer, image_bc, color);
        }
    }
    image_bc.write_tga_file("head_mesh_bc_zbuffer.tga");
    delete head;
}

void testTriangleByInterpolate2D()
{
    TGAImage image(width, height, TGAImage::RGB);
    
    Vec2i t0[3] = {Vec2i(10, 70),   Vec2i(50, 160),  Vec2i(70, 80)};
    Vec2i t1[3] = {Vec2i(180, 50),  Vec2i(150, 1),   Vec2i(70, 180)};
    Vec2i t2[3] = {Vec2i(180, 150), Vec2i(120, 160), Vec2i(130, 180)};
    triangleByInterpolate2D(t0[0], t0[1], t0[2], image, red);
    triangleByInterpolate2D(t1[0], t1[1], t1[2], image, white);
    triangleByInterpolate2D(t2[0], t2[1], t2[2], image, green);
    image.write_tga_file("trianglesByInterPolate2D.tga");
}

