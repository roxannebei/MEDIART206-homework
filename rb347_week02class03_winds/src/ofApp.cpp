#include "ofApp.h"

//int num = 1;
int world_height = 600;
int water_height = 650;

int emitter_height = 50;
int push_emitter_w = 80;
int drag_emitter_w = 160;
int push_emitter_x = 600-push_emitter_w/2;
int drag_emitter_x = 1000-drag_emitter_w/2;

bool gravity_on;
bool push_light_on = false;
bool drag_light_on = false;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofBackground(255);
    
    water1.setup(0, water_height, 300, ofGetHeight()-water_height, 0.1);
    water2.setup(1300, water_height, 300, ofGetHeight()-water_height, 0.1);
    
    pushEmitter.setup(push_emitter_x, world_height, push_emitter_w, emitter_height, ofColor(255, 215, 0), ofColor(255, 250, 205));
    dragEmitter.setup(drag_emitter_x, world_height, drag_emitter_w, emitter_height, ofColor(64, 224, 208), ofColor(240, 255, 240));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if ((int)ofRandom(0, 150) == 2){
        mover_color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(150, 200));
        mover *m = new mover (pushEmitter.x+pushEmitter.w/2, world_height, ofRandom(1, 2.5), ofRandom(-2, 2), ofRandom(-15, -5), mover_color);
        mover_list.push_back(*m);
    }
    
    if ((int)ofRandom(0, 150) == 52){
        mover_color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(150, 200));
        mover *m = new mover (dragEmitter.x+dragEmitter.w/2, world_height, ofRandom(1, 2.5), ofRandom(-2, 2), ofRandom(-15, -5), mover_color);
        mover_list.push_back(*m);
    }
    
    
    
    for (int i = 0; i < mover_list.size(); i++){
        
        ofPoint gravity(0, 0.1*mover_list[i].mass);
        
        if ((ofGetSeconds()>10 and ofGetSeconds()<20) or (ofGetSeconds()>30 and ofGetSeconds()<40) or (ofGetSeconds()>50 and ofGetSeconds()<60)){
            mover_list[i].applyForce(gravity);
            gravity_on = true;
        }
        if (ofGetSeconds()<=10 or (ofGetSeconds()>=20 and ofGetSeconds()<= 30) or (ofGetSeconds()>=40 or ofGetSeconds()<= 50)){
            gravity_on = false;
        }
        
        if (water1.contains(mover_list[i]) or water2.contains(mover_list[i])){
            ofPoint drag_force = water1.drag(mover_list[i]);
            mover_list[i].applyForce(drag_force);
        }
        

        
        if (pushEmitter.contains(mover_list[i]) and push_light_on){
            ofPoint push_force = pushEmitter.get_push_force(mover_list[i]);
            mover_list[i].applyForce(push_force);
        }
        
        if (dragEmitter.contains(mover_list[i]) and drag_light_on){
                ofPoint drag_force = dragEmitter.get_drag_force(mover_list[i]);
                mover_list[i].applyForce(drag_force);
        }
            
        
        mover_list[i].update();
        mover_list[i].checkEdges();
        
        for (int j = 0; j < mover_list.size(); j++){
            if (i != j){
                mover_list[i].collision(mover_list[j]);
            }
        }
    }
    
    pushEmitter.drag();
    pushEmitter.hover(ofGetMouseX(), ofGetMouseY());
    dragEmitter.drag();
    dragEmitter.hover(ofGetMouseX(), ofGetMouseY());

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (push_light_on){
        pushEmitter.display_light();
    }
    if (drag_light_on){
        dragEmitter.display_light();
    }
    

    water1.display();
    water2.display();
    
    ofSetColor(50, 90, 100);
    ofDrawRectangle(300, world_height, ofGetWidth()-600, ofGetHeight()-world_height);

    pushEmitter.display(ofColor(205, 173, 0), ofColor(238, 201, 0));
    dragEmitter.display(ofColor(0, 206, 209), ofColor(72, 209, 204));
    
    
    for (int i = 0; i<mover_list.size(); i++) {
        
        mover_list[i].display();
        
    }
    
    ofSetColor(0);
    ofDrawBitmapString("The two emitters pop balls out randomly. You can use keyboard and mouse to interact with the balls!\n\n[Keyboard Using Instruction]\n\"p\" - The yellow emitter generates light that gives balls more energy. Press again to turn it off.\n\"d\" - The green emitter generates light that absorbs energy from balls. Press again to turn it off.\nSPACE - clear all existed balls\n\nYou can use mouse to drag the emitters around to adjust the energy of balls in different area and the initial positions of balls.", 50, 50);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'p'){
        push_light_on = !push_light_on;
    }
    if (key == 'd'){
        drag_light_on = !drag_light_on;
    }
    if (key == ' '){
        mover_list.clear();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    //light_on = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    pushEmitter.drag();
    dragEmitter.drag();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    pushEmitter.clicked(ofGetMouseX(), ofGetMouseY());
    dragEmitter.clicked(ofGetMouseX(), ofGetMouseY());
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    pushEmitter.stop_dragging();
    dragEmitter.stop_dragging();
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
