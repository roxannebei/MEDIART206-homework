//
//  Road.cpp
//  rb347_week02class04_actNatural
//
//  Created by Rongqi Bei on 2020/11/6.
//

#include "Road.h"

Road::Road(ofVec2f pos_, float current_time_, ofVec2f road_dir_){
    pos.x = pos_.x;
    pos.y = pos_.y;
    current_time = current_time_;
    road_dir = road_dir_;
}

void Road::display(){
    
    float time = (ofGetElapsedTimef()-current_time)*2;
    
    float x = pos.x + time*50*road_dir.x;
    float y = pos.y + time*50*road_dir.y;
    float w = 7+time*3;
    float h = 10+time*2;
    
    ofSetColor(255);
    ofFill();
    ofBeginShape();
    ofVertex(x-w/2, y);
    ofVertex(x+w/2, y);
    ofVertex(x+5*h/7+w/2, y+h);
    ofVertex(x+5*h/7-w/2, y+h);
    ofVertex(x-w/2, y);
    ofEndShape();
    
}

void Road::display_line(ofVec2f v1, ofVec2f v2, ofColor c){
    
    float time = (ofGetElapsedTimef()-current_time)*2;
    float left_x = pos.x + v1.x*(time+0.5)*50;
    float left_y = pos.y + v1.y*(time+0.5)*50;
    float right_x = pos.x + v2.x*time*50;
    float right_y = pos.y + v2.y*time*50;
    ofSetColor(c);
    ofSetLineWidth(3);
    ofDrawLine(left_x, left_y, right_x, right_y);
}

void Road::display_line1(ofVec2f v1, ofVec2f v2, ofColor c){
    
    float time = (ofGetElapsedTimef()-current_time)*2;
    float left_x = pos.x + v1.x*time*50;
    float left_y = pos.y + v1.y*time*50;
    float right_x = pos.x + v2.x*time*50;
    float right_y = pos.y + v2.y*time*50;
    ofSetColor(c);
    ofSetLineWidth(3);
    ofDrawLine(left_x, left_y, right_x, right_y);
}

