#pragma once

#include "ofMain.h"
#include "Plane.hpp"
#include "ofxAssimpModelLoader.h"

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
    
    Plane mesh;
    
    ofxAssimpModelLoader model;
    ofxAssimpModelLoader cloud;
    
    vector<ofMesh> orig_mesh;
    vector<ofMesh> meshes;
    vector<ofMaterial> materials;
    vector<ofTexture> textures;
    
    ofLight sunlight;
    
    //ofParameter<float> scale;
    //ofParameter<glm::vec3> pos;
    

};
