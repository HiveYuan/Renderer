//
//  model.hpp
//  Renderer
//
//  Created by Yuan Liu on 10/11/22.
//

#ifndef model_hpp
#define model_hpp

#include <stdio.h>
#include "math.hpp"

class Model {
private:
    std::vector<Vec3f> mVertices;
    std::vector<Vec3f> mVtextures;
    std::vector<Vec3f> mVnormals;
    std::vector<std::vector<Vec3f>> mFaces;
public:
    Model(const char* filename);
    ~Model();
    int getVertsCnt() const;
    int getVtCnt() const;
    int getVnCnt() const;
    int getFacesCnt() const;
    
    Vec3f getVertex(int i) const;
    Vec3f getVtexture(int i) const;
    Vec3f getVnormal(int i) const;
    std::vector<Vec3f> getFace(int i) const;
};

#endif /* model_hpp */
