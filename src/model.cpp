//
// Created by Blake on 6/4/2022.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "../include/model.h"

Model::Model(const char *filename) : verts_(), faces_() {
    std::ifstream in;
    in.open(filename, std::ifstream::in);
    if(in.fail()) return;
    std::string line;
    while(!in.eof()){
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if(!line.compare(0,2, "v ")){
            iss >> trash;
            float x,y,z;
            iss >> x >> y >> z;
            Vec3f v(x,y,z);
            verts_.push_back(v);
        }
        else if(!line.compare(0,2,"f ")){
            std::vector<int> f;
            int itrash, idx;
            iss >> trash;
            while(iss >> idx >> trash >> itrash >> trash >> itrash){
                idx--;
                f.push_back(idx);
            }
            faces_.push_back(f);
        }
    }
    std::cerr << "# v# " << verts_.size() << " f# " << faces_.size() << std::endl;
}

int Model::nverts() {
    return (int)verts_.size();
}

int Model::nfaces() {
    return (int)faces_.size();
}

std::vector<int> Model::face(int idx){
    return faces_[idx];
}

Vec3f Model::vert(int index) {
    return verts_[index];
}