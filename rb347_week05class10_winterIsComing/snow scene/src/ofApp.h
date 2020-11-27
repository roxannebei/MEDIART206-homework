#pragma once

#include "ofMain.h"
#include "Box.hpp"
#include "Snow.hpp"
#include "Tree.hpp"

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
    Box box;
    vector<Snow> snow_list;
    
    ofBoxPrimitive BOX;
    
    ofLight sun;
    ofLight sun1;
    ofLight lake_light;
    ofLight clock_light;
    
    float set(float x, int t);
		
}; 

