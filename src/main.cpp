//
// Created by Blake on 6/2/2022.
//

#include <cmath>
#include <vector>
#include "../include/tgaimage.h"
#include "../include/vectors.h"
#include "../include/model.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
const TGAColor green = TGAColor(0 , 255 , 0, 255);
Model *model = nullptr;
const int width = 800;
const int height = 800;


//Using Barycentric Coordinates
//
//Vec3f barycentric(Vec2i *pts, Vec2i P) {
//    Vec3f u = Vec3f(pts[2][0]-pts[0][0], pts[1][0]-pts[0][0], pts[0][0]-P[0])^Vec3f(pts[2][1]-pts[0][1], pts[1][1]-pts[0][1], pts[0][1]-P[1]);
//    /* `pts` and `P` has integer value as coordinates
//       so `abs(u[2])` < 1 means `u[2]` is 0, that means
//       triangle is degenerate, in this case return something with negative coordinates */
//    if (std::abs(u.z)<1) return Vec3f(-1,1,1);
//    return Vec3f(1.f-(u.x+u.y)/u.z, u.y/u.z, u.x/u.z);
//}
//
//void triangle(Vec2i *pts, TGAImage &image, TGAColor color) {
//    Vec2i bboxmin(image.get_width()-1,  image.get_height()-1);
//    Vec2i bboxmax(0, 0);
//    Vec2i clamp(image.get_width()-1, image.get_height()-1);
//    for (int i=0; i<3; i++) {
//        bboxmin.x = std::max(0, std::min(bboxmin.x, pts[i].x));
//        bboxmin.y = std::max(0, std::min(bboxmin.y, pts[i].y));
//
//        bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, pts[i].x));
//        bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, pts[i].y));
//    }
//    Vec2i P;
//    for (P.x=bboxmin.x; P.x<=bboxmax.x; P.x++) {
//        for (P.y=bboxmin.y; P.y<=bboxmax.y; P.y++) {
//            Vec3f bc_screen  = barycentric(pts, P);
//            if (bc_screen.x<0 || bc_screen.y<0 || bc_screen.z<0) continue;
//            image.set(P.x, P.y, color);
//        }
//    }
//}

void line(Vec2i v1, Vec2i v2, TGAImage &image, TGAColor color){

    int x0 = v1.x;
    int y0 = v1.y;
    int x1 = v2.x;
    int y1 = v2.y;

    bool steep = false;
    if(std::abs(y1 - y0) > std::abs(x1 - x0)){
      std::swap(x0, y0);
      std::swap(x1, y1);
      steep = true;
    }

    if(x0 > x1){
        std::swap(x0, x1);
        std::swap(y0,y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror = std::abs(dy) * 2;
    int error = 0;
    int y = y0;

    if(steep){
        for(int x = x0; x <= x1; ++x){
            image.set(y,x,color);
            error += derror;
            if(error > dx){
                y += (y1>y0 ? 1 : -1);
                error -= dx * 2;
            }
        }
    }
    else{
        for(int x = x0; x <= x1; ++x){
            image.set(x,y,color);
            error += derror;
            if(error > dx){
                y += (y1 > y0 ? 1 : -1);
                error -= dx * 2;
            }
        }
    }

}

void triangle(Vec2i v1, Vec2i v2, Vec2i v3, TGAImage& image, TGAColor color){
    if(v2.y > v1.y) std::swap(v1,v2);
    if(v3.y > v1.y) std::swap(v1,v3);
    if(v3.y > v2.y) std::swap(v2,v3);

    float totalHeight = v1.y - v3.y;
    float segmentHeight = v2.y - v3.y + 1;

    for(int y = v3.y; y <= v2.y; ++y){
        float leftRatio = (y - v3.y) / totalHeight;
        float rightRatio = (y - v3.y) / segmentHeight;

        Vec2i left = v3 + (v1 - v3) * leftRatio;
        Vec2i right = v3 + (v2 - v3) * rightRatio;

        if(left.x > right.x) std::swap(left, right);

        for(int x = left.x; x <= right.x; ++x){
            image.set(x,y,color);
        }
    }

    segmentHeight = v1.y - v2.y + 1;
    for(int y = v1.y; y >= v2.y; --y){
        float legRatio = (v1.y - y) / segmentHeight;
        float hypRatio = (v1.y - y) / totalHeight;

        Vec2i leg = v1 - (v1 - v2) * legRatio;
        Vec2i hyp = v1 - (v1 - v3) * hypRatio;

        if(leg.x > hyp.x) std::swap(leg, hyp);

        for(int x = leg.x; x <= hyp.x; ++x){
            image.set(x,y,color);
        }
    }


}

int main(int argc, char** argv) {


    if(2==argc){
        model = new Model(argv[1]);
    }
    else{
        model = new Model("../obj/african_head.obj");
    }
    TGAImage image(width,height, TGAImage::RGB);
    Vec3f light_dir(0,0,-1); // define light_dir

    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec2i screen_coords[3];
        Vec3f world_coords[3];
        for (int j=0; j<3; j++) {
            Vec3f v = model->vert(face[j]);
            screen_coords[j] = Vec2i((v.x+1.)*width/2., (v.y+1.)*height/2.);
            world_coords[j]  = v;
        }
        Vec3f n = (world_coords[2]-world_coords[0])^(world_coords[1]-world_coords[0]);
        n.normalize();
        float intensity = n*light_dir;
        if (intensity>0) {
            triangle(screen_coords[0], screen_coords[1], screen_coords[2], image, TGAColor(intensity*255, intensity*255, intensity*255, 255));
        }
    }
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}



