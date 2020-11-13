//
//  potentialTarget.hpp
//  rb347_week03class06_love
//
//  Created by Rongqi Bei on 2020/11/13.
//

#pragma once
#include "ofMain.h"

class potentialTarget {
    
public:
    
    potentialTarget();
    potentialTarget(glm::vec2 pos_, int category_);
    
    void applyForce(glm::vec2 force);
    void applyDampingForce(float coeff);
    void applyElasticForce(float coeff);
    void update();
    void draw();
    
    glm::vec2 original_pos, pos, v, a;
    int category;
    float m;
    
    void clicked(int mouse_x, int mouse_y);
    void hover(int mouse_x, int mouse_y);
    void stopDragging();
    void drag();

    ofColor normal_color;
    
    glm::vec2 drag_offset;
    bool dragging = false;
    bool hovering = false;
    
    float r = m*4;
    
    bool exist = true;
    bool change = false;
    
    void check_edges();
    
};
