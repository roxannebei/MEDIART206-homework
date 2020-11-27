#include "ofApp.h"

bool draw_box = true;
int snowman_lowerR;
int snowman_upperR;

int temperature = 15;
//int temperature = -8;

int refresh1 = 1;
int refresh2 = 0;

float ccount = 0;
vector<Snow> snow_on_floor;

glm::vec3 hat_pos;
glm::vec3 nose_pos;
glm::vec3 lowerB_pos;
glm::vec3 upperB_pos;
glm::vec3 leftEye_pos;
glm::vec3 rightEye_pos;
glm::vec3 scarf1_pos;
glm::vec3 scarf2_pos;

int status;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetSmoothLighting(true);
    ofSetCircleResolution(300);
    ofSetCylinderResolution(200, 300);
    ofSetConeResolution(200, 300);
    ofSetFrameRate(60.f);
    ofBackground(50);
    
    box = Box(glm::vec3(0, 0, 0), ofGetHeight());
    
    for (int i = 0; i < 1000; i++){
        
        glm::vec3 position;
        position.x = ofRandom(box.getLeft(), box.getRight());
        position.y = ofRandom(2*box.getBottom(), 2*box.getTop());
        position.z = ofRandom(box.getFront(), box.getBack());
        
        Snow snow = Snow(position, 2);
        snow_list.push_back(snow);
    }
    
    sun.setDirectional();
    //sun1.setDirectional();
    lake_light.setDirectional();
    clock_light.setDirectional();
    
    lake_light.setPosition(700, -500, 1000);
    clock_light.setPosition(-1000, 300, 2000);
    sun.setPosition(200, 0, -3000);
    //sun1.setPosition(200, 0, -5000);
    
    lake_light.lookAt(glm::vec3(box.getRight(), 0, box.getBack()));
    sun.lookAt(glm::vec3(0));
    //sun1.lookAt(glm::vec3(0));
    clock_light.lookAt(glm::vec3(0));
    lake_light.setDiffuseColor(ofColor::aliceBlue);
    sun.setDiffuseColor(ofColor::snow);
    //sun1.setDiffuseColor(ofColor::snow);
    clock_light.setDiffuseColor(ofColor::antiqueWhite);
    
    
    //camera.setPosition(0,box.getBottom()+250,box.getTop()*1.2);
    camera.setPosition(box.getRight()*5/6, box.getBottom()+250, box.getBack()*1.2);
    camera.lookAt(glm::vec3(0, box.getBottom()+300, 0));
    
    BOX = ofBoxPrimitive(box.getLeft()*2, box.getLeft()*2, box.getLeft()*2);
    



}

//--------------------------------------------------------------
void ofApp::update(){
    
    glm::vec3 gravity(0, -0.05, 0);
    
    int num_of_snow;
    num_of_snow = ofMap(temperature, -10, 10, 1000, 0);
    
    for (int i = 0; i < num_of_snow; i++){
        float lower_bound = ofRandom(box.getBottom(), box.getBottom()*2);
        if (!snow_list[i].in_box(lower_bound)){
            float update_y = ofRandom(2*box.getBottom(), 1.2*box.getTop());
            snow_list[i].reset(update_y);
            ccount+=0.002;
        }

        snow_list[i].edge_detection(box.getLeft(), box.getRight(), box.getFront(), box.getBack());
        snow_list[i].apply_force(gravity);
        snow_list[i].update();
    }
    
    
    for (int i = 0; i < ccount; i++){
        glm::vec3 position;
        position.x = ofRandom(box.getLeft(), box.getRight());
        position.z = ofRandom(box.getFront(), box.getBack());
        float delta = 0;
        if (ofDist(position.x, position.z, box.getRight()-300, box.getBack()-70) < 450){
            delta += 20;
        }
        
        delta += ofMap(ccount, 0, 40, 0, 5);
        position.y = box.getBottom()+2.5 + delta;
        
        Snow snow = Snow(position, 1.5);
        snow_on_floor.push_back(snow);
    }
    if (temperature >= 9){
        snow_on_floor.clear();
    }

    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor center, bg;
    center.r = ofMap(temperature, -10, 15, 197, 238);
    center.g = ofMap(temperature, -10, 15, 66, 106);
    center.b = ofMap(temperature, -10, 15, 30, 80);
    bg.r = ofMap(temperature, -10, 15, 224, 238);
    bg.g = ofMap(temperature, -10, 15, 115, 154);
    bg.b = ofMap(temperature, -10, 15, 51, 73);
    ofBackgroundGradient(center, bg);
    
    
    camera.begin();
    ofEnableDepthTest();
    
    
    int num_of_snow;
    num_of_snow = ofMap(temperature, -10, 10, 1000, 0);
    
    for (int i = 0; i < num_of_snow; i++){
        snow_list[i].display();
    }
    
    int num_of_snow_on_floor;
    num_of_snow_on_floor = snow_on_floor.size() * (1 - (temperature+10)/19);
   
    for (int i = 0; i < num_of_snow_on_floor; i++){
        snow_on_floor[i].display();
    }

    
    ofDrawSphere(box.getLeft(), box.getBottom(), box.getFront(), 20);
   
    ofEnableLighting();
    sun.enable();
    //sun1.enable();
    
//    ofColor ground(205, 179, 139);
//    ofColor autumn(255, 228, 196);
//    ofBackgroundGradient(ground, autumn, OF_GRADIENT_LINEAR);
    
    snowman_lowerR = 100;
    snowman_upperR = 68;
    
    ofPushStyle();
    
    ofSetColor(255, 228, 196);
    ofFill();
    ofBoxPrimitive ground;
    ground = ofBoxPrimitive(5000, 5, 5000);
    ground.setPosition(0, box.getBottom(), 0);
    ground.draw();
    
    ofSetColor(255, 250, 250);
    ofFill();
    if (refresh1 != refresh2){
        lowerB_pos.x = set(box.getRight()-snowman_lowerR-100, 9);
        lowerB_pos.y = set(box.getBottom()+snowman_lowerR, 9);
        lowerB_pos.z = set(-100, 9);
        
    }
    ofDrawSphere(lowerB_pos.x, lowerB_pos.y, lowerB_pos.z, snowman_lowerR);
    
    if (temperature <= -5){
        ofPushStyle();
        ofSetColor(139, 115, 85);
        ofNoFill();
        ofSetLineWidth(6);
        ofDrawLine(box.getRight()-snowman_lowerR-100, box.getBottom()+snowman_lowerR-30, -80, box.getRight()-70, box.getBottom()+snowman_lowerR+100, -60);
        ofSetColor(139, 69, 19);
        ofNoFill();
        ofDrawLine(box.getRight()-snowman_lowerR-110, box.getBottom()+snowman_lowerR-50, -80, 150, box.getBottom()+snowman_lowerR+120, -80);
        ofPopStyle();
    }
    

    ofPushStyle();
    ofSetColor(60, 179, 113);
    if (temperature <= -7){
        ofDrawSphere(box.getRight()-snowman_lowerR-100, box.getBottom()+snowman_lowerR+30, -3, 5);
    }
    ofSetColor(238, 99, 99);
    if (temperature <= -8){
        ofDrawSphere(box.getRight()-snowman_lowerR-100, box.getBottom()+snowman_lowerR, 0, 5);
    }
    ofSetColor(99, 184, 255);
    if (temperature <= -9){
        ofDrawSphere(box.getRight()-snowman_lowerR-100, box.getBottom()+snowman_lowerR-30, -3, 5);
    }
    ofPopStyle();
    
    ofSetColor(205, 0, 0);
    ofFill();
    if (refresh1 != refresh2){
        scarf1_pos.x = set(box.getRight()-snowman_lowerR-100, -3);
        scarf1_pos.y = set(box.getBottom()+2*snowman_lowerR-25, -3);
        scarf1_pos.z = set(-100, -3);
        scarf2_pos.x = set(box.getRight()-snowman_lowerR-85, -3);
        scarf2_pos.y = set( box.getBottom()+2*snowman_lowerR-75, -3);
        scarf2_pos.z = set(-25, -3);
    }
    if (temperature <= 1){
        ofDrawCylinder(scarf1_pos, 70, 45);
        ofDrawCylinder(scarf2_pos, 15, 100);
    }
    
    
    ofSetColor(255, 250, 250);
    ofFill();
    if (refresh1 != refresh2){
        upperB_pos.x = set(box.getRight()-snowman_lowerR-100, 8);
        upperB_pos.y = set(box.getBottom()+snowman_upperR+2*snowman_lowerR-27, 8);
        upperB_pos.z = set(-100, 8);
    }
    ofDrawSphere(upperB_pos, snowman_upperR);
    
    ofSetColor(0, 0, 0);
    ofFill();
    if (refresh1 != refresh2){
        leftEye_pos.x = set(box.getRight()-snowman_lowerR-140, 2);
        leftEye_pos.y = set(box.getBottom()+2*snowman_lowerR+snowman_upperR-20, 2);
        leftEye_pos.z = set(-47, 2);
        rightEye_pos.x = set(box.getRight()-snowman_lowerR-100, 2);
        rightEye_pos.y = set(box.getBottom()+2*snowman_lowerR+snowman_upperR-20, 2);
        rightEye_pos.z = set(-32, 2);
    }
    if (temperature <= 5){
        ofDrawSphere(rightEye_pos, 5);
        ofDrawSphere(leftEye_pos, 5);
    }
    
    //nose
    ofSetColor(255, 165, 0);
    ofFill();
    ofPushMatrix();
    if (refresh1 != refresh2){
        nose_pos.x = set(box.getRight()-snowman_lowerR-110, -1);
        nose_pos.y = set(box.getBottom()+2*snowman_lowerR+25, -1);
        nose_pos.z = set(-40, -1);
    }
    ofRotateDeg(270, nose_pos.x+5, nose_pos.y, nose_pos.z);
    if (temperature <= 3){
        ofDrawCone(nose_pos, 15, 70);
    }
    ofPopMatrix();
    
    // hat
    ofSetColor(238, 197, 145);
    ofFill();
    ofPushMatrix();
    ofRotateDeg(180);

    if(refresh1 != refresh2){
        hat_pos.x = set(-(box.getRight()-snowman_lowerR-100), 5);
        hat_pos.y = set(-(box.getBottom()+snowman_upperR*2+snowman_lowerR*2-25), 5);
        hat_pos.z = set(-100, 5);
        refresh2++;
    }
    if (temperature <= 9){
        ofDrawCone(hat_pos.x, hat_pos.y, hat_pos.z, 95, 85);
    }
    ofPopMatrix();
    
    ofPopStyle();

    
    // lake
    lake_light.enable();
    ofCylinderPrimitive lake;
    lake = ofCylinderPrimitive(450, 40, 300, 300);
    lake.setPosition(box.getRight()-300, box.getBottom(), box.getBack()-70);
    int lake_alpha;
    lake_alpha = ofMap(temperature, -10, 15, 100, 255);
    ofPushStyle();
    ofColor warm_lake(135, 206, 235);
    ofColor cold_lake(198, 226, 255);
    float lake_r = ofMap(temperature, -10, 15, cold_lake.r, warm_lake.r);
    float lake_g = ofMap(temperature, -10, 15, cold_lake.g, warm_lake.g);
    float lake_b = ofMap(temperature, -10, 15, cold_lake.b, warm_lake.b);
    ofSetColor(lake_r, lake_g, lake_b, lake_alpha);
    ofFill();
    ofDrawCylinder(box.getRight()-300, box.getBottom(), box.getBack()-70, 450, 40);
    ofSetColor(lake_r, lake_g, lake_b);
    ofFill();
    lake.drawWireframe();
    ofPopStyle();
    lake_light.disable();

    
    // clock-building
    clock_light.enable();
    
    //ofSetColor(238, 207, 161);
    //ofSetColor(205, 175, 149);
    //ofSetColor(238, 203, 173);
    ofPushStyle();
    ofSetColor(205, 170, 125);
    ofFill();
    ofBoxPrimitive clock_B;
    clock_B = ofBoxPrimitive(200, 550, 200);
    clock_B.setPosition(box.getLeft()+clock_B.getWidth()/2, box.getBottom()+clock_B.getHeight()/2, 0);
    clock_B.draw();
    ofSetColor(139, 115, 85);
    ofNoFill();
    ofSetLineWidth(3);
    clock_B.drawWireframe();
    ofPopStyle();
    
    ofSetColor(255, 228, 196);
    ofFill();
    ofBoxPrimitive clock_c;
    ofSpherePrimitive clock_itself;
    clock_c = ofBoxPrimitive(clock_B.getWidth(), 150, clock_B.getDepth());
    clock_itself = ofSpherePrimitive(120, 300);
    clock_c.setPosition(box.getLeft()+clock_B.getWidth()/2, box.getBottom()+clock_B.getHeight()+clock_c.getHeight()/2, 0);
    clock_itself.setPosition(box.getLeft()+clock_B.getWidth()/2, box.getBottom()+clock_B.getHeight()+clock_c.getHeight()/2, 0);
    clock_c.drawFaces();
    ofSetColor(255, 255, 255);
    clock_itself.draw();
    
   
    for (int i = 0; i < 180; i++){
        ofPushStyle();
        ofSetColor(238, 203, 173);
        ofFill();
        ofBoxPrimitive clock_roof_i;
        float step_size = (clock_B.getWidth())/180;
        clock_roof_i = ofBoxPrimitive(clock_B.getWidth()-step_size*(i), 1, clock_B.getDepth()-step_size*(i));
        clock_roof_i.setPosition(box.getLeft()+clock_B.getWidth()/2, -clock_roof_i.getHeight()/2+box.getBottom()+clock_B.getHeight()+ (i+1)*clock_roof_i.getHeight()+clock_c.getHeight(), 0);
        clock_roof_i.drawFaces();
        ofSetColor(205, 175, 149);
        ofNoFill();
        ofSetLineWidth(1);
        clock_roof_i.drawWireframe();
        ofPopStyle();
    }
    clock_light.disable();
    
    // back-building
    
    ofBoxPrimitive backB1, backB2, backB3, backB4, backB5;
    glm::vec3 backB1_pos, backB2_pos, backB3_pos, backB4_pos, backB5_pos;
    float w1 = 150;
    float w2 = 250;
    float w3 = 200;
    float d1 = 300;
    float d2 = 200;
    float d3 = 300;
    float h1 = 300;
    float h2 = 500;
    float h3 = 700;
    
    backB1 = ofBoxPrimitive(w1, h1, d1);
    backB2 = ofBoxPrimitive(w2, h2-100, d2);
    backB3 = ofBoxPrimitive(w3, h3, d3);
    backB4 = ofBoxPrimitive(w2, h2-100, d2);
    backB5 = ofBoxPrimitive(w1, h1, d1);
    
    backB1_pos = glm::vec3(box.getLeft()+w1/2, box.getBottom()+h1/2, box.getFront()+d1/2);
    backB2_pos = glm::vec3(backB1_pos.x + w1/2 + w2/2, box.getBottom()+h2/2, box.getFront()+d2/2);
    backB3_pos = glm::vec3(backB2_pos.x + w2/2 + w3/2, box.getBottom()+h3/2, box.getFront()+d3/2);
    backB4_pos = glm::vec3(-backB2_pos.x, backB2_pos.y, backB2_pos.z);
    backB5_pos = glm::vec3(-backB1_pos.x, backB1_pos.y, backB1_pos.z);
    backB1.setPosition(backB1_pos);
    backB2.setPosition(backB2_pos);
    backB3.setPosition(backB3_pos);
    backB4.setPosition(backB4_pos);
    backB5.setPosition(backB5_pos);
    
    ofPushStyle();
    ofSetColor(238, 203, 173);
    //ofSetColor(238, 207, 161);
    ofFill();
    backB1.draw();
    backB5.draw();
    backB3.draw();
    ofSetColor(205, 170, 125);
    //ofSetColor(250, 197, 145);
    ofFill();
    backB2.draw();
    backB4.draw();
    ofSetColor(139, 115, 85);
    ofNoFill();
    ofSetLineWidth(1.5);
    backB2.drawWireframe();
    backB4.drawWireframe();
    
    ofPopStyle();
    
    for (int i = 0; i < 4; i++){
        ofPushStyle();
        ofSetColor(205, 183, 158);
        ofDrawBox(backB2_pos.x, backB2_pos.y+h2/2-25, backB2_pos.z, w2, 50, d2);
        ofBoxPrimitive B2_roof_i;
        B2_roof_i = ofBoxPrimitive(25, 25, d2);
        B2_roof_i.setPosition(backB2_pos.x-w2/2+ (i*3+0.5)*25, backB2_pos.y+h2/2+B2_roof_i.getHeight()/2, backB2_pos.z);
        B2_roof_i.draw();
        ofPopStyle();
    }
    
    for (int i = 0; i < 4; i++){
        ofPushStyle();
        ofSetColor(205, 183, 158);
        ofDrawBox(backB4_pos.x, backB4_pos.y+h2/2-25, backB4_pos.z, w2, 50, d2);
        ofBoxPrimitive B4_roof_i;
        B4_roof_i = ofBoxPrimitive(25, 25, d2);
        B4_roof_i.setPosition(backB4_pos.x-w2/2+ (i*3+0.5)*25, backB4_pos.y+h2/2+B4_roof_i.getHeight()/2, backB4_pos.z);
        B4_roof_i.draw();
    }
    
    for (int i = 0; i < 150; i++){
        ofPushStyle();
        ofSetColor(205, 175, 149);
        ofFill();
        ofBoxPrimitive B3_roof_i;
        float step_size = (w3)/150;
        B3_roof_i = ofBoxPrimitive(w3-step_size*(i), 1, d3-step_size*(i));
        B3_roof_i.setPosition(backB3_pos.x, backB3_pos.y+h3/2+(i+0.5)*B3_roof_i.getHeight(), backB3_pos.z);
        B3_roof_i.draw();
        ofSetColor(205, 175, 149);
        ofNoFill();
        ofSetLineWidth(1);
        B3_roof_i.drawWireframe();
        ofPopStyle();
    }
    
    for (int i = 0; i < 100; i++){
        ofPushStyle();
        ofSetColor(205, 175, 149);
        ofFill();
        ofBoxPrimitive B1_roof_i;
        float step_size = (w1)/100;
        B1_roof_i = ofBoxPrimitive(w1-step_size*(i), 1, d1-step_size*(i));
        B1_roof_i.setPosition(backB1_pos.x, backB1_pos.y+h1/2+(i+0.5)*B1_roof_i.getHeight(), backB1_pos.z);
        B1_roof_i.draw();
        ofSetColor(205, 175, 149);
        ofNoFill();
        ofSetLineWidth(1);
        B1_roof_i.drawWireframe();
        ofPopStyle();
    }
    
    for (int i = 0; i < 100; i++){
        ofPushStyle();
        ofSetColor(205, 175, 149);
        ofFill();
        ofBoxPrimitive B5_roof_i;
        float step_size = (w1)/100;
        B5_roof_i = ofBoxPrimitive(w1-step_size*(i), 1, d1-step_size*(i));
        B5_roof_i.setPosition(backB5_pos.x, backB5_pos.y+h1/2+(i+0.5)*B5_roof_i.getHeight(), backB5_pos.z);
        B5_roof_i.draw();
        ofSetColor(205, 175, 149);
        ofNoFill();
        ofSetLineWidth(1);
        B5_roof_i.drawWireframe();
        ofPopStyle();
    }
    
    Tree myfirsttree;
    myfirsttree = Tree(box.getLeft()+80, box.getBottom(), 200, 350, 90);
    myfirsttree.display_2(temperature);
    Tree mysecondtree;
    mysecondtree = Tree(box.getLeft()+130, box.getBottom(), 320, 250, 50);
    mysecondtree.display_1(temperature);
    Tree mythirdtree;
    mythirdtree = Tree(box.getLeft()+180, box.getBottom(), -150, 300, 50);
    mythirdtree.display_1(temperature);
    Tree myfourthtree;
    myfourthtree = Tree(box.getLeft()+240, box.getBottom(), -240, 270, 70);
    myfourthtree.display_2(temperature);
    Tree myfifthtree;
    myfifthtree = Tree(box.getLeft()+150, box.getBottom(), 400, 250, 50);
    myfifthtree.display_2(temperature);
    
    sun.disable();
    
    ofDisableLighting();
    
    
    
    ofSetHexColor(0xFFFFFF);
    
    if (draw_box){
        ofPushStyle();
        ofNoFill();
        box.draw();
        ofPopStyle();
        BOX.drawWireframe();
    }
    //ofDrawAxis(100);
    
    ofDisableDepthTest();
    
    sun.draw();
    lake_light.draw();
    camera.end();
    
    string info = "Temperature: ";
    info += to_string(temperature);
    info += " degree centigrade. (range: -10 to 15)\n";
    int nSnow;
    if (num_of_snow <= 0){
        nSnow = 0;
        info += "\nWinter has NOT come yet.";
    }
    else if (num_of_snow > 1000){
        nSnow = 1000;
        info += "\nWinter doesn't want to bring you snowstorm :(";
    }
    else{
        nSnow = num_of_snow;
        info += "\nWinter is coming! Now enjoy the snow ;)";
    }
//    info += "\nnum_of_snow: ";
//    info += to_string(nSnow);
//
//    info += "\ncount: " + to_string(ccount);
//    info += "\n";
//    info += to_string(box.getLeft());
    info += "\n\n[Instruction]\n1. Use the \"UP\" and \"DOWN\" keys to control the temperature. \n2. Click and drag left button to rotate camera\n";
    info += "3. Click and drag right button (or scroll wheel) to zoom\n";
    
    ofDrawBitmapStringHighlight(info, 20,20);
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        draw_box = !draw_box;
    }
    
    if (key == OF_KEY_UP and temperature < 15){
        temperature++;
        refresh1++;
        status ++;
    }
    
    if (key == OF_KEY_DOWN and temperature > -10){
        temperature--;
        refresh1++;
        status--;
    }

}

float ofApp::set(float x, int t){ // t is the time that the shape is at the right position
    
    if (temperature <= t){
        return x;
    }
    else{
        int diff = temperature-9;
        float range_roof = 500 * diff/(15-t);
        float range_floor = 500 * (diff-1)/(15-t);
        float result = ofRandom(range_floor, range_roof);
        float random = ofRandom(0,1);
        if (random > 0.5){
            return result;
        }
        else{
            return -result;
        }
        
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
