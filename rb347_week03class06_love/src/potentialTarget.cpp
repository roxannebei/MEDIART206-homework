//
//  potentialTarget.cpp
//  rb347_week03class06_love
//
//  Created by Rongqi Bei on 2020/11/13.
//

#include "potentialTarget.h"


potentialTarget::potentialTarget(){
    original_pos = glm::vec2(0, 0);
    pos = glm::vec2(0, 0);
    v = glm::vec2(0, 0);
    a = glm::vec2(0, 0);
    m = 5;
    category = 0;
    drag_offset = glm::vec2(0, 0);
}

potentialTarget::potentialTarget(glm::vec2 pos_, int category_){
    category = category_;
    original_pos = pos_;
    pos = original_pos;
    v = glm::vec2(0, 0);
    a = glm::vec2(0, 0);
    m = ofRandom(3, 7);
    drag_offset = glm::vec2(0, 0);
}

void potentialTarget::applyForce(glm::vec2 force){
    a += force/m;
}

void potentialTarget::applyDampingForce(float coeff){
    float speed = glm::length(v);
    if (speed != 0){
        glm::vec2 dir = v/speed;
        applyForce(coeff*-dir);
    }
}

void potentialTarget::applyElasticForce(float coeff){
    glm::vec2 shift = original_pos - pos;
    float length = glm::length(shift);
    if (length != 0){
        applyForce(shift*coeff/length);
    }
}

void potentialTarget::update(){
    v += a;
    pos += v;
    a *= 0;
}


void potentialTarget::draw(){
    
    ofColor normal_color;

    if (category == 1){
        normal_color = ofColor(238, 59, 59, 200);
    }
    if (category == 2){
        normal_color = ofColor(255, 215, 0, 100);
    }
    if (category == 3){
        normal_color = ofColor(34, 139, 34, 200);
    }
    if (category == 4){
        normal_color = ofColor(30, 144, 255, 100);
    }
    if (category == 5){
        normal_color = ofColor(172, 105, 189, 150);
    }
    if (category == 6){
        normal_color = ofColor(255, 255, 255);
    }
    
    if (exist){
        if (dragging) ofSetColor(normal_color.r - 50, normal_color.g - 50, normal_color.b - 50);
        else if (hovering) ofSetColor(normal_color.r, normal_color.g, normal_color.b);
        else ofSetColor(normal_color);
    }
    else{
        ofSetColor(normal_color.r-50, 100);
    }
    ofFill();
    ofDrawCircle(pos.x, pos.y, r);
    ofNoFill();
}

void potentialTarget::clicked(int mouse_x, int mouse_y){
    ofPoint mouse_pos;
    ofPoint target_pos;
    mouse_pos.set(mouse_x, mouse_y);
    target_pos.set(pos.x, pos.y);
    target_pos -= mouse_pos;
    float distance = target_pos.length();
    if (distance < r and exist){
        dragging = true;
        drag_offset.x = pos.x - mouse_x;
        drag_offset.y = pos.y - mouse_y;
    }
}

void potentialTarget::hover(int mouse_x, int mouse_y){
    
    ofPoint mouse_pos;
    ofPoint target_pos;
    mouse_pos.set(mouse_x, mouse_y);
    target_pos.set(pos.x, pos.y);
    target_pos -= mouse_pos;
    float distance = target_pos.length();
    if (distance < r and exist){
        hovering = true;
    }
    else{
        hovering = false;
    }
}

void potentialTarget::stopDragging(){
    dragging = false;
}

void potentialTarget::drag(){
    if (dragging){
        pos.x = ofGetMouseX() + drag_offset.x;
        pos.y = ofGetMouseY() + drag_offset.y;
    }
}

void potentialTarget::check_edges(){
    if (pos.x <= 200+r and exist){
        v.x = -v.x;
        pos.x = 200+r;
    }
    if (pos.x >= 1300-r and exist){
        v.x = -v.x;
        pos.x = 1300-r;
    }
    if (pos.y <= 170 and exist){
        v.y = -v.y;
        pos.y = 170;
    }
    if (pos.y >= 770-r and exist){
        v.y = -v.y;
        pos.y = 770-r;
    }
}
