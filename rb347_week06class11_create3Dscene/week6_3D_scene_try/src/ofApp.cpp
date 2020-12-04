#include "ofApp.h"

float scale = 1.0;
glm::vec3 pos = glm::vec3 (0, -460, 80);


//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofBackground(50);
    
    mesh.setup(800, 800, 100, 100);
    mesh.noise_scale = glm::vec2(0.006, 0.017);
    mesh.noise_freq = 0.5;
    mesh.noise_amp = 28;
    mesh.top_color = ofColor(41, 49, 201);
    mesh.down_color = ofColor(190, 231, 255);
    
    mesh.update_noise();
    mesh.update_color();
    
    model.loadModel("mountain/mountain.obj");
    cloud.loadModel("low_poly_cloud_v1.stl");
    
    for (int i = 0; i < model.getMeshCount(); i++)
    {
        orig_mesh.push_back(model.getMesh(i));
        materials.push_back(model.getMaterialForMesh(i));
        textures.push_back(model.getTextureForMesh(i));
    }
    
    meshes = orig_mesh;
    
    ofSetSmoothLighting(true);
    
    sunlight.setDirectional();
    sunlight.setPosition(-400, -200, -500);
    sunlight.lookAt(glm::vec3(0));
    sunlight.setDiffuseColor(ofColor::antiqueWhite);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    mesh.update_noise();
    mesh.update_color();
    
    mesh.setPosition(pos);
    mesh.setScale(scale);
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofColor center, bg;
    center = ofColor(255, 218, 185);
//    bg = ofColor(255, 222, 173);
    bg = ofColor(255, 228, 196);
    ofBackgroundGradient(center, bg);
    
    ofEnableLighting();
    
    camera.begin();
    ofEnableDepthTest();
    
    sunlight.enable();
    
    // --------------------------------------- mountain 0 ----------
    ofPushMatrix();
    ofTranslate(-390, -80, -110);
    
    float scale = model.getNormalizedScale();
    ofScale(scale/1.3, scale/3.7, scale);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 1 ----------
    ofPushMatrix();
    ofTranslate(-360, -80, -100);
    
    ofScale(scale/1.3, scale/3.7, scale);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 2 ----------
    ofPushMatrix();
    ofTranslate(-150, -100, -50);

    ofScale(scale, scale/5, scale/1.5);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 3 ----------
    ofPushMatrix();
    ofTranslate(100, -100, 30);

    ofScale(scale, scale/4.5, scale/2);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 4 ----------
    ofPushMatrix();
    ofTranslate(150, -100, 30);

    ofScale(scale, scale/4.5, scale/2);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 5 ----------
    ofPushMatrix();
    ofTranslate(350, -100, 30);

    ofScale(scale/1.1, scale/2.8, scale/1.5);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- rock ----------
    ofPushMatrix();
    ofTranslate(-95, -135, 120);
    //float scale1 = model.getNormalizedScale();
    ofScale(scale/1.2, scale/4.5, scale/3);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- rock2 ----------
    ofPushMatrix();
    ofTranslate(180, -150, 250);
    //float scale1 = model.getNormalizedScale();
    ofScale(scale/1.2, scale/4.5, scale/4.5);
    
    for (int i = 0; i < meshes.size(); i++){
        
        textures[i].bind();
        meshes[i].draw();
        textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- lighthouse ----------
    
    ofPushStyle();

    ofSetColor(255, 255, 255);
    ofFill();
    ofCylinderPrimitive lighthouse_body;
    lighthouse_body = ofCylinderPrimitive(5, 200, 200, 200);
    ofVec3f lighthouse_pos;
    lighthouse_pos.set(-95, -10, 145);
    lighthouse_body.setPosition(lighthouse_pos);
    lighthouse_body.draw();
    //ofDrawCylinder(lighthouse_pos.x, lighthouse_pos.y-25, lighthouse_pos.z, 8, 70);
    ofDrawBox(lighthouse_pos.x, lighthouse_pos.y-25, lighthouse_pos.z, 10, 70, 10);
    ofPushMatrix();
    ofRotateDeg(180);
    ofDrawCone(-lighthouse_pos.x, 200, lighthouse_pos.z, 8, 15);
    ofPopMatrix();
    
    ofSetColor(205,55, 0);
    ofFill();
    ofDrawSphere(lighthouse_pos.x, lighthouse_pos.y+95, lighthouse_pos.z, 7.5);
    ofDrawCylinder(lighthouse_pos.x, lighthouse_pos.y+70, lighthouse_pos.z, 7, 15);
    ofDrawCylinder(lighthouse_pos.x, lighthouse_pos.y+40, lighthouse_pos.z, 7, 15);
    
    ofPopStyle();
    
    ofPushMatrix();
    cloud.setPosition(180, 100, 100);
    cloud.drawWireframe();
    ofPopMatrix();
    
    sunlight.disable();
    ofDisableLighting();
    
    // --------------------------------------- sea ----------
    ofPushMatrix();
    ofRotateDeg(180, 0, -95, 100);
    mesh.draw();
    ofPopMatrix();

    
    sunlight.draw();
    ofDisableDepthTest();
    camera.end();
    

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
