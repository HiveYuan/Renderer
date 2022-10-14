//
//  model.cpp
//  Renderer
//
//  Created by Yuan Liu on 10/11/22.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "model.hpp"

Model::Model(const char* filename) : mVertices(), mFaces()
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
        // vertex definition
        if(!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vec3f v;
            // read x,y,z of vetrtex
            for(int i = 0; i < 3; ++i) iss >> v.mRawData[i];
            mVertices.emplace_back(v);
        }else if(!line.compare(0, 2, "f ")){
            iss >> trash;
            std::vector<int> f;
            int idx_vt, itrash, idx;
            // read vertex index of a face
            while(iss >> idx >> trash >> idx_vt >> trash >> itrash)
                f.emplace_back(--idx);
            mFaces.emplace_back(f);
        }
    }
    std::cout << "#vertices: " << mVertices.size() << ", #faces: " << mFaces.size() << std::endl;
    fin.close();
}

Model::~Model()
{
    
}

int Model::getVertsCnt() const
{
    return (int)mVertices.size();
}

int Model::getFacesCnt() const
{
    return (int)mFaces.size();
}

Vec3f Model::getVertex(int i) const
{
    return mVertices[i];
}

std::vector<int> Model::getFace(int i) const
{
    return mFaces[i];
}
