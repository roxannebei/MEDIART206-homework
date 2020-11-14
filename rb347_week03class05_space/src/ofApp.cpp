#include "ofApp.h"

float theata;
bool turn_off_repulsion = false;

vector<float> random_x;
vector<float> random_y;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    for (int i = 0;i < 20; i++) {
        star_list.push_back(Star());
    }
    
    for (int i = 0; i < 3; i++){
        planet_list.push_back(Planet());
    }
    
    for (int i = 0; i < 300; i++){
        random_x.push_back(ofRandom(1700));
        random_y.push_back(ofRandom(1200));
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < planet_list.size(); i++){
        planet_list[i].hover(mouseX, mouseY);
    }
    
    
    for (int i = 0; i < star_list.size(); i++){
        ofPoint a_f1 = planet_list[1].attract(star_list[i]);
        ofPoint a_f2 = planet_list[2].attract(star_list[i]);
        star_list[i].applyForce(a_f1);
        star_list[i].applyForce(a_f2);
        star_list[i].update();
        
        if (turn_off_repulsion){
            ofPoint diff_w_1 = planet_list[1].pos - star_list[i].pos;
            float dist = diff_w_1.length();
            if (dist != 0 and dist < 100){
                ofPoint repulsion = diff_w_1/dist;
                star_list[i].applyForce(-0.05*repulsion);
            }
        }
        
    }
    
    theata += PI/90 * 0.25;
    
    planet_list[1].pos.x = ofGetWidth()/2 + 100* cos(theata);
    planet_list[1].pos.y = ofGetHeight()/2 + 100* sin(theata);
    planet_list[2].pos.x = ofGetWidth()/2 + 300* cos(theata+PI/2);
    planet_list[2].pos.y = ofGetHeight()/2 + 300* sin(theata+PI/2);
}


//--------------------------------------------------------------
void ofApp::draw(){
    
    for(int i = 0; i<300; i++){
        ofSetColor(255, sin(0.25*theata*i/TWO_PI)*255);
        ofFill();
        ofDrawCircle(random_x[i], random_y[i], 3);
    }
    
    ofSetHexColor(0xFFFFFF);
    ofDrawBitmapString("Press key r to trun on/off the repulsion that the inner planet has on the objects\nMove the mouse around and click to generate new stars.", 40, 50);
    if (turn_off_repulsion){
        ofFill();
        ofDrawBitmapString("REPULSION OFF", 40, 105);
    }
    else{
        ofFill();
        ofDrawBitmapString("REPULSION ON", 40, 105);
    }
    
    
    for (auto& s: star_list){
        s.display();
    }
    for (auto& p: planet_list){
        p.display();
    }
    
    ofSetHexColor(0xFFFFFF);
    ofNoFill();
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 300);
    ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, 2);
    ofFill();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r'){
        turn_off_repulsion = !turn_off_repulsion;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    for (int i = 0; i < planet_list.size(); i++){
        planet_list[i].drag();
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    for (int i = 0; i < planet_list.size(); i++){
        planet_list[i].clicked(mouseX, mouseY);
    }
    
    star_list.push_back(Star(ofGetMouseX(), ofGetMouseY()));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    for (int i = 0; i < planet_list.size(); i++){
        planet_list[i].stop_dragging();
    }
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
