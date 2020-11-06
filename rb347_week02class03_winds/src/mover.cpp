//
//  mover.cpp
//  rb347_week02class03_winds
//
//  Created by Rongqi Bei on 2020/11/4.
//

#include "mover.h"

int land_height = 600;


mover::mover(float x, float y, float m, float v_x, float v_y, ofColor c_){
    
    loc.set(x, y);
    mass = m;
    v.set(v_x, v_y);
    a.set(0, 0);
    c = c_;
    
}

void mover::applyForce(ofPoint F){
    
    a += F/mass;
    
}

void mover::update(){
    
    v += a;
    loc += v;
    a *= 0;
    
    
    
}

void mover::display(){
    
//    if (mover_list[i].inLight){
//        ofSetColor(ofRandom(0, 255), ofRandom(0, 255), ofRandom(0, 255));
//    }
//    ofSetColor(0, 127);
    
    ofSetColor(c);
    
    int r = mass*8;
    ofDrawCircle(loc.x, loc.y, r);
    update();
    
}

void mover::checkEdges(){
    int r = mass*8;
    
    if (loc.x <= r){
        v.x = -0.9 * v.x;
        loc.x = r;
    }
    if (loc.x >= ofGetWidth()-r){
        v.x = -0.9 * v.x;
        loc.x = ofGetWidth()-r;
    }
    if (loc.y <= r){
        v.y = -0.9 * v.y;
        loc.y = r;
    }
    if (loc.y >= land_height-r and loc.x>300 and loc.x<1300){
        v.y = -0.9 * v.y;
        loc.y = land_height-r;
    }
    
    if((loc.x<300 or loc.x>1300) and loc.y >= ofGetHeight()-r){
        v.y = 0;
        loc.y = ofGetHeight()-r;
    }
}

void mover::collision(mover anotherMover){
    
    int r = mass*8;
    int anotherMover_r = anotherMover.mass*8;
    
    float dist = sqrt(pow(loc.x-anotherMover.loc.x,2)+pow(loc.y-anotherMover.loc.y,2));
    if (dist <= r + anotherMover_r){
        
        float angle = atan2(abs(anotherMover.loc.y-loc.y), abs(anotherMover.loc.x-loc.x));
        float vx1 = cos(angle)*v.x + sin(angle)*v.y;
        float vy1 = sin(angle)*-v.x + cos(angle)*v.y;
        float vx2 = cos(angle)*anotherMover.v.x + sin(angle)*anotherMover.v.y;
        float vy2 = sin(angle)*-anotherMover.v.x + cos(angle)*anotherMover.v.y;
    
        float vx1final = ((mass - anotherMover.mass)*vx1 + 2*anotherMover.mass*vx2)/(mass + anotherMover.mass);
        float vx2final = ((anotherMover.mass - mass)*vx2 + 2*mass*vx1)/(mass + anotherMover.mass);
        
        v.x = vx1final*cos(angle) - vy1*sin(angle);
        v.y = vx1final*sin(angle) + vy1*cos(angle);
        anotherMover.v.x = cos(angle)*vx2final - sin(angle)*vy2;
        anotherMover.v.y = sin(angle)*vx2final + cos(angle)*vy2;
        
        float overlap = r + anotherMover_r - dist;
        if (loc.x<=anotherMover.loc.x){
            loc.x -= overlap/2;
            anotherMover.loc.x += overlap/2;
        }
        else{
            loc.x += overlap/2;
            anotherMover.loc.x -= overlap/2;
        }
    }
    
}


