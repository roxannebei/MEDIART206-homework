#include "ofApp.h"

float r_upperBound = 240;
float r_h = 30;

float b_upperBound = 400;
float b_h = 40;

float reverse_upperBound = 370;
float reverse_h = 100;


//--------------------------------------------------------------
void ofApp::setup(){
    
    vid1.load("video1.mp4");
    vid1.play();
    vid.load("video.mp4");
    vid.play();
    
    vidShift.allocate(640,480, OF_IMAGE_COLOR);
    vidShift_noNoise.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    vidShift_bw.allocate(640, 480, OF_IMAGE_GRAYSCALE);
}

float ofApp::check_row(float data){
    if (data < 0){
        return 0;
    }
    if (data > vid.getWidth()){
        return vid.getWidth();
    }
    else {
        return data;
    }
}

float ofApp::check_col(float data){
    if (data < 0){
        return 0;
    }
    if (data > vid.getHeight()){
        return vid.getHeight();
    }
    else {
        return data;
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    float time = ofGetElapsedTimef();
    float time_variable = min(fmodf(time, 200), 200-fmodf(time, 200));
    

    r_upperBound = ofRandom(0, vid.getHeight()-10);
    r_h = ofRandom(3, 20);
    b_upperBound = ofRandom(vid.getHeight()/3, vid.getHeight()-10);
    b_h = ofRandom(5, 30);
    reverse_upperBound = ofRandom(0, vid.getHeight()*4/5);
    reverse_h = ofRandom(5, 80);

    
    vid.update();
    vid1.update();
    
    if (vid1.isFrameNew()){
        
        for (int y = 0; y < vid1.getHeight(); y++){
        
            for (int x = 0; x < vid1.getWidth(); x++){
                
                ofColor color = vid1.getPixels().getColor(x,y);
                float brightness = color.getLightness();
                
                ofVec2f pos;
                pos.set(x,y);
                pos.normalize();
                
                
                float offset_x1 = brightness * pos.x * sin(time_variable) * ofMap(x, 0, vid1.getWidth(), -5, 5);
                float offset_y1 = brightness * pos.y * cos(time_variable) * ofMap(y, 0, vid1.getHeight(), -5, 5);
                float offset_x2 = pos.x * time_variable * ofMap(x, 0, vid1.getWidth(), -2, 2);
                float offset_y2 = pos.y * time_variable * ofMap(y, 0, vid1.getHeight(), -2, 2);

                float newX1 = vid1.getWidth() - (x + offset_x1);
                float newY1 = vid1.getHeight() - (y + offset_y1);
                float newX2 = x + offset_x2;
                float newY2 = y + offset_y2;
                
                vidShift_noNoise.setColor(check_row(newX1), check_col(newY1), color);
                vidShift_bw.setColor(check_row(newX2), check_col(newY2), color);
            }
        }
                
    }
    
    if (vid.isFrameNew())
    {
        
        for (int y = 0; y < vid.getHeight(); y++){
        
            for (int x = 0; x < vid.getWidth(); x++){
                
                
                ofColor color = vid.getPixels().getColor(x,y);
                float brightness = color.getLightness()/255;
                

                int offset_x3 = ofNoise(y * .002, cos(time)) * ofMap(ofGetMouseX() - 320, -320, 320, -50, 100);
                int offset_y3 = ofNoise(x * .002, sin(time)) * ofMap(ofGetMouseY() - 240, -240, 240, -50, 100);

                int newX3 = x + offset_x3;
                int newY3 = y + offset_y3;
                
                if (y > r_upperBound and y < r_upperBound+r_h){
                    if (color.r + color.g + color.b > 80){
                        color = ofColor(255-color.r, color.g, color.b);
                    }
                }
                if (y > b_upperBound and y < b_upperBound+b_h){
                    if (color.r + color.g +color.b > 150){
                        color = ofColor(color.r, color.g, 255-color.b);
                    }
                }
                if (y > reverse_upperBound and y < reverse_upperBound+reverse_h){
                    if (color.r + color.g + color.b > 300){
                        color = ofColor(255-color.r, 255-color.b, 255-color.g);
                    }
                }
                
            
                vidShift.setColor(check_row(newX3), check_col(newY3), color);

                
            }
        }
        
        
        vidShift.update();
        vidShift_noNoise.update();
        vidShift_bw.update();
    }
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (int(ofGetElapsedTimef())%10 < 5){
        vidShift.draw(0,0, ofGetWidth(), ofGetHeight());
    }
    else if (int(ofGetElapsedTimef())%10 == 5 or int(ofGetElapsedTimef())%10 == 6){
        vidShift.draw(0, 0, ofGetWidth()/2, ofGetHeight()/2);
        vidShift_noNoise.draw(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight()/2);
        vidShift_bw.draw(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
        vidShift.draw(ofGetWidth()/2, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);
    }
    else{
        vidShift.draw(0, 0, ofGetWidth()/3, ofGetHeight()/3);
        vidShift_noNoise.draw(0, ofGetHeight()*1/3, ofGetWidth()/3, ofGetHeight()/3);
        vidShift.draw(0, ofGetHeight()*2/3, ofGetWidth()/3, ofGetHeight()/3);
        
        vidShift_noNoise.draw(ofGetWidth()*1/3, 0, ofGetWidth()/3, ofGetHeight()/3);
        vidShift.draw(ofGetWidth()*1/3, ofGetHeight()*1/3, ofGetWidth()/3, ofGetHeight()/3);
        vidShift_bw.draw(ofGetWidth()*1/3, ofGetHeight()*2/3, ofGetWidth()/3, ofGetHeight()/3);
        
        vidShift.draw(ofGetWidth()*2/3, 0, ofGetWidth()/3, ofGetHeight()/3);
        vidShift_bw.draw(ofGetWidth()*2/3, ofGetHeight()*1/3, ofGetWidth()/3, ofGetHeight()/3);
        vidShift.draw(ofGetWidth()*2/3, ofGetHeight()*2/3, ofGetWidth()/3, ofGetHeight()/3);
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

