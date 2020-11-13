#include "ofApp.h"


// 1100*600 in 1500*900
float frame_w = 1100;
float frame_h = 600;
glm::vec2 frame = glm::vec2(200, 170);
int num_of_potential = 18;
bool meet_love = false;
bool change_background = false;
bool one = false;
bool two = false;
bool three = false;
bool four = false;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofBackground(255, 245, 238);
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    for (int i = 0; i < num_of_potential; i++){
        float pos_x = ofRandom(frame.x+50, frame.x + frame_w - 50);
        float pos_y = ofRandom(frame.y+50, frame.y + frame_h - 50);
        
        int z;
        if (i < num_of_potential-2){
            z = i%4+1;
        }
        else if (i == num_of_potential-2){
            z = 6;
        }
        else{
            z = 5;
        }
        potentialTarget pt(glm::vec2(pos_x, pos_y), z);
        targets.push_back(pt);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!meet_love){
    glm::vec2 finder_pos = targets[num_of_potential-1].pos;
    int current_category = targets[num_of_potential-1].category;
    
    for (int i = 0; i < num_of_potential; i++){
        targets[i].drag();
        targets[i].hover(mouseX, mouseY);
        
        if ((targets[i].pos.x < frame.x or targets[i].pos.x > frame.x + frame_w or targets[i].pos.y < frame.y or targets[i].pos.y > frame.y + frame_h) and targets[i].hovering and i != num_of_potential-1){
            targets[i].exist = false;
        }
        targets[i].check_edges();
    }
    
    for (int i = 0; i < targets.size()-2; i++){
        if (targets[i].exist){
        glm::vec2 difference = finder_pos - targets[i].pos;
        float distance = glm::length(difference);
        glm::vec2 norm = difference/distance;
        
        if (current_category == targets[i].category){
            if (distance < 200){
                targets[i].applyForce(-1.5*norm);
            }
            if (distance < 400){
                targets[i].applyForce(1.5*norm);
            }
        }
        
        if (current_category != targets[i].category){
            if (distance < 250){
                targets[i].applyForce(-norm);
            }
            
            else if (distance < 300){
                targets[i].applyForce(norm);
            }
        }
       
        targets[i].applyDampingForce(0.3);
        targets[i].applyElasticForce(0.5);
        targets[i].update();
    }
    }
    
    if (!meet_love){
        glm::vec2 attraction_f = finder_pos;
        attraction_f -= targets[num_of_potential-2].pos;
        float d = attraction_f.length();
        d = ofClamp(d, 5, 20);
        attraction_f/= attraction_f.length();
        float scalar = 0.004*targets[num_of_potential-2].m * targets[num_of_potential-1].m/(d*d);
        attraction_f *= scalar;
        targets[num_of_potential-2].applyForce(attraction_f);
        targets[num_of_potential-2].update();
    }
    }
    if (meet_love){
        glm::vec2 gravity1(0, 2*targets[num_of_potential-1].m);
        glm::vec2 gravity2(0, 2*targets[num_of_potential-2].m);
        targets[num_of_potential-1].applyForce(gravity1);
        targets[num_of_potential-1].check_edges();
        targets[num_of_potential-2].check_edges();
        targets[num_of_potential-1].update();
        targets[num_of_potential-2].applyForce(gravity2);
        targets[num_of_potential-2].update();
        glm::vec2 attraction_force = targets[num_of_potential-1].pos;
        attraction_force -= targets[num_of_potential-2].pos;
        float distance = glm::length(attraction_force);
        glm::vec2 norm = attraction_force/distance;
        targets[num_of_potential-1].applyForce(norm);
        targets[num_of_potential-2].applyForce(-norm);
       
        
        
    
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    ofSetColor(255, 255, 255);
    if (change_background or meet_love){
        ofSetColor(238, 203, 173);
    }
    ofFill();
    ofDrawRectangle(frame.x, frame.y, frame_w, frame_h);
    ofNoFill();
    
    if (!meet_love){
    glm::vec2 finder_pos = targets[num_of_potential-1].pos;
    

    for (int i = 0; i<targets.size(); i++){
        targets[i].draw();
        
//        glm::vec2 difference = finder_pos - targets[i].pos;
//        float distance = glm::length(difference);
//        if ( distance < 400 and targets[num_of_potential-1].dragging and targets[i].exist){
//            ofSetColor(ofColor(255, 140, 105));
//            ofDrawLine(targets[i].pos.x, targets[i].pos.y, targets[num_of_potential-1].pos.x, targets[num_of_potential-1].pos.y);
//        }
    }
    }
    if (meet_love){
        targets[num_of_potential-2].draw();
        targets[num_of_potential-1].draw();
    }
    ofSetColor(0);
    ofDrawBitmapString("FIND OUT WHAT IS LOVE", 700, 50);
    ofDrawBitmapString("Drag the purple ball around to find love for it.", 600, 70);
    ofDrawBitmapString("You can press the number 1-4 to get some Hints!", 50, 60);
    if (one){
        ofDrawBitmapString("1. You can change the color of the purple ball so that it will look similar to the rest of the \"potential\" lovers.\n   key r for red; key y for yellow; key g for green; key b for blue.", 50, 90);
    }
    if (two){
        ofDrawBitmapString("2. You can drag some of the \"potential\" lovers out of the white block.", 50, 120);
    }
    if (three){
        ofDrawBitmapString("3. Try to change the color of the block by pressing key c, what can you see?", 50, 135);
    }
    if (four){
        ofDrawBitmapString("4. If you think that you have already found what LOVE is, press the space button to check your result.", 50, 150);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == 'r'){
        targets[num_of_potential-1].category = 1;
    }
    if (key == 'y'){
        targets[num_of_potential-1].category = 2;
    }
    if (key == 'g'){
        targets[num_of_potential-1].category = 3;
    }
    if (key == 'b'){
        targets[num_of_potential-1].category = 4;
    }
    if (key == 'z'){
        targets[num_of_potential-1].category = 5;
    }
    if (key == 'c'){
        change_background = true;
    }
    if (key == ' '){
        meet_love = true;
    }
    if (key == '1'){
        one = true;
    }
    if (key == '2'){
        two = true;
    }
    if (key == '3'){
        three = true;
    }
    if (key == '4'){
        four = true;
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
    
    for (int i = 0; i < num_of_potential; i++){
        targets[i].drag();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    for (int i = 0; i < num_of_potential; i++){
        targets[i].clicked(mouseX, mouseY);
    }
    
   
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    for (int i = 0; i < num_of_potential; i++){
        targets[i].stopDragging();
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
