//
//  Road.hpp
//  rb347_week02class04_actNatural
//
//  Created by Rongqi Bei on 2020/11/6.
//

//#ifndef Road_hpp
//#define Road_hpp
//
//#include <stdio.h>
//
//#endif /* Road_hpp */

#include "ofMain.h"

class Road {
    
public:
    
    Road(ofVec2f pos_, float current_time_, ofVec2f road_dir_);
    
    ofVec2f pos;
    float current_time;
    ofVec2f road_dir;
    
    void display();
    void display_line(ofVec2f v1, ofVec2f v2, ofColor c);
    void display_line1(ofVec2f v1, ofVec2f v2, ofColor c);
    
};
