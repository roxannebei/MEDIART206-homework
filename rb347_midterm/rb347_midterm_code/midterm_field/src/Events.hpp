//
//  Events.hpp
//  lamp_3D
//
//  Created by Rongqi Bei on 2020/11/21.
//

#include "ofMain.h"

class Events{
    
public:
    
    Events(int shape_, int v);
    
    int shape;
    int v;
    ofVec3f pos;
    ofVec2f moving_dir;
    float w;
    float h;
    ofColor random_red;
    ofColor random_blue;
    ofColor constant_c;
    ofColor cons_red;
    ofColor cons_blue;
    
    void update();
    void display();
    
    ofVec2f center_start;
    float speed_coeff;
    int random;
    
    
};



