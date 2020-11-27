//
//  Tree.cpp
//  snow scene
//
//  Created by Rongqi Bei on 2020/11/27.
//

#include "Tree.hpp"

Tree::Tree(){
}

Tree::Tree(float pos_x_, float pos_y_, float pos_z_, float h_, float r_){
    
    pos_x = pos_x_;
    pos_y = pos_y_;
    pos_z = pos_z_;
    h = h_;
    r = r_;
    
}

void Tree::display_1(int status){
    
    ofSetColor(205, 133, 63);
    ofFill();
    ofDrawCylinder(pos_x, pos_y+h/2, pos_z, 10, h-10);
    ofNoFill();
    
    if (status >= -6){
        
        float k = ofMap(status, -6, 15, 0, 1.2);
        
        ofPushStyle();
        
        ofSetColor(50, 205, 50);
        ofFill();
        ofPushMatrix();
        ofRotateDeg(180);
        ofDrawCone(-pos_x, -(pos_y+h/2+h*1/3), pos_z, r*k, h*0.9);
        ofPopMatrix();
        
        ofPopStyle();
    }
}

void Tree::display_2(int status){
    
    ofSetColor(205, 133, 63);
    ofFill();
    ofDrawCylinder(pos_x, pos_y+h/2, pos_z, 10, h-10);
    ofNoFill();
    
    if (status >= -8){
        
        float k = ofMap(status, -8, 15, 0.35, 1.2);
        
        ofPushStyle();
        
        ofSetColor(50, 205, 50);
        ofPushMatrix();
        ofRotateDeg(180);
        ofDrawCone(-pos_x, -(pos_y+h/2+h*1/4), pos_z, r*k, h*0.5);
        ofDrawCone(-pos_x, -(pos_y+h/2+h*1/2), pos_z, r*(k-0.2), h*0.5);
        ofDrawCone(-pos_x, -(pos_y+h/2+h*3/4), pos_z, r*(k-0.35), h*0.4);
        ofPopMatrix();
        
        ofPopStyle();
    }
    
}
    
