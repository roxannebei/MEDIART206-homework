#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    
    glm::vec2 pos = glm::vec2(-ofGetWidth()/2, -ofGetHeight()/2);
    ParticleSystem p_system = ParticleSystem(pos);
    particleSystems.push_back(p_system);
    
    for (int i = 0; i < particleSystems.size(); i++){
        particleSystems[i].setup();
    }
    
    gravity = glm::vec2(0, 0.0005);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    while (particleSystems.size() > 3)     // keep the number of particles under a limit
    {
        particleSystems.erase(particleSystems.begin());     // erase the oldest particle
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    for (int i=0; i<particleSystems.size(); i++){
        particleSystems[i].applyForce(gravity);
        particleSystems[i].update();
        particleSystems[i].draw();
    }
    
    if ((int)ofGetElapsedTimef()%6==5){
    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, ofGetHeight()-100))));
    setup();
    }
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
