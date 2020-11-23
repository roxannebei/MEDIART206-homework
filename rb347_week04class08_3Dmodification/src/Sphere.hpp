//
//  Sphere.hpp
//  rb347_week04class08_3Dmodification
//
//  Created by Rongqi Bei on 2020/11/23.
//

#pragma once
#include "ofMain.h"

class Sphere{
    
public:
    
    Sphere();
    Sphere(glm::vec3 pos_);
    
    ofColor get_color();
    float get_radius();
    void update();
    void draw();
    
    void set_velocity(glm::vec3 velocity_);
    void apply_force(glm::vec3 force);
    void wall_detection(float left, float right, float top, float bottom, float front, float back);
    void collision(Sphere s);
    
    glm::vec3 pos;
    glm::vec3 v;
    glm::vec3 a;
    float r;
    ofColor color;
    
};
