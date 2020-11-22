//
//  Events.cpp
//  lamp_3D
//
//  Created by Rongqi Bei on 2020/11/21.
//

#include "Events.hpp"

Events::Events(int shape_, int v_){
    
    shape = shape_;
    v = v_;
    pos.set(510, 350, 50);
    moving_dir.set(ofRandom(500, 900), 500);
   
    center_start.set(500, 350);
    moving_dir -= center_start;
    moving_dir.normalize();
    
    w = ofRandom(5, 13);
    h = ofRandom(15, 38);
    
    random_red.set(ofRandom(200, 245), ofRandom(90, 170), ofRandom(90, 150));
    random_blue.set(ofRandom(10, 130), ofRandom(130, 230), ofRandom(180, 220));
    //constant_c.set(250, 250, 210);
    constant_c.set(255, 248, 220);
    cons_red.set(ofRandom(180, 235), ofRandom(30, 80), ofRandom(35, 85), ofRandom(100, 120));
    cons_blue.set(ofRandom(0, 100), ofRandom(130, 200), ofRandom(180, 235), ofRandom(100, 200));
    
    speed_coeff = ofRandom(0.3, 1.5);
    random = ofRandom(100, 300);
}

void Events::update(){
    
    if (shape == 1){
        pos.x += speed_coeff*(ofSignedNoise(moving_dir.x)+0.5);
        pos.y += speed_coeff*ofNoise(moving_dir.y);
        pos.z += 1;
    }
}

void Events::display(){
    update();
    ofNoFill();

    if (v == 1){
        int n = ofGetFrameNum()%random;
        if (random <= 200){
            ofSetColor(random_red.r+ofMap(n, 0, random-1, -20, 40), random_red.g, random_red.b);
        }
        else{
            ofSetColor(random_blue.r, random_blue.g, random_blue.b+ofMap(n, 0, random-1, -20, 50));
        }
    }
    if (v == 2){
        if (random <= 200){
            ofSetColor(cons_red);
        }
        else{
            ofSetColor(cons_blue);
        }
    }
    if (v == 3){
        ofSetColor(constant_c);
    }
    
    if (shape == 1){
        //ofDrawSphere(pos, w);
        //ofDrawBox(pos, w, w, w);
        ofDrawCone(pos, w, h);
    }
}



