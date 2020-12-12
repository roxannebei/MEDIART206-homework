//
//  Flower.hpp
//  final_scene_create_try3
//
//  Created by Rongqi Bei on 2020/12/11.
//

#pragma once
#include "ofMain.h"

class Flower{
    
public:
    
    Flower();
    Flower(glm::vec3 pos_, float size_);
    
    void display(float theata, int time_status, ofColor c_d, ofColor c_n, float count_day);
    
    glm::vec3 pos;
    float size;
    
    float random;
    
    ofColor get_current_color(float current_time, float min_time, float max_time, ofColor c_bgn, ofColor c_end);
    
    
    
};
