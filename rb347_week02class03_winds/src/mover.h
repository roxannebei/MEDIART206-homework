//
//  mover.h
//  rb347_week02class03_winds
//
//  Created by Rongqi Bei on 2020/11/4.
//

//#ifndef mover_hpp
//#define mover_hpp

//#include <stdio.h>
#include "ofMain.h"

//#endif /* mover_hpp */

class mover{

public:
    mover(float x, float y, float m, float v_x, float v_y, ofColor c_);
    void applyForce(ofPoint F);
    void update();
    void display();
    void checkEdges();
    void collision(mover anotherMover);
    
    ofPoint loc;
    ofPoint v;
    ofPoint a;
    float mass;
    ofColor c;
    
    
};
