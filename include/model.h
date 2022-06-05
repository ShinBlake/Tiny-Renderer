//
// Created by Blake on 6/4/2022.
//

#ifndef SIMPLERENDERING_MODEL_H
#define SIMPLERENDERING_MODEL_H

#include <vector>
#include "vectors.h"

class Model {
private:
    std::vector<Vec3f> verts_;
    std::vector<std::vector<int>> faces_;

public:
    Model(const char *filename);
    ~Model() =default;
    int nverts();
    int nfaces();
    Vec3f vert(int index);
    std::vector<int> face(int idx);

};


#endif //SIMPLERENDERING_MODEL_H
