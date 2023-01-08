//
//  model.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/11/22.
//

#include <fstream>
#include <sstream>
#include <iostream>sssi
#include <string>
#include <vector>
#include "model.hpp"

Model::Model(const char* filename)
    : mVertices(), mVtextures(), mFaces()
{
    std::ifstream fin;
    fin.open(filename, std::ifstream::in);
    if(fin.fail())
    {
        std::cout << "Failed to read file " << filename << "!" << std::endl;
        return;
    }
    
    std::string line;
    while(!fin.eof())
    {
        std::getline(fin, line);
        std::istringstream iss(line.c_str());
        char trash;
        // vertices
        if(!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            // read x,y,z of vetrtex
            for(int i = 0; i < 3; ++i) iss >> v.mRawData[i];
            mVertices.emplace_back(v);
        }
        // texture coordinates
        else if(!line.compare(0, 4, "vt  ")){
            iss >> trash >> trash;
            Vec3f vt;
            for(int i = 0; i < 3; ++i) iss >> vt.mRawData[i];
            mVtextures.emplace_back(vt);
        }
        // vertex normals
        else if(!line.compare(0, 4, "vn  ")){
            iss >> trash >> trash;
            Vec3f vn;
            for(int i = 0; i < 3; ++i) iss >> vn.mRawData[i];
            mVnormals.emplace_back(vn);
        }
        // faces
        else if(!line.compare(0, 2, "f ")){
            iss >> trash;
            std::vector<Vec3f> f;
            int idx, idx_vt, idx_vn;
            // read vertex index of a face
            while(iss >> idx >> trash >> idx_vt >> trash >> idx_vn)
                f.emplace_back(Vec3f(--idx, --idx_vt, --idx_vn));
            mFaces.emplace_back(f);
        }
    }
    std::cout << "#vertices: " << mVertices.size() << ", #texture coordinates: " << mVtextures.size() << " #vertex normals: " << mVnormals.size() << ", #faces: " << mFaces.size() << std::endl;
    fin.close();
}

Model::~Model()
{
//    delete mVertices;
//    delete mVtextures;
//    delete mFaces;
}

int Model::getVertsCnt() const
{
    return (int)mVertices.size();
}

int Model::getVtCnt() const
{
    return (int)mVtextures.size();
}

int Model::getVnCnt() const
{
    return (int)mVnormals.size();
}

int Model::getFacesCnt() const
{
    return (int)mFaces.size();
}

Vec3f Model::getVertex(int i) const
{
    return mVertices[i];
}

Vec3f Model::getVtexture(int i) const
{
    return mVtextures[i];
}

Vec3f Model::getVnormal(int i) const
{
    return mVnormals[i];
}

std::vector<Vec3f> Model::getFace(int i) const
{
    return mFaces[i];
}
