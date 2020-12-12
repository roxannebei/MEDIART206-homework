#pragma once

#include "ofMain.h"
#include "Plane.hpp"
#include "ofxAssimpModelLoader.h"
#include "Snow.hpp"
#include "Flower.hpp"
#include "ofxKinectV2.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    ofEasyCam camera;
    Plane lake;
    
    ofxAssimpModelLoader cottage;
    vector<ofMesh> cottage_orig_mesh;
    vector<ofMesh> cottage_meshes;
    vector<ofMaterial> cottage_materials;
    vector<ofTexture> cottage_textures;
    
    ofxAssimpModelLoader mountain;
    vector<ofMesh> mountain_orig_mesh;
    vector<ofMesh> mountain_meshes;
    vector<ofMaterial> mountain_materials;
    vector<ofTexture> mountain_textures;
    
    ofxAssimpModelLoader farm;
    
//    ofxAssimpModelLoader model;
//
//    vector<ofMesh> orig_mesh;
//    vector<ofMesh> meshes;
//    vector<ofMaterial> materials;
//    vector<ofTexture> textures;
    
    ofLight sunlight;
    ofLight cottage_color_light;

    
    ofColor get_current_color(float current_time, float min_time, float max_time, ofColor c_bgn, ofColor c_end);
    
    ofLight farm_light;
    
    ofxKinectV2 kinect;
    ofTexture texture;
    ofImage img;
    void exit();
    
    ofVideoGrabber cam;
    ofxCv::ObjectFinder finder;
    
    
};

