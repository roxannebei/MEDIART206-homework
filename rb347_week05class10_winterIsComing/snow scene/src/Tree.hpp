//
//  Tree.hpp
//  snow scene
//
//  Created by Rongqi Bei on 2020/11/27.
//

#pragma once
#include "ofMain.h"

class Tree {
    
public:
    
    Tree();
    
    Tree (float pos_x_, float pos_y_, float pos_z_, float h_, float r_);
        
    float pos_x;
    float pos_y;
    float pos_z;
    float h;
    float r;
        
    void display_1(int status);
    void display_2(int status);
    
};
