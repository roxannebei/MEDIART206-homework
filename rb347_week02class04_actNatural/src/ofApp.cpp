#include "ofApp.h"

ofVec2f start_road;
ofVec2f end_road;
ofVec2f road_dir;

ofVec2f tree_buttom;
ofVec2f tree_top;
ofVec2f edge_left;
ofVec2f edge_mid;
ofVec2f edge_right;
ofVec2f side;
ofVec2f green_buttom;
ofVec2f green_top;



int copy1 = 1;
int copy2 = 0;
int copy3 = 1;
int copy4 = 0;
float current_time;
float current_time1;
float theata;

bool morning = true;

vector<float> random_x;
vector<float> random_y;


//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableSmoothing();
    
    
    if (!morning){
        ofBackground(60);
    }
    
    
    for (int i = 0; i<50; i++){
        random_x.push_back(ofRandom(ofGetWidth()));
        random_y.push_back(ofRandom(500));
    }
    

    
    start_road.set(500, 350);
    end_road.set(750, 700);
    road_dir = end_road-start_road;
    road_dir.normalize();
    
    tree_buttom.set(1300, 450);
    tree_buttom -= start_road;
    tree_buttom.normalize();
    tree_top.set(1300, 275);
    tree_top -= start_road;
    tree_top.normalize();
    
    edge_left.set(0, 675);
    edge_left -= start_road;
    edge_left.normalize();
    edge_right.set(75, 700);
    edge_right -= start_road;
    edge_right.normalize();
    edge_mid.set(25, 700);
    edge_mid -= start_road;
    edge_mid.normalize();
    side.set(1300, 575);
    side -= start_road;
    side.normalize();
    green_buttom.set(0, 575);
    green_buttom -= start_road;
    green_buttom.normalize();
    green_top.set(0, 450);
    green_top -= start_road;
    green_top.normalize();
    
    

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    theata += PI/90;
    
    if (!morning){
        
        for(int i = 0; i<50; i++){
            ofSetColor(255, sin(theata*i/TWO_PI)*255);
            ofFill();
            ofDrawCircle(random_x[i], random_y[i], 3);
        }
    }
    
    if (morning){
        float hue = min(fmodf(ofGetElapsedTimef()*50, 510), 510-fmodf(ofGetElapsedTimef()*50, 510));
        ofSetColor(ofMap(hue, 0, 255, 130, 135), ofMap(hue, 0, 255, 191, 206), ofMap(hue, 0, 255, 220, 255));
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255, 114, 86);
        ofDrawCircle(500, 300, 250+20*sin(theata));
    }
    
    
    /* pure drawing */
    ofSetHexColor(0x000000);
    ofSetLineWidth(1.5);
//    ofDrawLine(start_road.x, start_road.y, 0, 300);
//    ofDrawLine(start_road.x, start_road.y, 75, 700);
//    ofDrawLine(start_road.x, start_road.y, 150, 700);
//    ofDrawLine(start_road.x, start_road.y, 175, 700);
//    ofDrawLine(start_road.x, start_road.y, 1300, 650);
//    ofDrawLine(start_road.x, start_road.y, 1300, 675);
//    ofDrawLine(start_road.x, start_road.y, 0, 675);
//    ofDrawLine(start_road.x, start_road.y, 0, 575);
//    ofDrawLine(start_road.x, start_road.y, 25, 700);
//    ofDrawLine(start_road.x, start_road.y, 1300, 575);
    
//    ofSetLineWidth(0.5);
//    ofDrawLine(start_road.x, start_road.y, 1300, 450);
//    ofSetLineWidth(1.5);
    
    ofSetColor(175);
    ofFill();
    ofDrawTriangle(start_road.x, start_road.y, 75, 700, 150, 700);
    ofDrawTriangle(start_road.x, start_road.y, 1300, 575, 1300, 650);
    ofBeginShape();
    ofVertex(start_road.x, start_road.y);
    ofVertex(175, 700);
    ofVertex(1300, 700);
    ofVertex(1300, 675);
    ofVertex(start_road.x, start_road.y);
    ofEndShape();
    
    ofSetColor(238, 216, 174);
    ofBeginShape();
    ofVertex(start_road.x, start_road.y);
    ofVertex(0, 675);
    ofVertex(0, 700);
    ofVertex(75, 700);
    ofVertex(start_road.x, start_road.y);
    ofEndShape();
    
    ofSetColor(255, 235, 200);
    ofDrawTriangle(start_road.x, start_road.y, 25, 700, 75, 700);
    ofDrawTriangle(1300, 450, 1300, 575, start_road.x, start_road.y);
    ofSetColor(205, 170, 125);
    ofDrawLine(start_road.x, start_road.y, 25, 700);
    
    
    ofSetColor(240, 255, 240);
   // ofDrawTriangle(start_road.x, start_road.y, 0, 450, 0, 470);
    ofDrawTriangle(start_road.x, start_road.y, 0, 485, 0, 505);
    ofDrawTriangle(start_road.x, start_road.y, 0, 520, 0, 540);
    ofDrawTriangle(start_road.x, start_road.y, 0, 555, 0, 575);
    
    ofSetColor(200, 230, 200);
   // ofDrawTriangle(start_road.x, start_road.y, 0, 470, 0, 485);
    ofDrawTriangle(start_road.x, start_road.y, 0, 540, 0, 555);
    ofDrawTriangle(start_road.x, start_road.y, 0, 505, 0, 520);
    //ofDrawTriangle(start_road.x, start_road.y, 0, 575, 0, 590);
    
    ofSetColor(170);
    ofDrawTriangle(start_road.x, start_road.y, 0, 575, 0, 675);
    ofSetColor(255);
    ofDrawTriangle(start_road.x, start_road.y, 0, 645, 0, 630);
    ofDrawTriangle(start_road.x, start_road.y, 150, 700, 175, 700);
    ofDrawTriangle(start_road.x, start_road.y, 1300, 650, 1300, 675);
    ofDrawBitmapString("Press the SPACE ;)", 50, 50);
    
    ofSetColor(255, 228, 225);
    ofDrawTriangle(1300, 450, 1300, 435, start_road.x, start_road.y);
    ofDrawTriangle(1300, 415, 1300, 400, start_road.x, start_road.y);
    ofSetColor(255, 245, 238);
    ofDrawTriangle(1300, 435, 1300, 415, start_road.x, start_road.y);
    ofDrawTriangle(1300, 400, 1300, 380, start_road.x, start_road.y);
    
    if (copy1 != copy2){
        current_time = ofGetElapsedTimef();
        copy2++;
    }
    if (copy3 != copy4){
        current_time1 = ofGetElapsedTimef();
        copy4++;
    }
    
    
    ofColor edge;
    edge.set(205, 170, 125);
    
    
    //ofDrawLine(start_road.x, start_road.y, end_road.x, end_road.y);
    
    if(int(ofGetElapsedTimef())%2 == 1){
        copy1++;
        Road *road = new Road(start_road, current_time, road_dir);
        road_vector.push_back(*road);
    }
    
    for (int i = 0; i < road_vector.size(); i++){
        road_vector[i].display();
    }
    
    if (int(ofGetElapsedTimef())%2 == 1){
        copy3++;
        Road *road = new Road(start_road, current_time1, road_dir);
        road_line_vector.push_back(*road);
    }
    for (int i = 0; i < road_line_vector.size(); i++){
        road_line_vector[i].display_line(edge_left, edge_mid, edge);
        road_line_vector[i].display_line(edge_right, edge_mid, edge);
        road_line_vector[i].display_line1(tree_buttom, side, edge);
    }
    
    //draw_roadLine(start_road, current_time);
    
    int step = 1;
    for (int i = 10; i<850; i+=step){
        step += 2;
        float x = start_road.x + tree_buttom.x*i;
        float y = start_road.y + tree_buttom.y*i;
        float y_top = start_road.y + tree_top.y*i;
        
        float x1 = start_road.x + green_buttom.x*i;
        float y1 = start_road.y + green_buttom.y*i;
        float y_top1 = start_road.y + green_top.y*i;
        
        ofSetColor(0, 139, 0);
        ofSetLineWidth(3);
        if (i%40 == 20){
            ofDrawLine(x, y, x, y_top+8*sin(i*ofGetElapsedTimef()));
            ofDrawLine(x1, y1, x1, y_top1+8*sin(i*ofGetElapsedTimef()));
        }
        else{
            ofDrawLine(x, y, x, y_top+8*sin(PI/32*i*ofGetElapsedTimef()));
            ofDrawLine(x1, y1, x1, y_top1+8*sin(PI/32*i*ofGetElapsedTimef()));
        }
    }
    
    
    

}




//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        morning = !morning;
        setup();
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


//--------------------------------------------------------------
//void ofApp::draw_roadLine(ofVec2f pos, float current_time){
//
//    float time = (ofGetElapsedTimef()-current_time)*10;
//
//    float x = pos.x + time*15*road_dir.x;
//    float y = pos.y + time*15*road_dir.y;
//    float w = 8+time/1.5;
//    float h = 10+time*3;
//
//    ofBeginShape();
//    ofVertex(x-w/2, y);
//    ofVertex(x+w/2, y);
//    ofVertex(x+5*h/7+w/2, y+h);
//    ofVertex(x+5*h/7-w/2, y+h);
//    ofVertex(x-w/2, y);
//    ofEndShape();
//
////    float x1 = pos.x + time*20*road_dir.x;
////    float y1 = pos.y + time*20*road_dir.y;
////    float w1 = 11+time/1.5;
////    float h1 = 15+time*3;
////
////    ofBeginShape();
////    ofVertex(x1-w1/2, y1);
////    ofVertex(x1+w1/2, y1);
////    ofVertex(x1+5*h1/7+w1/2, y1+h1);
////    ofVertex(x1+5*h1/7-w1/2, y1+h1);
////    ofVertex(x1-w1/2, y1);
////    ofEndShape();
//
//}

