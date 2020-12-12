//
//  Plane.hpp
//  final_scene_create_try1
//
//  Created by Rongqi Bei on 2020/12/9.
//

#pragma once
#include "ofMain.h"

class Plane : public ofNode {
    
public:
    
    Plane();
    
    void setup(float width, float height, float num_of_col, float num_of_row);
    
    void update_noise();
    void update_color();
    
    void draw();
    
    ofMesh mesh;
    
//    ofParameter<float> noise_amp;
//    ofParameter<float> noise_freq;
//    ofParameter<glm::vec2> noise_scale;
//
//    ofParameter<ofColor> top_color, down_color;
//    ofParameter<float> vertex_radius;
    float noise_amp;
    float noise_freq;
    glm::vec2 noise_scale;
    
    ofColor top_color, down_color;
    float vertex_radius;
    
};


