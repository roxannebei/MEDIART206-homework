//
//  Flower.cpp
//  final_scene_create_try3
//
//  Created by Rongqi Bei on 2020/12/11.
//

#include "Flower.hpp"


Flower::Flower(){
    
    pos = glm::vec3(0, 0, 0);
    size = 5;
}

Flower::Flower(glm::vec3 pos_, float size_){
    
    pos = pos_;
    size = size_;
    random = ofRandom(1,4);
    
//    vector<ofColor> day_color;
//    vector<ofColor> night_color;
//
//    ofColor d_c1 = ofColor(255, 228, 225);
//    ofColor n_c1 = ofColor(205, 155, 155);
//
//    day_color.push_back(d_c1);
//    night_color.push_back(n_c1);
}

ofColor Flower::get_current_color(float current_time, float min_time, float max_time, ofColor c_bgn, ofColor c_end){
    ofColor current_color;
    current_color.r = ofMap(current_time, min_time, max_time, c_bgn.r, c_end.r);
    current_color.g = ofMap(current_time, min_time, max_time, c_bgn.g, c_end.g);
    current_color.b = ofMap(current_time, min_time, max_time, c_bgn.b, c_end.b);
    return current_color;
}

void Flower::display(float theata, int time_status, ofColor c_d, ofColor c_n, float count_day){
    int len_day = 10;
    int len_night = 10;
    int trans_day_night = 6;
    float len_total_day = len_day + len_night + 2*trans_day_night;
    
    ofColor flower_c;
    if (time_status == 1){
        flower_c = c_d;
    }
    if (time_status == 3){
        flower_c = c_n;
    }
    if (time_status == 2){
        flower_c = get_current_color(count_day,len_day, len_day+trans_day_night, c_d, c_n);
    }
    if (time_status == 4){
        flower_c = get_current_color(count_day,len_day+len_night+trans_day_night, len_total_day, c_n, c_d); 
    }
    
    ofPushMatrix();
    ofPushStyle();
    ofSetColor(flower_c);
    ofFill();
    float d = 0.7*size;
    //float r = size + abs(sin(theata)*size/3);
    float r = size+size/6;
    ofDrawSphere(pos.x-d, pos.y, pos.z-d, r);
    ofDrawSphere(pos.x+d, pos.y, pos.z-d, r);
    ofDrawSphere(pos.x-d, pos.y, pos.z+d, r);
    ofDrawSphere(pos.x+d, pos.y, pos.z+d, r);
    ofDrawSphere(pos.x, pos.y+d*1.5, pos.z, r);
    ofSetColor(139, 69, 19);
    ofDrawCylinder(pos.x, pos.y-size, pos.z, 1, size*4);
    ofPopStyle();
    ofPopMatrix();
}
