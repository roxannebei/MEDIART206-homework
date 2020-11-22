//
//  Field.cpp
//  midterm_field
//
//  Created by Rongqi Bei on 2020/11/22.
//

#include "Field.hpp"

Field::Field(){
    
}

Field::Field(float w_, float h_, float res_){
    
    w = w_;
    h = h_;
    res = res_;
    
    num_of_col = w/res + 1;
    num_of_row = h/res + 1;
    
    int total_points = num_of_row*num_of_col;
    
    for (int i = 0; i < total_points; i++){
        ofVec3f force_point;
        field_element.push_back(force_point);
    }
}

void Field::init_force(float k){
    
    for (int y = 0; y < num_of_row; y++){
        for (int x = 0; x < num_of_col; x++){
            
            int i = (y*num_of_col)+x;
            
            ofVec3f noise_pos;
            noise_pos.x = x * 0.1;
            noise_pos.y = y * 0.1;
            noise_pos.z = ofGetElapsedTimef() * k;
            float noise = ofNoise(noise_pos);
            
            noise = ofMap(noise, 0, 1, PI/1.5, PI);
            ofVec2f force = ofVec2f(cos(noise), sin(noise));
            force.scale(k);
            field_element[i].set(force);
        }
    }
}

ofVec3f Field::get_force_at(ofVec3f pos){
    
    ofVec3f force;
    force.set(0, 0);
    
    if (pos.x < 0 or pos.x > w or pos.y < 0 or pos.y > h){ 
        return force;
    }
    
    int x_index = ofMap(pos.x, 0, w, 0, num_of_col);
    int y_index = ofMap(pos.y, 0, h, 0, num_of_row);
    
    int idx = y_index * num_of_col + x_index;
    force = field_element[idx];
    return force;
}
