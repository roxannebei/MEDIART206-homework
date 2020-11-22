//
//  SideRoad.cpp
//  midterm_adjust_speed
//
//  Created by Rongqi Bei on 2020/11/15.
//

#include "SideRoad.hpp"

SideRoad::SideRoad(ofVec2f start_, ofVec2f road_dir1_, ofVec2f road_dir2_, float current_time_){
    start = start_;
    road_dir1 = road_dir1_;
    road_dir2 = road_dir2_;
    current_time = current_time_;
}

void SideRoad::display(int v){
    
    if (v == 1){
        float time = (ofGetElapsedTimef()-current_time)*2;
        
        int c1 = 30;
        int c2 = 31;
        
        float x1 = start.x + (time - 4)*(time - 4)*c1/50*road_dir1.x;
        float y1 = start.y + (time - 4)*(time - 4)*c1/50*road_dir1.y;
        float x2 = start.x + (time - 4)*(time - 4)*c2/50*road_dir1.x;
        float y2 = start.y + (time - 4)*(time - 4)*c2/50*road_dir1.y;
        
        ofSetColor(205, 170, 125);
        ofFill();
        ofBeginShape();
        ofVertex(x1, y1);
        ofVertex(x2, y2);
        ofVertex(x2, y2+200);
        ofVertex(x1, y1+200);
        ofVertex(x1, y1);
        ofEndShape();
    }
    
    if (v == 2){
    
        float time = (ofGetElapsedTimef()-current_time)*2;
    
        int c1 = 30;
        int c2 = 31;
    
        float x1 = start.x + (time - 4)*(time - 4)*c1/30*road_dir1.x;
        float y1 = start.y + (time - 4)*(time - 4)*c1/30*road_dir1.y;
        float x2 = start.x + (time - 4)*(time - 4)*c2/30*road_dir1.x;
        float y2 = start.y + (time - 4)*(time - 4)*c2/30*road_dir1.y;
    
        ofSetColor(205, 170, 125);
        ofFill();
        ofBeginShape();
        ofVertex(x1, y1);
        ofVertex(x2, y2);
        ofVertex(x2, y2+200);
        ofVertex(x1, y1+200);
        ofVertex(x1, y1);
        ofEndShape();
    }
    
    if (v == 3){
        float time = (ofGetElapsedTimef()-current_time)*2;
        
        int c1 = 30;
        int c2 = 31;
        
        float x1 = start.x + (time - 4)*(time - 4)*c1/15*road_dir1.x;
        float y1 = start.y + (time - 4)*(time - 4)*c1/15*road_dir1.y;
        float x2 = start.x + (time - 4)*(time - 4)*c2/15*road_dir1.x;
        float y2 = start.y + (time - 4)*(time - 4)*c2/15*road_dir1.y;
        
        ofSetColor(205, 170, 125);
        ofFill();
        ofBeginShape();
        ofVertex(x1, y1);
        ofVertex(x2, y2);
        ofVertex(x2, y2+200);
        ofVertex(x1, y1+200);
        ofVertex(x1, y1);
        ofEndShape();
    }
    
}




