//
//  Plane.cpp
//  week6_3D_scene_try
//
//  Created by Rongqi Bei on 2020/12/4.
//

#include "Plane.hpp"

Plane::Plane(){
    
}

void Plane::setup(float width, float height, float num_of_col, float num_of_row){
    
    for (int r = 0; r < num_of_row; r++){
        for (int c = 0; c < num_of_col; c++){
            
            glm::vec3 pos;
            
            pos.x = ofMap(r, 0, num_of_row-1, -width/2, width/2);
            pos.y = ofMap(c, 0, num_of_col-1, -height/2, height/2);
            pos.z = 0;
            
            mesh.addVertex(pos);
            mesh.addColor(ofColor());
            
            if (r < num_of_row-1 and c < num_of_col-1){
                
                int index = r * num_of_col + c;
                
                mesh.addIndex(index);
                mesh.addIndex(index + 1);
                mesh.addIndex(index + num_of_col);
                
                mesh.addIndex(index + 1);
                mesh.addIndex(index + 1 + num_of_col);
                mesh.addIndex(index + num_of_col);
            }
        }
    }
    vertex_radius = 1.f;
}

void Plane::update_noise(){
    
    for (int i = 0; i < mesh.getVertices().size(); i++){
        
        glm::vec3 &vertex = mesh.getVertices()[i];
        
        float noise_x = vertex.x * noise_scale.x;
        float noise_y = vertex.y * noise_scale.y;
        float noise_z = ofGetElapsedTimef() * noise_freq;
        float noise = ofSignedNoise(noise_x, noise_y, noise_z);
        
        vertex.z = noise * noise_amp;
    }
}

void Plane::update_color(){
    
    for (int i = 0; i < mesh.getVertices().size(); i++){
        
        glm::vec3 & vertex = mesh.getVertices()[i];
        
        float depth_percent = ofMap(vertex.z, -noise_amp, noise_amp, 0, 1, true);
        ofColor color = down_color.getLerped(top_color, depth_percent);
        //ofColor color = (255, 0, 0);
        mesh.setColor(i, color); 
    
    }
}

void Plane::draw(){
    
    ofPushMatrix();
    
    ofTranslate(getPosition());
    ofScale(getScale());
    mesh.draw();
    ofPopMatrix();
}


