//
//  Attractor.hpp
//  rb347_w*eek03class05_space
//
//  Created by Rongqi Bei on 2020/11/14.
//

class Planet{
    
public:
    
    float m;
    ofPoint pos;
    
    bool dragging = false;
    bool hovering = false;
    ofPoint drag_offset;
    float r = 2*m;
    
    Planet(){
        pos.set(ofRandom(200, ofGetWidth()/2-200), ofRandom(100, ofGetHeight()/2-100));
        m = ofRandom(15, 30);
        drag_offset.set(0, 0);
    }
    
    ofPoint attract(Star star){
        ofPoint force;
        force.set(pos);
        force -= star.pos;
        float d = force.length();
        d = ofClamp(d, 5.0, 25.0);
        force.normalize();
        float strength = (0.3 * m * star.m) / (d * d);     
        force *= strength;
        return force;
    }
    
    
    void display() {
        if (dragging) ofSetColor(255-50);
        else if (hovering) ofSetColor(255-100);
        else ofSetColor(200, 190);
        ofDrawCircle(pos.x, pos.y, r);
    }
    
    void clicked(float mouse_x, float mouse_y){
        ofPoint mouse_pos;
        ofPoint target_pos;
        mouse_pos.set(mouse_x, mouse_y);
        target_pos.set(pos.x, pos.y);
        target_pos -= mouse_pos;
        float distance = target_pos.length();
        if (distance < r){
            dragging = true;
            drag_offset.x = pos.x - mouse_x;
            drag_offset.y = pos.y - mouse_y;
        }
    }
    
    void hover(float mouse_x, float mouse_y){
        ofPoint mouse_pos;
        ofPoint target_pos;
        mouse_pos.set(mouse_x, mouse_y);
        target_pos.set(pos.x, pos.y);
        target_pos -= mouse_pos;
        float distance = target_pos.length();
        if (distance < r){
            hovering = true;
        }
        else{
            hovering = false;
        }
    }
    
    void stop_dragging(){
        dragging = false;
    }
    
    void drag(){
        if (dragging){
            pos.x = ofGetMouseX() + drag_offset.x;
            pos.y = ofGetMouseY() + drag_offset.y;
        }
    }
    
    
    
    
};
