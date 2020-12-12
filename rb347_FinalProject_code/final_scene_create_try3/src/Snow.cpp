//
//  Snow.cpp
//  final_scene_create_try3
//
//  Created by Rongqi Bei on 2020/12/11.
//

#include "Snow.hpp"

Snow::Snow(){
    
    pos = glm::vec3(0, 0, 0);
    size = 20;
}

Snow::Snow(glm::vec3 pos_, float size_){
    
    pos = pos_;
    size = size_;
}

void Snow::update(){
    
    v += a;
    pos += v;
    a *= 0;
}

void Snow::display(){
    ofPushStyle();
    ofSetColor(255, 255, 255);
    ofFill();
    ofDrawSphere(pos.x, pos.y, pos.z, size);
    ofPopStyle();
}

//void Snow::display_temp(){
//
//}

void Snow::apply_force(glm::vec3 force){
    
    a += force;
}

void Snow::edge_detection(float left, float right, float front, float back){
    
    float r = size;

    if (pos.x < left + r) {
        pos.x = left + r;
        v.x *= -1.;
    }
    
    if (pos.x > right - r) {
        pos.x = right - r;
        v.x *= -1.;
    }
    
//    if (pos.y > top - r) {
//        pos.y = top - r;
//        v.y *= -1.;
//    }
    
//    if (pos.y < bottom + r) {
//        pos.y = bottom + r;
//        v.y *= -1.;
//    }
    
    if (pos.z < front + r) {
        pos.z = front + r;
        v.z *= -1.;
    }
    
    if (pos.z > back - r) {
        pos.z = back - r;
        v.z *= -1.;
    }
    
}

bool Snow::in_box(float bottom){
    
    if (pos.y < bottom){
//        ofPushStyle();
//        ofSetColor(255, 255, 255);
//        ofFill();
//        ofDrawSphere(0, 0, 0, size+100);
//        ofPopStyle();
        return false;
    }
    return true;
    
}

void Snow::reset(float top){ 
    
    pos.y = top;
    v = glm::vec3(0, 0, 0);
    a = glm::vec3(0, 0, 0);
}

