#include "ofApp.h"

float sum_x = 0;
float sum_y = 0;
float countt = 0;
float avg_x = 0;
float avg_y = 0;
float scale_pos_x = 0;
float scale_pos_y = 0;

ofColor dark_pink = ofColor(205, 155, 155);
ofColor shallow_pink = ofColor(255, 228, 225);


ofColor light_sky = ofColor(82, 137, 189);
ofColor dark_sky = ofColor(35, 77, 117);
ofColor current_sky;
float sky_r;
float sky_g;
float sky_b;

int num_of_star;
int max_num_of_star = 80;

vector<float> star_x;
vector<float> star_y;
float theata;


void ofApp::setup(){
    kinect.open();
    img.allocate(521,424, OF_IMAGE_COLOR);
    
    for (int i = 0; i < max_num_of_star; i++){
        star_x.push_back(ofRandom(503, 1024));
        star_y.push_back(ofRandom(0, 330));
    }
    
    model.loadModel("mountain/mountain.obj");
    for (int i = 0; i < model.getMeshCount(); i++)
    {
        orig_mesh.push_back(model.getMesh(i));
        materials.push_back(model.getMaterialForMesh(i));
        textures.push_back(model.getTextureForMesh(i));
    }
    meshes = orig_mesh;
    
    sunlight.setDirectional();
    sunlight.setPosition(2000, 1800, 500);
    sunlight.lookAt(glm::vec3(-200, -200, -200));
    sunlight.setDiffuseColor(ofColor::antiqueWhite);

    
}


//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
    if(kinect.isFrameNew()){
        texture.loadData(kinect.getRawDepthPixels());
        
        sum_x = 0;
        sum_y = 0;
        countt = 0;
        avg_x = 0;
        avg_y = 0;
        scale_pos_x = 0;
        scale_pos_y = 0;
        
        for (int y=0; y < texture.getHeight(); y++){
            for (int x=0; x < texture.getWidth(); x++){
                ofColor color = kinect.getDepthPixels().getColor(x, y);
                float brightness = color.getBrightness();
                
//                if (brightness < 20){
//
//                    img.setColor(x, y, dark_pink);
//                }
//                else{
//                    img.setColor(x, y, shallow_pink);
//                }
                float c_r = ofMap(brightness, 0, 255, dark_pink.r, shallow_pink.r);
                float c_g = ofMap(brightness, 0, 255, dark_pink.g, shallow_pink.g);
                float c_b = ofMap(brightness, 0, 255, dark_pink.b, shallow_pink.b);
                img.setColor(x, y, ofColor(c_r, c_g, c_b));
                //img.setColor(x, y, color);;
                
                
                if(brightness<20){
                   // ofSetColor(255, 200, 10);
                    if (y < texture.getHeight()-10){
                        if (x < texture.getWidth()-100){
                            sum_x += x;
                            sum_y += y;
                            countt++;
                        }
                    }
                    
                }
                else{
                    //ofSetColor(10,200,100);
                }
            }
        }
        
        img.update();
        
        avg_x = sum_x/countt;
        avg_y = sum_y/countt;
        
        scale_pos_x = ofMap(avg_x, 50, 341, 503, 1024);
        scale_pos_y = ofMap(avg_y, 50, 315, 0, 424) - 50;
        
        //std::cout << texture.getWidth() << " " << texture.getHeight() << endl;
    }
    
    sky_r = ofMap(scale_pos_y, 0, 424, light_sky.r, dark_sky.r);
    sky_g = ofMap(scale_pos_y, 0, 424, light_sky.g, dark_sky.g);
    sky_b = ofMap(scale_pos_y, 0, 424, light_sky.b, dark_sky.b);
    current_sky = ofColor(sky_r, sky_g, sky_b);
    
    if (scale_pos_x < 1024 and scale_pos_x > 503){
        num_of_star = ofMap(scale_pos_x, 503, 1024, 0, max_num_of_star);
    }
    
    theata += PI/540;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushStyle();
    ofSetColor(current_sky);
    ofDrawRectangle(0, 0, 1024, 424);
    ofPopStyle();
    
    ofPushStyle();
    for(int i = 0; i < num_of_star; i++){
        ofSetColor(255, sin(theata*i/TWO_PI)*255);
        ofFill();
        ofDrawCircle(star_x[i], star_y[i], 2);
    }
    ofPopStyle();
    

    ofEnableLighting();
    ofEnableDepthTest();
    sunlight.enable();
    
    ofPushMatrix();
    ofTranslate(600, 350, 0);
    ofRotateDeg(180);
    float scale = model.getNormalizedScale();
    ofScale(scale/1.3, scale/3.7, scale);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(800, 400, 0);
    ofRotateDeg(180);
    ofScale(scale/1.3, scale/4, scale);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    ofPopMatrix();
    ofPushMatrix();
    ofTranslate(990, 400, 60);
    ofRotateDeg(180);
    ofScale(scale, scale/3.5, scale/3);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    sunlight.disable();
    ofDisableDepthTest();
    ofDisableLighting();
    
    img.draw(0,0, 521,424);
    
//    ofPushStyle();
//    ofSetColor(255, 0, 0);
//    ofFill();
//    ofTranslate(0, -50);
//    ofDrawCircle(scale_pos_x, scale_pos_y, 10);
//    ofNoFill();
//    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp:: exit(){
    kinect.close();
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

