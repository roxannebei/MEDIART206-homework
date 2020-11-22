//
//  Field.hpp
//  midterm_field
//
//  Created by Rongqi Bei on 2020/11/22.
//

#pragma once
#include "ofMain.h"

class Field{
    
public:
    
    Field();
    ~Field(){}
    
    Field(float w_, float h_, float res_);
    
    void init_force(float k);
    ofVec3f get_force_at(ofVec3f pos);
    
    vector<ofVec3f> field_element;
    
    int num_of_col;
    int num_of_row;
    
    float w;
    float h;
    float res;
    
    
};
