//
//  ParticleSystem.cpp
//  rb347_week03class05_firework
//
//  Created by Rongqi Bei on 2020/11/14.
//

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(){
    
    pos = glm::vec2(0, 0);
    start_time = ofGetElapsedTimef();
    
}

ParticleSystem::ParticleSystem(glm::vec2 pos_){
    pos = pos_;
    start_time = ofGetElapsedTimef();
}

void ParticleSystem::applyForce(glm::vec2 force){
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].applyForce(force);
    }
    
}

void ParticleSystem::setup(int max_particles){
    
    for (int i = 0; i< max_particles; i++){
        
        float v_x = ofRandom(-1.5, 1.5);
        glm::vec2 v = glm::vec2(v_x, pow(1.5*1.5-v_x*v_x, 0.5)*ofRandom(-1, 1));
        float m = ofRandom(.02, 1);
        Particle particle = Particle(pos, v, m);
        particles.push_back(particle);
    }

    
}
void ParticleSystem::update(){
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].update();
    }
    
}

void ParticleSystem::draw(){
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
}
