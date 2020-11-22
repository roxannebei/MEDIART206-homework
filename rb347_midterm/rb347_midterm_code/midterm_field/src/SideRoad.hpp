//
//  SideRoad.hpp
//  midterm_adjust_speed
//
//  Created by Rongqi Bei on 2020/11/15.
//

#include "ofMain.h"

class SideRoad {
    
public:
    
    SideRoad(ofVec2f start_, ofVec2f road_dir1_, ofVec2f road_dir2_, float current_time_);
    
    ofVec2f start;
    ofVec2f road_dir1;
    ofVec2f road_dir2;
    float current_time;
    
    void display(int v);
    
};




