//
//  ParticleSystem.hpp
//  rb347_week03class05_firework
//
//  Created by Rongqi Bei on 2020/11/14.
//

#pragma once
#include "ofMain.h"
#include "Particle.hpp"

class ParticleSystem {
    
public:
    
    ParticleSystem();
    ParticleSystem(glm::vec2 pos_);
    
    void applyForce(glm::vec2 force);
    void setup(int max_particles = 1000);
    void update();
    
    void draw();
    
    glm::vec2 pos;
    
    vector<Particle> particles;
    float start_time;
};
