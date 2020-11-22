#pragma once

#include "ofMain.h"
#include "Light.hpp"
#include "Road.hpp"
#include "SideRoad.hpp"
#include "Events.hpp"
#include "Particle.hpp"
#include "ParticleSystem.hpp"
#include "Meteor.hpp"
#include "Field.hpp"

class Scheduler : public ofThread {
public:
    unsigned long counter = 0;
    
    Scheduler() {
        //timer.setPeriodicEvent(1000000000); // 1 second
        timer.setPeriodicEvent(700000000); // 1 second
        startThread();
    }
private:
    ofTimer timer;
    void threadedFunction() {
        while (isThreadRunning()) {
            timer.waitNext();
            
            counter ++;
        }
    }
};


class ofApp : public ofBaseApp{
 
    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    
    Scheduler mysch;
    //Scheduler mysch1;
    
    vector<ParticleSystem> particleSystems;
    glm::vec2 gravity;
    
    Field meteor_field; 
    vector<Meteor> meteors;
    float damping;
    
    void meteor_update();
        
  
        
};







