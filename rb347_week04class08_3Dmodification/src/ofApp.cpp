#include "ofApp.h"

int num_of_sphere = 100;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetSmoothLighting(true);
    ofSetFrameRate(60.f);
    ofBackground(50);
    
    for (int i = 0; i < num_of_sphere; i++){
        glm::vec3 velocity;
        velocity.x = ofRandom(-2, 2);
        velocity.y = ofRandom(-2, 2);
        velocity.z = ofRandom(-2, 2);
        
        glm::vec3 pos = glm::vec3(ofRandom(100), ofRandom(100), ofRandom(100));
        
        Sphere sphere = Sphere(pos);
        sphere.set_velocity(velocity);
        
        sphere_list.push_back(sphere);
    }
    
    box = Box(glm::vec3(0, 0, 0), ofGetHeight());
    
    sunlight.setDirectional();
    sunlight.setPosition(200, 0, -1000);
    sunlight.lookAt(glm::vec3(0));
    sunlight.setDiffuseColor(ofColor::wheat);
    
    firelight.setPointLight();
    firelight.setPosition(0, -500, 0);
    firelight.setDiffuseColor(ofColor::red);

}

//--------------------------------------------------------------
void ofApp::update(){
    
    float display_num = min(fmodf(ofGetElapsedTimef()*2, 200) , 200-fmodf(ofGetElapsedTimef()*2, 200)  );
    
    for (int i=0; i < num_of_sphere; i++)
    {
        sphere_list[i].update();
        sphere_list[i].wall_detection(box.getLeft(), box.getRight(), box.getTop(), box.getBottom(), box.getFront(), box.getBack());
    }
    
    sunlight.rotateDeg(.2, 0, 0.1, 0);

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float display_num = min(fmodf(ofGetElapsedTimef()*2, 200) , 200-fmodf(ofGetElapsedTimef()*2, 200)  );
    
    ofColor current_color = ofColor::fromHsb(255-(100-display_num), 100, 200);
    ofColor brown = ofColor(160, 70, 32);
    
    ofBackgroundGradient(current_color, brown, OF_GRADIENT_LINEAR);
   
    ofEnableLighting();
    camera.begin();
    ofEnableDepthTest();
    
    sunlight.enable();
    firelight.enable();
    
    ofFill();
    if (display_num < 5){
        display_num = 5;
    }
    for (int i = 0; i < display_num; i++){
        for (int j = 0; j < display_num; j++){
            if (i != j){
                sphere_list[i].collision(sphere_list[j]);
            }
        }
        sphere_list[i].draw();
    }
    
    sunlight.disable();
    firelight.disable();
    ofDisableLighting();
    
    ofSetHexColor(0xFFFFFF);
    ofNoFill();
    box.draw();
    
    ofSetColor(255, 30);
    ofFill();
    box.draw();
    ofNoFill();
    
    ofDrawAxis( 100 );
    
    ofDisableDepthTest();
    
    sunlight.draw();
    firelight.draw();
    
    camera.end();
        
    string info = "click and drag left button to rotate camera\n";
    info += "click and drag right button (or scroll wheel) to zoom\n";
    info += "Number of spheres: ";
    info += to_string((int)display_num);
    info += "\n";
    info += "Timer: ";
    info += to_string((int)ofGetElapsedTimef());
    ofDrawBitmapStringHighlight(info, 20,20);
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
