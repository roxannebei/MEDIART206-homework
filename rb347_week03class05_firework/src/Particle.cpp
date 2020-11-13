//
//  Particle.cpp
//  rb347_week03class05_firework
//
//  Created by Rongqi Bei on 2020/11/14.
//

#include "Particle.hpp"

Particle::Particle(){
    
    pos = glm::vec2(0,0);
    v = glm::vec2(0,0);
    a = glm::vec2(0,0);
    
    born_time = ofGetElapsedTimef();
}

Particle::Particle(glm::vec2 pos_, glm::vec2 v_, float m_){
    
    pos = pos_;
    v = v_;
    m = m_;
    born_time = ofGetElapsedTimef();
}

void Particle::applyForce(glm::vec2 force){
    a += force/m;
}

void Particle::update(){
    v += a;
    pos += v;
    a *= 0;
}

void Particle::draw(){
    
    float alive_time = ofGetElapsedTimef() - born_time;
    //float alive_time = ofGetElapsedTimef()*2 - born_time;
    float alpha = ofMap(alive_time, 0, 6, 255, 0, true);

    //float hue = fmodf(ofRandom(5)*50+alive_time*50, 255);
    float hue = fmodf(alive_time*50, 255);

    ofColor color = ofColor::fromHsb(hue, 250, 250, alpha);
    ofSetColor(color);

    ofDrawCircle(pos.x, pos.y, m*2);

    
}
