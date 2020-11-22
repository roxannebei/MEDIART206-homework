//
//  Light.hpp
//  lamp_3D
//
//  Created by Rongqi Bei on 2020/11/19.
//

#include "ofMain.h"

class Light{
    
public:
    Light(ofVec3f pos_, ofVec2f moving_dir_);
    
    ofVec3f pos;
    ofVec2f moving_dir;
    
    float c;
    
    
    void update_light();
    void update_light_left();
    
    void display();
    void display_left();
    
};



