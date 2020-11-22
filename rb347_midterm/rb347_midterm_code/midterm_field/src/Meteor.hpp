//
//  Meteor.hpp
//  midterm_field
//
//  Created by Rongqi Bei on 2020/11/22.
//

#pragma once
#include "ofMain.h"

class Meteor{
    
    public:
    
    Meteor();
    ~Meteor(){}
    
    Meteor(ofVec3f pos_, ofVec3f v_);
    
    void apply_force (ofVec3f force);
    void apply_damping (float strength);
    void update();
    void display();
    
    ofVec3f pos;
    ofVec3f v;
    ofVec3f a;
    
};
