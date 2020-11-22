//
//  Light.cpp
//  lamp_3D
//
//  Created by Rongqi Bei on 2020/11/19.
//

#include "Light.hpp"


Light::Light(ofVec3f pos_, ofVec2f moving_dir_){
    pos = pos_;
    moving_dir = moving_dir_;
    c = 0.0;
}

void Light::update_light(){
    pos.x += 3*moving_dir.x;
    pos.y += 2*moving_dir.y;
    pos.z += 1;
    c += 0.35;
}

void Light::display(){

    update_light();
    
    ofVec2f head_dir;
    head_dir.set(-4, 1);
    head_dir.normalize();
    float top_x = pos.x+(120+c)*head_dir.x;
    float top_y = pos.y-(130+c/2)*head_dir.y;
    float width = 15+c/20;
    
 
    ofSetColor(238, 229, 222);
    ofFill();
    ofBeginShape();
    ofVertex(top_x, top_y+width, pos.z);
    ofVertex(top_x, top_y, pos.z);
    ofVertex(pos.x, pos.y, pos.z);
    ofVertex(pos.x, pos.y+3000, pos.z);
    ofVertex(pos.x-width, pos.y+3000, pos.z);
    ofVertex(pos.x-width, pos.y, pos.z);
    ofVertex(top_x, top_y+width, pos.z);
    ofEndShape();
    ofNoFill();
    
}

void Light::update_light_left(){
    pos.x += 3*moving_dir.x;
    pos.y += 2*moving_dir.y;
    pos.z += 1;
    c += 0.35;
}

void Light::display_left(){
    
    update_light_left();
    
    ofVec2f head_dir;
    head_dir.set(-3, 1);
    head_dir.normalize();
    float top_x = pos.x-(120+c)*head_dir.x;;
    float top_y = pos.y-(140+c/2)*head_dir.y;
    float width = 15+c/20;
    
    ofSetColor(238, 229, 222);
    ofFill();
    ofBeginShape();
    ofVertex(top_x, top_y+width, pos.z);
    ofVertex(top_x, top_y, pos.z);
    ofVertex(pos.x, pos.y, pos.z);
    ofVertex(pos.x, pos.y+3000, pos.z);
    ofVertex(pos.x+width, pos.y+3000, pos.z);
    ofVertex(pos.x+width, pos.y, pos.z);
    ofVertex(top_x, top_y+width, pos.z);
    ofEndShape();
    ofNoFill();
    
}
 



