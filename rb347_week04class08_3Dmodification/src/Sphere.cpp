//
//  Sphere.cpp
//  rb347_week04class08_3Dmodification
//
//  Created by Rongqi Bei on 2020/11/23.
//

#include "Sphere.hpp"

Sphere::Sphere(){
    
    pos = glm::vec3(0, 0, 0);
    r = get_radius();
    color = get_color();
}


Sphere::Sphere(glm::vec3 pos_){
    pos = pos_;
    r = get_radius();
    color = get_color();
}

void Sphere::update(){
    
    glm::vec3 speed_change;
    glm::vec3 normalized_v;
    
    normalized_v = v/v.length();
    
    int mod = int(ofGetElapsedTimef())%100;
    if (mod <= 49){
        speed_change = 0.002 * normalized_v;
    }
    if (mod > 49){
        speed_change = -0.002 * normalized_v;
    }
    
    v += speed_change;
    v += a;
    pos += v;
    a *= 0;
    
    r = get_radius();
    color = get_color();
}

ofColor Sphere::get_color(){

    float display_num = min(fmodf(ofGetElapsedTimef()*2, 200) , 200-fmodf(ofGetElapsedTimef()*2, 200)  );
    
    ofColor c;
    c.r = ofMap(display_num, 0, 100, 0, 255);
    c.g = ofMap(display_num, 0, 100, 100, 0);
    c.b = ofMap(display_num, 0, 100, 255, 0);

    return ofColor(c.r, c.g, c.b);
}

float Sphere::get_radius(){
    
    float display_num = min(fmodf(ofGetElapsedTimef()*2, 200) , 200-fmodf(ofGetElapsedTimef()*2, 200)  );
    float r = ofMap(display_num, 0, 99, 80, 15);
  
    return r;
}

void Sphere::draw(){
    
    ofPushStyle();
    ofSetColor(color);
    ofDrawSphere(pos, r);
    ofPopStyle();
}

void Sphere::set_velocity(glm::vec3 velocity_){
    
    v = velocity_;
}

void Sphere::apply_force(glm::vec3 force){
    
    a+= force;
}

void Sphere::wall_detection(float left, float right, float top, float bottom, float front, float back){

    if (pos.x < left + r) {
        pos.x = left + r;
        v.x *= -1.;
    }
    
    if (pos.x > right - r) {
        pos.x = right - r;
        v.x *= -1.;
    }
    
    if (pos.y > top - r) {
        pos.y = top - r;
        v.y *= -1.;
    }
    
    if (pos.y < bottom + r) {
        pos.y = bottom + r;
        v.y *= -1.;
    }
    
    if (pos.z < front + r) {
        pos.z = front + r;
        v.z *= -1.;
    }
    
    if (pos.z > back - r) {
        pos.z = back - r;
        v.z *= -1.;
    }
    
}

void Sphere::collision(Sphere s){
    
    float distance = pow(pow(s.pos.x-pos.x, 2)+pow(s.pos.y-pos.y,2)+pow(s.pos.z-pos.z,2), 0.5);
    
    if (distance <= s.r+r){
        
        ofVec3f v1_x, v1_y, v2_x, v2_y;
        ofVec3f dir;
        float m1 = 5, m2 = 5;
        float x1, x2;
        dir.set(pos.x-s.pos.x, pos.y-s.pos.y, pos.z-s.pos.z);
        dir.normalize();
        x1 = dir.dot(v);
        v1_x = x1 * dir;
        v1_y = v-v1_x;
        
        dir *= -1;
        x2 = dir.dot(s.v);
        v2_x = x2 * dir;
        v2_y = s.v - v2_x;
        
        v = v1_x*(m1-m2)/(m1+m2) + v2_x*(2*m2)/(m1+m2) + v1_y;
        s.v = v1_x*(2*m1)/(m1+m2) + v2_x*(m2-m1)/(m1+m2) + v2_y;
        
        float overlap = r + s.r - distance;
        if (pos.x <= s.pos.x){
            pos.x -= overlap/2;
            s.pos.x += overlap/2;
        }
        else{
            pos.x += overlap/2;
            s.pos.x -= overlap/2;
        }
        
    }
    
}

