#include "ofApp.h"

/* colors */

ofColor outer_face = ofColor(255, 255, 255);
ofColor inner_face = ofColor(255, 255, 255);
ofColor neck = ofColor(255, 255, 255);
ofColor body = ofColor(255, 255, 255);
ofColor blush = ofColor(255, 255, 255);

ofVec2f left_eye_center;
ofVec2f right_eye_center;
ofVec2f left_eye_pos;
ofVec2f right_eye_pos;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(100, 149, 237);
    
    //ofBackground(255);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofSetCircleResolution(200);
    
    left_eye_center.set(585, 275);
    left_eye_pos.set(585, 275);
    right_eye_center.set(815, 275);
    right_eye_pos.set(815, 275);
    
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofVec2f mouse;
    mouse.set(ofGetMouseX(), ofGetMouseY());
    
    float pct = 0.05;
    
    left_eye_pos = left_eye_pos*(1-pct) + mouse*pct;
    right_eye_pos = right_eye_pos*(1-pct) + mouse*pct;

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofNoFill();
    
    float hue = min(fmodf(ofGetElapsedTimef()*50, 510), 510-fmodf(ofGetElapsedTimef()*50, 510));
    float hue1 = fmodf(ofGetElapsedTimef()*50, 255);
    float hue2 = min(fmodf(ofGetElapsedTimef()*100, 510), 510-fmodf(ofGetElapsedTimef()*100, 510));
    
    /* -----------------------------------  coloring  ---------------- */
    
    /* background */
    
    ofSetColor(120+hue1, ofMap(hue1, 0, 255, 215, 255), 0);
    ofFill();
    ofDrawTriangle(75, 400, 0, 150, 0, 400);
    ofDrawTriangle(1400-75, 400, 1400, 150, 1400, 400);
    ofBeginShape();
    ofVertex(150, 400);
    ofVertex(350, 400);
    ofVertex(150, 900);
    ofVertex(-50, 900);
    ofVertex(150, 400);
    ofEndShape();
    ofBeginShape();
    ofVertex(500, 400);
    ofVertex(650, 400);
    ofVertex(500, 900);
    ofVertex(350, 900);
    ofVertex(500, 400);
    ofEndShape();
    ofBeginShape();
    ofVertex(750, 400);
    ofVertex(900, 400);
    ofVertex(1050, 900);
    ofVertex(900, 900);
    ofVertex(750, 400);
    ofEndShape();
    ofBeginShape();
    ofVertex(1050, 400);
    ofVertex(1250, 400);
    ofVertex(1450, 900);
    ofVertex(1250, 900);
    ofVertex(1060, 400);
    ofEndShape();
    
    ofSetColor(205, 60, 60);
    ofFill();
    ofDrawEllipse(700, 0, 1800, 1400);
    
    /* face */
    inner_face.setHsb(hue1, 80, 200);
    ofSetColor(inner_face);
    ofFill();
    ofBeginShape();
    ofVertex(550, 50);
    ofVertex(360, 300);
    ofVertex(490, 650);
    ofVertex(905, 650);
    ofVertex(1040, 300);
    ofVertex(850, 50);
    ofVertex(550, 50);
    ofEndShape();
    
    outer_face.set(ofMap(hue, 0, 255, 253, 255), ofMap(hue, 0, 255, 230, 250), ofMap(hue, 0, 255, 200, 240));
    ofSetColor(outer_face);
    ofFill();
    ofDrawEllipse(700, 350, 560, 520);
    
    blush.set(ofMap(hue1, 0, 255, 230, 255), ofMap(hue1, 0, 255, 180, 240), ofMap(hue1, 0, 255, 190, 230));
    ofSetColor(blush);
    ofFill();
    ofDrawEllipse(520, 400, 100, 30);
    ofDrawEllipse(880, 400, 100, 30);
    
    
    
    /* eyes */
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(585, 275, 75);
    ofDrawCircle(815, 275, 75);
    
    ofSetColor(0, 0, 0);
    
    float distance_left = left_eye_center.distance(left_eye_pos);
    float distance_right = right_eye_center.distance(right_eye_pos);
    
    if (distance_left >= 40){
        float ratio_left = 40/distance_left;
        ofVec2f new_left_pos = left_eye_center*(1-ratio_left) + left_eye_pos*ratio_left;
        ofDrawCircle(new_left_pos.x, new_left_pos.y, 35);
    }
    if (distance_left < 40){
        ofDrawCircle(left_eye_pos.x, left_eye_pos.y, 35);
    }
    
    if (distance_right >= 40){
        float ratio_right = 40/distance_right;
        ofVec2f new_right_pos = right_eye_center*(1-ratio_right) + right_eye_pos*ratio_right;
        ofDrawCircle(new_right_pos.x, new_right_pos.y, 35);
    }
    if (distance_right < 40){
        ofDrawCircle(right_eye_pos.x, right_eye_pos.y, 35);
    }
    

    
    /* neck */
    
    neck.set(ofMap(hue, 0, 255, 225, 255), ofMap(hue, 0, 255, 130, 190), ofMap(hue, 0, 255, 130, 200));
    ofSetColor(neck);
    ofFill();
    ofDrawRectangle(625, 650, 150, 125);
    
    /* body */
    //body.set(ofMap(hue, 0, 255, 30, 70), ofMap(hue, 0, 255, 205, 230), ofMap(hue, 0, 255, 200, 255));
    body.setHsb(ofMap(hue2, 0, 255, 200, 250), ofMap(hue2, 0, 255, 20, 50), ofMap(hue2, 0, 255, 200, 250));
    ofSetColor(body);
    ofFill();
    ofBeginShape();
    ofVertex(550, 775);
    ofVertex(850, 775);
    ofVertex(1050, 900);
    ofVertex(350, 900);
    ofVertex(550, 775);
    ofEndShape();
    
    /* hair part1 */
    
    if (ofGetFrameNum()%100 < 25){
        
        ofSetColor(255, 215, 0);
        ofFill();
        ofDrawCircle(1090, 300, 50);
        ofDrawCircle(215, 210, 80);
        
    
        ofSetColor(0, 191, 255);
        ofFill();
        ofDrawCircle(1185, 210, 80);
        ofDrawCircle(180, 345, 60);
    
        ofSetColor(255, 245, 238);
        ofFill();
        ofDrawCircle(1220, 345, 60);
        ofDrawCircle(310, 300, 50);
    
        ofSetColor(193, 255, 193);
        ofFill();
        ofDrawCircle(1235, 433, 30);
        ofDrawCircle(165, 433, 30);
    }
    
    if (ofGetFrameNum()%100 > 75){
        
        ofSetColor(193, 255, 193);
        ofFill();
        
        ofDrawCircle(215, 210, 80);
        ofDrawCircle(1220, 345, 60);
    
        ofSetColor(255, 245, 238);
        ofFill();
        ofDrawCircle(1185, 210, 80);
        ofDrawCircle(310, 300, 50);
    
        ofSetColor(255, 215, 0);
        ofFill();
        ofDrawCircle(1090, 300, 50);
        ofDrawCircle(1235, 433, 30);
    
        ofSetColor(0, 191, 255);
        ofFill();
        ofDrawCircle(180, 345, 60);
        ofDrawCircle(165, 433, 30);
    }
    
    if (ofGetFrameNum()%100 > 50 and ofGetFrameNum()%100 <75){
    
        ofSetColor(255, 245, 238);
        ofFill();
        ofDrawCircle(1185, 210, 80);
        ofDrawCircle(310, 300, 50);
        ofDrawCircle(180, 345, 60);
        ofDrawCircle(1235, 433, 30);
    
        ofSetColor(255, 215, 0);
        ofFill();
        ofDrawCircle(1090, 300, 50);
        ofDrawCircle(1220, 345, 60);
        ofDrawCircle(215, 210, 80);
        ofDrawCircle(165, 433, 30);
    }
    
    if (ofGetFrameNum()%100 > 25 and ofGetFrameNum()%100 < 50){
        
        ofSetColor(193, 255, 193);
        ofFill();
        ofDrawCircle(215, 210, 80);
        ofDrawCircle(165, 433, 30);

        ofSetColor(0, 191, 255);
        ofFill();
        ofDrawCircle(1090, 300, 50);
        ofDrawCircle(1220, 345, 60);
        
        ofSetColor(255, 215, 0);
        ofFill();
        ofDrawCircle(1185, 210, 80);
        ofDrawCircle(310, 300, 50);
        
        ofSetColor(255, 245, 238);
        ofFill();
        ofDrawCircle(180, 345, 60);
        ofDrawCircle(1235, 433, 30);
    }
    
    
    
    
    
    
    

    
    
    
    
    
    
    /* -----------------------------------  coloring  ---------------- */
    
    
    /* -----------------------------------  outline  ---------------- */
    
    ofNoFill();
    ofSetHexColor(0x000000);
    ofSetLineWidth(3.5);
    
    /* face */
    
    ofBeginShape();
    ofVertex(550, 50);
    ofVertex(360, 300);
    ofVertex(490, 650);
    ofVertex(905, 650);
    ofVertex(1040, 300);
    ofVertex(850, 50);
    ofVertex(550, 50);
    ofEndShape();

    
    ofDrawEllipse(700, 350, 560, 520);
    
//    ofDrawEllipse(520, 400, 100, 30);
//    ofDrawEllipse(880, 400, 100, 30);
    
    
    /* eyes */
    ofDrawCircle(585, 275, 75);
    ofDrawCircle(815, 275, 75);
    
    //ofDrawCircle(585, 275, 25);
    //ofDrawCircle(815, 275, 25);
    
    /* eyeborw */
    
    ofBeginShape();
    ofVertex(650, 175);
    ofVertex(600, 170);
    ofVertex(500, 200);
    ofEndShape();
    
    ofBeginShape();
    ofVertex(750, 175);
    ofVertex(825, 170);
    ofVertex(900, 200);
    ofEndShape();
    
    /* nose */

    ofBeginShape();
    ofVertex(700, 375);
    ofVertex(750, 400);
    ofVertex(700, 425);
    ofEndShape();
    
    /* mouse */
 
    //ofDrawCurve(600, 800, 600, 500, 850, 500, 850, 800);
    ofDrawCurve(575, 200, 575, 500, 825, 500, 825, 200);
    
    
    
    /* neck */
    
    ofDrawRectangle(625, 650, 150, 125);
    
    /* body */
    ofBeginShape();
    ofVertex(550, 775);
    ofVertex(850, 775);
    ofVertex(1050, 900);
    ofVertex(350, 900);
    ofVertex(550, 775);
    ofEndShape();
    
    /* hair */
    
    ofDrawCircle(1090, 300, 50);
    ofDrawCircle(1185, 210, 80);
    ofDrawCircle(1220, 345, 60);
    ofDrawCircle(1235, 433, 30);

    ofDrawCircle(310, 300, 50);
    ofDrawCircle(215, 210, 80);
    ofDrawCircle(180, 345, 60);
    ofDrawCircle(165, 433, 30);
    
    /* -----------------------------------  outline  ---------------- */
    
    
    

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

float ofApp::min(float a, float b){
    if (a <= b){
        return a;
    }
    else{
        return b;
    }
}
