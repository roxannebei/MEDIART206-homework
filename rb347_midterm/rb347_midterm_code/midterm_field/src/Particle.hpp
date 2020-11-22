//
//  Particle.hpp
//  rb347_week03class05_firework
//
//  Created by Rongqi Bei on 2020/11/14.
//

#pragma once
#include "ofMain.h"

class Particle{

public:
    
    Particle();
    Particle(glm::vec2 pos_, glm::vec2 v_, float m_, int bc_);
    
    void applyForce(glm::vec2 force);
    void update();
    void draw();
    
    glm::vec2 pos, v, a;
    float m;
    float born_time;
    int bc;
    
};



