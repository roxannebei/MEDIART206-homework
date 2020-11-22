//
//  Road.hpp
//  midterm_adjust_speed
//
//  Created by Rongqi Bei on 2020/11/14.
//

#include "ofMain.h"

class Road {
    
public:
    
    Road(ofVec2f pos_, float current_time_, ofVec2f road_dir_);
    
    ofVec2f pos;
    float current_time;
    ofVec2f road_dir;
    
    void display(int v);
    void display_sign(int v);
    
};




