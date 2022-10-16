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
const int depth = 255;

Vec3f camera(0, 0, 3);

void testHeadWireFrame();
void testTriangleByInterpolate2D();
void testTriangleByBCCoords2D();
void testHeadMesh();
Vec3f matrixToVec3f(const Matrix& m);
Matrix vec3ToMatrix(const Vec3f& v);
Matrix viewPort(int x, int y, int w, int h);

int main(int argc, char** argv) {
//    Matrix a(4, 4);
//    Matrix b = Matrix::identity(4);
//    std::cout << b;
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
        std::vector<Vec3f> face = head->getFace(i);
        for(int j = 0; j < 3; ++j)
        {
            Vec3 v0 = head->getVertex(face[j % 3].ivert);
            Vec3 v1 = head->getVertex(face[(j + 1) % 3].ivert);
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
    TGAImage image_texture;
    image_texture.read_tga_file("texture/african_head_diffuse.tga");
    image_texture.flip_vertically();
    
    Model* head = new Model("obj/african_head.obj");
    int nf = head->getFacesCnt();
    Vec3f light_dir(0, 0, -1);
    std::vector<float> zBuffer(image_bc.width()*image_bc.height(), std::numeric_limits<float>::min());
    // for each face (triangle)
    for(int i = 0; i < nf; ++i)
    {
        std::vector<Vec3f> face = head->getFace(i);
        Vec3f screenVertices[3];
        Vec3f vertexTexCoords[3];
        Vec3f vertexNormals[3];
        Vec3f worldVertices[3]; // for face culling
        // for each vertex of the face
        Matrix projection = Matrix::identity(4);
        projection[3][2] = -1.0 / camera.z;
        Matrix viewport = viewPort(width / 8.0, height / 8.0, width * 0.75, height * 0.75);
        for(int j = 0; j < 3; ++j)
        {
            Vec3f v = head->getVertex(face[j].ivert);
            worldVertices[j] = v;
            screenVertices[j] =  matrixToVec3f(viewport * projection * vec3ToMatrix(v));
            vertexTexCoords[j] = head->getVtexture(face[j].iuv);
            vertexNormals[j] = head->getVertex(face[j].inorm);
        }
        Vec3f faceNormal = ((worldVertices[2] - worldVertices[0]) ^ (worldVertices[1] - worldVertices[0])).normalize();
        float intensity = faceNormal * light_dir;
        // face culling
        if(intensity > 0)
        {
//            std::cout << intensity << std::endl;
            triangle2D(screenVertices, vertexTexCoords, vertexNormals, light_dir, image_texture, image_bc, zBuffer, intensity);
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

Vec3f matrixToVec3f(const Matrix& m)
{
    assert(m.getnRows() >= 3 && m.getnCols() == 1);
    float z = m.getElement(3, 0);
    return Vec3f(m.getElement(0, 0) / z, m.getElement(1, 0) / z, m.getElement(2, 0) / z);
}

Matrix vec3ToMatrix(const Vec3f& v)
{
    Matrix m(4, 1);
    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1;
    return m;
}

Matrix viewPort(int x, int y, int w, int h)
{
    Matrix m = Matrix::identity(4);
    m[0][3] = x + w / 2.0;
    m[1][3] = y + h / 2.0;
    m[2][3] = depth / 2.0;
    
    m[0][0] *= w / 2.0;
    m[1][1] *= h / 2.0;
    m[2][2] *= depth / 2.0;
    
    return m;
}
