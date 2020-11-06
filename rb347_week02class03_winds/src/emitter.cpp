//
//  emitter.cpp
//  rb347_week02class03_winds
//
//  Created by Rongqi Bei on 2020/11/5.
//

#include "waterAndEmitter.h"

int light_height = 525;
int land = 600;

void emitter::setup(float x_, float y_, float w_, float h_, ofColor c1_, ofColor c2_){
    x = x_;
    y = y_;
    w = w_;
    h = h_;
    c1 = c1_;
    c2 = c2_;
}

bool emitter::contains(mover m){
    if (m.loc.x > x and m.loc.x < x+w and m.loc.y < land and m.loc.y > ofGetHeight()-land-light_height){
        return true;
    }
    else{
        return false;
    }
}

void emitter::display(ofColor drag_c, ofColor hover_c){
    
    if (dragging){
        ofSetColor(drag_c);
    }
    else if (hovering){
        ofSetColor(hover_c);
    }
    else{
        ofSetColor(c1);
    }
    
    ofDrawRectangle(x, y, w, h);
}

void emitter::display_light(){
    ofSetColor(c2);
    ofDrawRectangle(x, y-light_height, w, light_height);
}

void emitter::clicked(float cursor_x, float cursor_y){
    
    ofPoint a;
    ofPoint b;
    a.set(cursor_x, cursor_y);
    b.set(x, y);
    b -= a;
    float dist = b.length();
    if (dist < w) {
        dragging = true;
        drag_offset.x = x-cursor_x;
    }
}

void emitter::hover(float cursor_x, float cursor_y){
    ofPoint a;
    ofPoint b;
    a.set(cursor_x, cursor_y);
    b.set(x, y);
    b -= a;
    float dist = b.length();
    if (dist < w) {
        hovering = true;
    }
    else {
        hovering = false;
    }
}

void emitter::stop_dragging() {
    dragging = false;
}


void emitter::drag() {
    if (dragging) {
        x = ofGetMouseX() + drag_offset.x;
    }
}

ofPoint emitter::get_drag_force(mover m){
    float speed = m.v.length();
    float drag_length = 0.1 * speed * speed;
    
    ofPoint drag_force = m.v;
    drag_force.normalize();
    drag_force *= -drag_length;
    return drag_force;
}

ofPoint emitter::get_push_force(mover m){
    float drag_length = 0.2*m.mass;
    
    ofPoint drag_force = m.v;
    drag_force.normalize();
    drag_force *= drag_length;
    return drag_force;
}

