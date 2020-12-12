//
//  Snow.hpp
//  final_scene_create_try3
//
//  Created by Rongqi Bei on 2020/12/11.
//


#pragma once
#include "ofMain.h"

class Snow{
    
public:
    
    Snow();
    Snow(glm::vec3 pos_, float size_);
    
    void update();
    bool in_box(float bottom);
    void display();
    
    void apply_force(glm::vec3 force);
    void edge_detection(float left, float right, float front, float back);
    void reset(float top);
    //void display_temp();
    
    glm::vec3 pos;
    float size;
    
    glm::vec3 v;
    glm::vec3 a;
    
};
