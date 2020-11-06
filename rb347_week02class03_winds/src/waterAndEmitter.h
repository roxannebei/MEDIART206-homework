//
//  water.hpp
//  rb347_week02class03_winds
//
//  Created by Rongqi Bei on 2020/11/5.
//

//#ifndef water_hpp
//#define water_hpp
//
//#include <stdio.h>
//
//#endif /* water_hpp */

#include "ofMain.h"
#include "mover.h"

class water{
    
public:
    
    void setup(float x_, float y_, float w_, float h_, float coeff_);
    bool contains(mover m);
    ofPoint drag(mover m);
    void display();
    
    float x, y, w, h;
    float coeff;
};

class emitter{
    
public:
    
    void setup(float x_, float y_, float w_, float h_, ofColor c1_, ofColor c2_);
    bool contains(mover m);
    ofPoint get_drag_force(mover m);
    ofPoint get_push_force(mover m);
    void display(ofColor drag_c, ofColor hover_c);
    void display_light();
    void clicked(float cursor_x, float cursor_y);
    void hover(float cursor_x, float cursor_y);
    void drag();
    void stop_dragging();
    
    
    float x;
    float y;
    float w;
    float h;
    ofColor c1;
    ofColor c2;
    
    bool dragging = false;
    bool hovering = false;
    ofPoint drag_offset;
    
};
