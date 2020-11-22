#include "ofApp.h"

ofVec2f start_road;
ofVec2f end_road;
ofVec2f road_dir;

int copy_centerR1 = 1;
int copy_centerR2 = 0;
float ct_centerR; // current time center road
bool create_centerR;
vector<Road> centerR_vector;

ofVec2f rightR_up;
ofVec2f rightR_down;
ofVec2f rightR_dirUp;
ofVec2f rightR_dirDown;
vector<SideRoad> rightSR_vector;

float tree_theata;

ofVec2f end_light;
ofVec2f light_dir;
vector<Light> light_vector;
ofVec3f position;

int create_light = 0;

ofVec2f end_sign;
ofVec2f sign_dir;
vector<Road> sign_vector;
vector<Road> sign_vector1;
bool create_sign;
int copy_sign1 = 1;
int copy_sign2 = 0;
float ct_sign;

ofVec2f left_sr;
ofVec2f leftSR_dir;
vector<SideRoad> leftSR_vector;

ofVec2f end_light_left;
ofVec2f left_light_dir;
vector<Light> left_light_vector;
ofVec3f position_left;

vector<Events> event_vector;

float sun_theata;
float sun_theata_r;
bool create_sun;
float sunny_day;

vector<float> stars_x;
vector<float> stars_y;
float star_theata;
int total_stars = 60;
float having_stars = 90;

bool create_firework1 = true;
bool create_firework2 = true;
bool create_firework3 = true;

bool create_rainbow;


int v = 1;
int scope = 1;

int field_h = 350;

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofEnableSmoothing();
    ofSetCircleResolution(200);
    
    start_road.set(500, 350);
    end_road.set(750, 700);
    road_dir = end_road-start_road;
    road_dir.normalize();
    
    end_light.set(1300, 150);
    light_dir = end_light - start_road;
    light_dir.normalize();
    
    
    position.set(start_road.x-200, start_road.y-50,  -1000);
    
    
    rightR_up.set(1300, 430);
    rightR_down.set(1300, 555);
    rightR_dirUp = (rightR_up-start_road).normalize();
    rightR_dirDown = (rightR_down-start_road).normalize();
    
    end_sign.set(20, 700);
    sign_dir = end_sign-start_road;
    sign_dir.normalize();
    
    left_sr.set(0, 490);
    leftSR_dir = (left_sr-start_road).normalize();
    
    end_light_left.set(0, 300);
    position_left.set(start_road.x-300, start_road.y-30, -1000);
    left_light_dir = end_light_left - start_road;
    left_light_dir.normalize();
    
    for (int i = 0; i<total_stars; i++){
        stars_x.push_back(ofRandom(ofGetWidth()-15));
        stars_y.push_back(ofRandom(15, 380));
    }
    
    // ------------- fire work
//    glm::vec2 pos = glm::vec2(-ofGetWidth()/2, -ofGetHeight()/2);
//    ParticleSystem p_system = ParticleSystem(pos);
    //particleSystems.push_back(p_system);
    
    for (int i = 0; i < particleSystems.size(); i++){
        particleSystems[i].setup();
    }
    
    gravity = glm::vec2(0, 0.0005);
    
    

}

void ofApp::meteor_update(){
    
    meteor_field = Field(ofGetWidth(), field_h, 20);
    meteor_field.init_force(0.07);

    for (int i = 0; i < 3+int(ofGetElapsedTimef())%6; i++){
        Meteor m;
        m.pos.x = ofRandom(0, ofGetWidth());
        m.pos.y = ofRandom(-100, field_h-200);

        meteors.push_back(m);

    }
    
    damping = 0.05;
}
    


//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < meteors.size(); i++){
        ofVec3f force = meteor_field.get_force_at(meteors[i].pos);
        meteors[i].apply_force(force);
        meteors[i].apply_damping(damping);
        meteors[i].update();
    }
    
    float hue = min(fmodf(ofGetElapsedTimef()*5, 510), 510-fmodf(ofGetElapsedTimef()*5, 510));
    float fake_hue = fmodf(ofGetElapsedTimef()*5, 510);
    
    
    if (copy_centerR1 != copy_centerR2){
        ct_centerR = ofGetElapsedTimef();
        copy_centerR2++;
    }
    
    if (copy_sign1 != copy_sign2){
        ct_sign = ofGetElapsedTimef();
        copy_sign2++;
    }
    

    if (v == 1){
        if (mysch.counter%4 == 1 and create_centerR){
            copy_centerR1++;
            Road *road = new Road (start_road, ct_centerR, road_dir);
            SideRoad *sr = new SideRoad (start_road, rightR_dirUp, rightR_dirDown, ct_centerR);
            centerR_vector.push_back(*road);
            rightSR_vector.push_back(*sr);
    
            create_light++;
            if (create_light % 2 == 0){
                Light *l = new Light(position, light_dir);
                light_vector.push_back(*l);
            }
    
            if (create_light %2 == 1){
                Light *left_light = new Light(position_left, left_light_dir);
                left_light_vector.push_back(*left_light);
            }
    
            Road *sign = new Road(start_road, ct_centerR, sign_dir);
            sign_vector.push_back(*sign);
    
            SideRoad *lsr = new SideRoad (start_road, leftSR_dir, leftSR_dir, ct_centerR);
            leftSR_vector.push_back(*lsr);
            create_centerR = false;
        }
        if (mysch.counter%4 == 0){
            create_centerR = true;
        }
        if (mysch.counter%4 == 3 and create_sign){
            copy_sign1++;
            Road *sign = new Road(start_road, ct_sign, sign_dir);
            sign_vector1.push_back(*sign);
            create_sign = false;
        }
        if (mysch.counter%4 == 1){
            create_sign = true;
        }
        
        // ------------ v = 1 events
        
        int random_number;
        random_number = ofRandom(350);
        if (random_number < 3){
            Events *e = new Events(1, v);
            event_vector.push_back(*e);
        }
        
    }

    
    if (v == 2){
        if (int(ofGetElapsedTimef())%2 == 1 and create_centerR){
            copy_centerR1++;
            Road *road = new Road (start_road, ct_centerR, road_dir);
            SideRoad *sr = new SideRoad (start_road, rightR_dirUp, rightR_dirDown, ct_centerR);
            centerR_vector.push_back(*road);
            rightSR_vector.push_back(*sr);
        
            create_light++;
            if (create_light % 2 == 0){
                Light *l = new Light(position, light_dir);
                light_vector.push_back(*l);
            }
        
            if (create_light %2 == 1){
                Light *left_light = new Light(position_left, left_light_dir);
                left_light_vector.push_back(*left_light);
            }
        
            Road *sign = new Road(start_road, ct_centerR, sign_dir);
            sign_vector.push_back(*sign);
        
            SideRoad *lsr = new SideRoad (start_road, leftSR_dir, leftSR_dir, ct_centerR);
            leftSR_vector.push_back(*lsr);
    
            create_centerR = false;
        }
        
        if (int(ofGetElapsedTimef())%2 == 0){
            create_centerR = true;
        }
        if (int(ofGetElapsedTimef())%2 == 0 and create_sign){
            copy_sign1++;
            Road *sign = new Road(start_road, ct_sign, sign_dir);
            sign_vector1.push_back(*sign);
            create_sign = false;
        }
        if (int(ofGetElapsedTimef())%2 == 1){
            create_sign = true;
        }
        
        // ------------ v = 2 events
        
        int random_number;
        random_number = ofRandom(350);
        if (random_number < 3){
            Events *e = new Events(1, v);
            event_vector.push_back(*e);
        }
    }


    if (v == 3){
        
        if (mysch.counter%2 == 1 and create_centerR){
            copy_centerR1++;
            Road *road = new Road (start_road, ct_centerR, road_dir);
            SideRoad *sr = new SideRoad (start_road, rightR_dirUp, rightR_dirDown, ct_centerR);
            centerR_vector.push_back(*road);
            rightSR_vector.push_back(*sr);
    
            create_light++;
            if (create_light % 2 == 0){
                Light *l = new Light(position, light_dir);
                light_vector.push_back(*l);
            }
    
            if (create_light %2 == 1){
                Light *left_light = new Light(position_left, left_light_dir);
                left_light_vector.push_back(*left_light);
            }
    
            Road *sign = new Road(start_road, ct_centerR, sign_dir);
            sign_vector.push_back(*sign);
    
            SideRoad *lsr = new SideRoad (start_road, leftSR_dir, leftSR_dir, ct_centerR);
            leftSR_vector.push_back(*lsr);
            create_centerR = false;

        }
        if (mysch.counter%2 == 0){
            create_centerR = true;
        }
        if (mysch.counter%2 == 0 and create_sign){
            copy_sign1++;
            Road *sign = new Road(start_road, ct_sign, sign_dir);
            sign_vector1.push_back(*sign);
            create_sign = false;
        }
        if (mysch.counter%2 == 1){
            create_sign = true;
        }
        
        // ------------ v = 3 events
        
        int random_number;
        random_number = ofRandom(350);
        if (random_number < 3){
            Events *e = new Events(1, v);
            event_vector.push_back(*e);
        }
        
    }
    
    tree_theata += PI/90;
    
    
// ------------- firework
    while (particleSystems.size() > 3)     // keep the number of particles under a limit
    {
        particleSystems.erase(particleSystems.begin());     // erase the oldest particle
    }
 
}



//--------------------------------------------------------------
void ofApp::draw(){
    
    float hue = min(fmodf(ofGetElapsedTimef()*5, 510), 510-fmodf(ofGetElapsedTimef()*5, 510));
    float fake_hue = fmodf(ofGetElapsedTimef()*5, 510);
    
    //ofSetColor(ofMap(hue, 0, 255, 130, 135), ofMap(hue, 0, 255, 191, 206), ofMap(hue, 0, 255, 220, 255));
    float sky_r = ofMap(hue, 0, 255, 54, 170);
    float sky_g = ofMap(hue, 0, 255, 80, 220);
    float sky_b = ofMap(hue, 0, 255, 120, 255);
    
    ofSetColor(sky_r, sky_g, sky_b);
    ofFill();
    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
    ofNoFill();
    
    if (v == 1){
        sun_theata_r += PI/80;
        star_theata += PI/180;
    
        if (hue > 133 and sunny_day > 40){
            create_sun = true;
        }
        if (hue > 133 and sunny_day < 40){
            create_rainbow = true;
        }
        if (hue <= 133){
            create_sun = false;
            create_rainbow = false;
            sunny_day = ofRandom(100);
        }
        if (create_sun){
            sun_theata = (fake_hue-140)/230*2.3+3.5;
            ofSetColor(255, 114, 86);
            ofFill();
            ofDrawCircle(660+560*cos(sun_theata), 730+560*sin(sun_theata), 145+5*sin(sun_theata_r));
            ofNoFill();
        }
        if (create_rainbow){
            
            float alpha;
            alpha = ofMap(hue, 133, 255, 0, 255) * (0.9+ofNoise(1));
            
            ofPushStyle();
            //ofSetColor(123, 104, 238);
            ofSetColor(146, 132, 228, alpha-50);
            ofFill();
            ofDrawEllipse(600, 460, 1047, 718);
            
            
            ofSetColor(sky_r, sky_g, sky_b);
            ofFill();
            ofDrawEllipse(600, 460, 977, 658);
            //ofSetColor(76, 216, 158);
            ofSetColor(113, 225, 176, alpha-40);
            ofFill();
            ofDrawEllipse(600, 460, 977, 658);
            //ofSetColor(255, 215, 0);
            
            ofSetColor(sky_r, sky_g, sky_b);
            ofFill();
            ofDrawEllipse(600, 460, 907, 598);
            ofSetColor(237, 209, 81, alpha-30);
            ofFill();
            ofDrawEllipse(600, 460, 907, 598);
            
            ofSetColor(sky_r, sky_g, sky_b);
            ofFill();
            ofDrawEllipse(600, 460, 837, 538);
            //ofSetColor(255, 140, 0);
            ofSetColor(249, 165, 66, alpha-20);
            ofFill();
            ofDrawEllipse(600, 460, 837, 538);
            
            ofSetColor(sky_r, sky_g, sky_b);
            ofFill();
            ofDrawEllipse(600, 460, 767, 478);
            //ofSetColor(255, 48, 48);
            ofSetColor(241, 83, 83, alpha-10);
            ofFill();
            ofDrawEllipse(600, 460, 767, 478);
            
            ofSetColor(sky_r, sky_g, sky_b);
            ofFill();
            ofDrawEllipse(600, 460, 697, 418);
            ofPopStyle();
        }
        if (hue > 90){
            having_stars = ofRandom(100);
        }
        if (hue <= 90){
            if (having_stars <= 80){
                int num_of_stars = ofMap(hue, 0, 90, total_stars, 1);
                for (int i = 0; i < num_of_stars; i++){
                    ofSetColor(255, sin(star_theata*i/TWO_PI)*255);
                    ofFill();
                    ofDrawCircle(stars_x[i], stars_y[i], 2);
                    ofNoFill();
                }
            }
            
            if (having_stars >= 40){

                if ((int)ofGetElapsedTimef()%16==0){
                    create_firework1 = true;
                }
                if ((int)ofGetElapsedTimef()%16==3 and create_firework1){
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, 300-100)), 0, 1));
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, 250-100)), 25, 0));
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, 350-100)), 60, 1));
                    setup();
                    meteor_update();
                    create_firework1 = false;
                    create_firework3 = true;
                }
                
                if ((int)ofGetElapsedTimef()%16==8 and create_firework2){
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, 300-100)), 0, 0));
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, 250-100)), 25, 1));
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(200, ofGetWidth()-200),ofRandom(100, 350-100)), 60, 0));
                    setup();
                    meteor_update();
                    create_firework2 = false;
                }
                
                if ((int)ofGetElapsedTimef()%16==13 and create_firework3){
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(300, ofGetWidth()-600),ofRandom(100, 300-100)), 0, 1));
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(300, ofGetWidth()-600),ofRandom(100, 250-100)), 25, 1));
                    particleSystems.push_back(ParticleSystem(glm::vec2(ofRandom(300, ofGetWidth()-600),ofRandom(100, 350-100)), 60, 1));
                    setup();
                    meteor_update();
                    create_firework3 = false;
                    create_firework2 = true;
                }
            }
        }
    
        for (int i=0; i<particleSystems.size(); i++){
            particleSystems[i].applyForce(gravity);
            particleSystems[i].update();
            particleSystems[i].draw();
        }
        
        if (hue >= 20 and hue < 150){
            
            if ((int)ofGetElapsedTimef()%16==0){
                create_firework1 = true;
            }
            if ((int)ofGetElapsedTimef()%16==3 and create_firework1){
                meteor_update();
                create_firework1 = false;
                create_firework3 = true;
            }

            if ((int)ofGetElapsedTimef()%16==8 and create_firework2){
                meteor_update();
                create_firework2 = false;
            }

            if ((int)ofGetElapsedTimef()%16==13 and create_firework3){
                meteor_update();
                create_firework3 = false;
                create_firework2 = true;
            }
        
            for (int i = 0; i < meteors.size(); i++){
                meteors[i].display();
            }
        }
        
    }
    
    if (v == 2){
        sun_theata_r += PI/80;
        star_theata += PI/180;
    
        if (hue > 133){
            create_sun = true;
        }
        if (hue <= 133){
            create_sun = false;
        }
        if (create_sun){
            sun_theata = (fake_hue-140)/230*2.3+3.5;
            ofSetColor(255, 114, 86);
            ofFill();
            ofDrawCircle(660+560*cos(sun_theata), 730+560*sin(sun_theata), 145+5*sin(sun_theata_r));
            ofNoFill();
        }
       
        if (hue <= 90){
            int num_of_stars = ofMap(hue, 0, 90, total_stars, 1);
            for (int i = 0; i < num_of_stars; i++){
                ofSetColor(255, sin(star_theata*i/TWO_PI)*255);
                ofFill();
                ofDrawCircle(stars_x[i], stars_y[i], 2);
                ofNoFill();
            }
        }
    }

    
    float step_size = 10;
    
    if (scope == 2){
        for (int i = 0; i < ofGetWidth()/step_size; i++){
            for (int j = 0; j < (ofGetHeight()*0.7)/step_size; j++){
                ofSetColor(230, ofRandom(50, 80));
                //ofSetColor(0, ofRandom(255), ofRandom(255), ofRandom(10, 50));
                ofFill();
                ofDrawRectangle(i*step_size, j*step_size, step_size, step_size);
                ofNoFill();
            }
        }
    }
    
    
    
    // tree
    
    ofSetColor(60, 179, 113);
    ofFill();
    ofDrawEllipse(532, 400, 50+10*sin(tree_theata), 70+4*sin(tree_theata+PI/8));
    ofDrawEllipse(580, 366, 65+8*cos(tree_theata), 55+10*cos(tree_theata));
    ofDrawEllipse(666, 396, 155+15*sin(tree_theata+PI/4), 150+5*sin(tree_theata));
    ofDrawEllipse(800, 412, 210+8*cos(tree_theata), 200+10*cos(tree_theata+PI/6));
    ofDrawEllipse(901, 405, 140+11*sin(tree_theata+PI/8), 130+6*sin(tree_theata));
    ofDrawEllipse(993, 403, 125+5*cos(tree_theata-PI/4), 140+15*cos(tree_theata));
    ofDrawEllipse(1094, 409, 187+20*sin(tree_theata-PI/8), 200-20*sin(tree_theata));
    ofDrawEllipse(1191, 345, 85+5*cos(tree_theata), 95-8*cos(tree_theata));
    ofDrawEllipse(1247, 455, 230+20*sin(tree_theata+PI/7), 230-10*sin(tree_theata));
    ofDrawEllipse(1273, 365, 130+20*cos(tree_theata), 170+12*cos(tree_theata+PI*4/3));
    ofNoFill();
    
    ofSetColor(75, 134, 75);
    ofFill();
    ofDrawEllipse(886, 441, 75, 60+10*cos(tree_theata));
    ofDrawEllipse(956, 440+10*sin(tree_theata), 105+6*sin(tree_theata), 84);
    ofDrawEllipse(1046, 442+6*cos(tree_theata+PI/4), 110+4*cos(tree_theata-PI/6), 113);
    ofDrawEllipse(1145, 447+8*sin(tree_theata-PI/8), 153+8*sin(tree_theata), 146);
    ofDrawEllipse(1245, 470+5*cos(tree_theata), 175+20*cos(tree_theata+PI/4), 215);
    ofNoFill();
    
    ofSetColor(162, 205, 90);
    ofFill();
    ofDrawEllipse(472, 367, 35+5*sin(tree_theata), 30+3*sin(tree_theata-PI/4));
    ofDrawEllipse(432, 387, 95+5*cos(tree_theata-PI/4), 65+5*cos(tree_theata));
    ofDrawEllipse(362, 419, 95+10*sin(tree_theata+PI/8), 95+8*sin(tree_theata));
    ofDrawEllipse(310, 418, 100+15*cos(tree_theata), 90+8*cos(tree_theata+PI/2));
    ofDrawEllipse(240, 452, 133+8*sin(tree_theata), 129+10*cos(tree_theata-PI/6));
    ofDrawEllipse(183, 454, 100+12*cos(tree_theata+PI/6), 105+14*cos(tree_theata));
    ofDrawEllipse(108, 480+5*cos(tree_theata), 145+5*sin(tree_theata+PI/4), 125+10*sin(tree_theata));
    ofDrawEllipse(3, 500+10*sin(tree_theata+PI/4), 150+10*cos(tree_theata-PI/6), 168+5*cos(tree_theata));
    ofNoFill();
    
    
    for (int i = 0; i < light_vector.size(); i++){
        light_vector[i].display();
    }
    
    for (int i = 0; i < left_light_vector.size(); i++){
        left_light_vector[i].display_left();
    }
    
    for (int i = 1; i < centerR_vector.size(); i++){
        rightSR_vector[i].display(v);
    }
    
    for (int i = 1; i < leftSR_vector.size(); i++){
        leftSR_vector[i].display(v);
    }
    
    ofSetHexColor(0x000000);
    ofSetLineWidth(1.5);
    
    ofSetColor(175);
    ofFill();
    ofDrawTriangle(start_road.x, start_road.y, 75, 700, 160, 700);
    ofDrawTriangle(start_road.x, start_road.y, 1300, 550, 1300, 650);
    ofBeginShape();
    ofVertex(start_road.x, start_road.y);
    ofVertex(175, 700);
    ofVertex(1300, 700);
    ofVertex(1300, 675);
    ofVertex(start_road.x, start_road.y);
    ofEndShape();
    
    ofSetColor(238, 216, 174);
    ofBeginShape();
    ofVertex(start_road.x, start_road.y);
    ofVertex(0, 630);
    ofVertex(0, 700);
    ofVertex(70, 700);
    ofVertex(start_road.x, start_road.y);
    ofEndShape();
    ofDrawTriangle(start_road.x, start_road.y, 1300, 560, 1300, 520);
   
    
    ofSetColor(255, 235, 200);
    //ofDrawTriangle(start_road.x, start_road.y, 25, 700, 75, 700);
    ofDrawTriangle(start_road.x, start_road.y, 70, 700, 120, 700);
    ofDrawTriangle(1300, 410, rightR_up.x, rightR_up.y, start_road.x, start_road.y);
    ofDrawTriangle(left_sr.x, left_sr.y, 0, 470, start_road.x, start_road.y);
    
    ofSetColor(205, 170, 125);
    ofDrawLine(start_road.x, start_road.y, 70, 700);
    //ofDrawLine(start_road.x, start_road.y, end_sign.x, 700);
    
    
    ofSetColor(170);
    ofDrawTriangle(start_road.x, start_road.y, 0, 565, 0, 675);
    
    if (scope == 3){
        
        for (int i = 0; i < ofGetWidth()/step_size; i++){
            for (int j = 0; j < (ofGetHeight())/step_size; j++){
                ofSetColor(230, ofRandom(50, 80));
                //ofSetColor(0, ofRandom(255), ofRandom(255), ofRandom(10, 50));
                ofFill();
                ofDrawRectangle(i*step_size, j*step_size, step_size, step_size);
                ofNoFill();
            }
        }
        
        ofSetColor(175);
        ofFill();
        ofDrawTriangle(start_road.x, start_road.y, 120, 700, 160, 700);
        ofDrawTriangle(start_road.x, start_road.y, 1300, 550, 1300, 650);
        ofBeginShape();
        ofVertex(start_road.x, start_road.y);
        ofVertex(175, 700);
        ofVertex(1300, 700);
        ofVertex(1300, 675);
        ofVertex(start_road.x, start_road.y);
        ofEndShape();
    }
    
    ofSetColor(255);
    ofDrawTriangle(start_road.x, start_road.y, 0, 645, 0, 630);
    ofDrawTriangle(start_road.x, start_road.y, 185, 700, 160, 700);
    ofDrawTriangle(start_road.x, start_road.y, 1300, 650, 1300, 675);
    //ofDrawBitmapString("Press the SPACE ;)", 50, 50);
//    ofDrawBitmapString(to_string(hue), 50, 100);
//    ofDrawBitmapString(to_string(fake_hue), 200, 200);
//    ofDrawBitmapString(to_string(sunny_day), 200, 300);
//    ofDrawBitmapString(to_string(having_stars), 200, 320);
    
    ofSetColor(238, 216, 174);
    ofDrawTriangle(start_road.x, start_road.y, 0, 565, 0, 545);

    
    for (int i = 1; i < centerR_vector.size(); i++){
        centerR_vector[i].display(v);
    }
    
    for (int i = 1; i < sign_vector.size(); i++){
        sign_vector[i].display_sign(v);
    }
    for (int i = 1; i < sign_vector1.size(); i++){
        sign_vector1[i].display_sign(v);
    }
    
    for (int i = 0; i < event_vector.size(); i++){
        event_vector[i].display();
    }
    
    
    // mosaic try
    
    if (scope == 4){
        for (int i = 0; i < ofGetWidth()/step_size; i++){
            for (int j = 0; j < (ofGetHeight()*0.7)/step_size; j++){
                ofSetColor(240, ofRandom(50, 100));
                //ofSetColor(0, ofRandom(255), ofRandom(255), ofRandom(10, 50));
                ofFill();
                ofDrawRectangle(i*step_size, j*step_size, step_size, step_size);
                ofNoFill();
            }
        }
    }
    
    for (int i = 0; i < meteors.size(); i++){
        meteors[i].display();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if (key == '1'){
        v = 1;
    }
    if (key == '2'){
        v = 2;
    }
    if (key == '3'){
        v = 3;
    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    if (scope == 4){
        scope = 1;
    }
    else{
        scope++;
    }

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
