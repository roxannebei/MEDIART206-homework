//
//  water.cpp
//  rb347_week02class03_winds
//
//  Created by Rongqi Bei on 2020/11/5.
//

#include "waterAndEmitter.h"

void water::setup(float x_, float y_, float w_, float h_, float coeff_){
    x = x_;
    y = y_;
    w = w_;
    h = h_;
    coeff = coeff_;
}

bool water::contains(mover m){
    
    if (m.loc.x > x && m.loc.x < x+w && m.loc.y > y && m.loc.y < y+h) {
        return true;
    }
    else {
        return false;
    }
    
}

ofPoint water::drag(mover m){
    
    float speed = m.v.length();
    float drag_length = coeff * speed * speed;
    
    ofPoint drag_force = m.v;
    drag_force.normalize();
    drag_force *= -drag_length;
    return drag_force;
    
}

void water::display(){
    ofSetColor(135, 206, 250);
    ofDrawRectangle(x, y, w, h);
}


