//
//  Road.cpp
//  midterm_adjust_speed
//
//  Created by Rongqi Bei on 2020/11/14.
//

#include "Road.hpp"

Road::Road(ofVec2f pos_, float current_time_, ofVec2f road_dir_){
    pos.x = pos_.x;
    pos.y = pos_.y;
    current_time = current_time_;
    road_dir = road_dir_;
}

void Road::display(int v){
    
    float time = (ofGetElapsedTimef()-current_time)*2;
    
    
    if (v == 1){
        float x = pos.x + (time - 5.5)*time*3*road_dir.x;
        float y = pos.y + (time - 5.5)*time*3*road_dir.y;
        float w = 3+time*0.9;
        float h = 20+time*time*0.8;
        
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

    if (v == 2){
        float x = pos.x + (time - 3.9)*time*2.5*road_dir.x;
        float y = pos.y + (time - 3.9)*time*2.5*road_dir.y;
        float w = 3+time*0.9;
        float h = 20+time*2*time/3;
        
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
        

    if (v == 3){
        float x = pos.x + (time - 2.8)*time*3.5*road_dir.x;
        float y = pos.y + (time - 2.8)*time*3.5*road_dir.y;
        float w = 4+time;
        float h = 20+time*2*time/3;
        
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
}

void Road::display_sign(int v){
    
    if (v == 1){
        float time = (ofGetElapsedTimef()-current_time)*2;
        
        float x = pos.x + (time-4)*(time-4)*5*road_dir.x;
        float y = pos.y + (time-4)*(time-4)*5*road_dir.y;
        float r = 1.5+time*0.3;
        float h = (time-3.5)*(time-3.5)*2;
        
        ofSetLineWidth(2.5);
        
        ofSetColor(221, 186, 88);
        ofDrawEllipse(x, y, 2*r, r);
        ofDrawRectangle(x-r, y-h, r*2, h);
        
        ofSetColor(244, 214, 81);
        ofFill();
        ofDrawEllipse(x, y, 2*r, r);
        ofDrawRectangle(x-r, y-h, r*2, h);
        ofNoFill();
        
        ofSetColor(237, 212, 139);
        ofFill();
        ofDrawEllipse(x, y-h, 2*r, r);
        ofNoFill();
        
        ofSetColor(196, 176, 90);
        ofFill();
        ofDrawRectangle(x-r, y-h*2/3, 2*r, h/3);
        ofNoFill();
        
        ofSetLineWidth(0.7);
        ofSetColor(221, 186, 88);
        ofDrawEllipse(x, y-h, 2*r, r);
    }
    
    if (v == 2){
        float time = (ofGetElapsedTimef()-current_time)*2;
        
        float x = pos.x + (time-4)*(time-4)*5*road_dir.x;
        float y = pos.y + (time-4)*(time-4)*5*road_dir.y;
        float r = 1.5+time*0.3;
        float h = (time-3.5)*(time-3.5)*2;
        
        ofSetLineWidth(2.5);
        
        ofSetColor(221, 186, 88);
        ofDrawEllipse(x, y, 2*r, r);
        ofDrawRectangle(x-r, y-h, r*2, h);
        
        ofSetColor(244, 214, 81);
        ofFill();
        ofDrawEllipse(x, y, 2*r, r);
        ofDrawRectangle(x-r, y-h, r*2, h);
        ofNoFill();
        
        ofSetColor(237, 212, 139);
        ofFill();
        ofDrawEllipse(x, y-h, 2*r, r);
        ofNoFill();
        
        ofSetColor(196, 176, 90);
        ofFill();
        ofDrawRectangle(x-r, y-h*2/3, 2*r, h/3);
        ofNoFill();
        
        ofSetLineWidth(0.7);
        ofSetColor(221, 186, 88);
        ofDrawEllipse(x, y-h, 2*r, r);
    }
    
    if (v == 3){
    float time = (ofGetElapsedTimef()-current_time)*2;
    
    float x = pos.x + (time-3)*(time-3)*6*road_dir.x;
    float y = pos.y + (time-3)*(time-3)*6*road_dir.y;
    float r = 1.5+time*0.3;
    float h = (time-2)*(time-2)*2;

    ofSetLineWidth(2.5);
    
    ofSetColor(221, 186, 88);
    ofDrawEllipse(x, y, 2*r, r);
    ofDrawRectangle(x-r, y-h, r*2, h);
    
    ofSetColor(244, 214, 81);
    ofFill();
    ofDrawEllipse(x, y, 2*r, r);
    ofDrawRectangle(x-r, y-h, r*2, h);
    ofNoFill();
    
    ofSetColor(237, 212, 139);
    ofFill();
    ofDrawEllipse(x, y-h, 2*r, r);
    ofNoFill();
    
    ofSetColor(196, 176, 90);
    ofFill();
    ofDrawRectangle(x-r, y-h*2/3, 2*r, h/3);
    ofNoFill();
    
    ofSetLineWidth(0.7);
    ofSetColor(221, 186, 88);
    ofDrawEllipse(x, y-h, 2*r, r);
    }
    
    
    
}





