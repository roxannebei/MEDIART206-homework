//
//  Star.h
//  rb347_week03class05_space
//
//  Created by Rongqi Bei on 2020/11/14.
//

class Star{
    
public:
    
    ofPoint pos, v, a;
    float m;
    float r;
    
    Star(){
        m = ofRandom(1,1.5);
        r = 8*m;
        pos.set(ofRandom(100,400),ofRandom(50,100));
        v.set(1,0);
        a.set(0, 0);
    }
    
    Star(float x, float y){
        m = ofRandom(1,1.5);
        r = 8*m;
        pos.set(x,y);
        v.set(1,0);
        a.set(0, 0);
    }
    
    void applyForce(ofPoint force){
        force /= m;
        a += force;
    }
    
    void update(){
        v += a;
        pos += v;
        a *= 0;
    }
    
    void display(){
        ofSetLineWidth(2);
        ofSetColor(255,170);
        ofDrawCircle(pos.x, pos.y, r);
    }
    
};
