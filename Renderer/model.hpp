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
    std::vector<std::vector<int>> mFaces;
public:
    Model(const char* filename);
    ~Model();
    int getVertsCnt() const;
    int getFacesCnt() const;
    Vec3f getVertex(int i) const;
    std::vector<int> getFace(int i) const;
};

#endif /* model_hpp */
