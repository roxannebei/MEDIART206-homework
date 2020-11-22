//
//  Meteor.cpp
//  midterm_field
//
//  Created by Rongqi Bei on 2020/11/22.
//

#include "Meteor.hpp"

Meteor::Meteor(){}

Meteor::Meteor(ofVec3f pos_, ofVec3f v_){
    
    pos = pos_;
    v = v_;
}

void Meteor::apply_force(ofVec3f force){
    
    a += force;
}

void Meteor::apply_damping(float strength){
    
    a -= v.getNormalized() * strength;
}

void Meteor::update(){
    
    v += a;
    pos += v;
    a *= 0;
}

void Meteor::display(){
    
    if (pos.y < 330){
    ofSetColor(255);
    ofFill();
    ofDrawCircle(pos, 1.5);
    ofNoFill();
    }
    
}
