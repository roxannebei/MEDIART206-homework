#include "ofApp.h"
using namespace ofxCv;
using namespace cv;

glm::vec3 lake_pos = glm::vec3 (-400, -760, 80);

float z = 200;

ofColor lake_top;
ofColor lake_down;
ofColor day_lake_top = ofColor(64, 113, 210);
ofColor day_lake_down = ofColor(118, 178, 204);
ofColor night_lake_top = ofColor(50, 93, 154);
ofColor night_lake_down = ofColor(78, 132, 150);

ofColor ground;
ofColor day_ground = ofColor(238, 216, 174);
ofColor night_ground = ofColor(206, 184, 139);

ofColor brown_land;
ofColor spring_day_brown_land = ofColor(127, 168, 111);
ofColor spring_night_brown_land = ofColor(89, 116, 53);
ofColor winter_day_brown_land = ofColor(165, 132, 96);
ofColor winter_night_brown_land = ofColor(123, 97, 72);
ofColor day_brown = winter_day_brown_land;
ofColor night_brown = winter_night_brown_land;

ofColor green;
ofColor soring_day_green = ofColor(154, 205, 50);
ofColor spring_night_green = ofColor(121, 154, 54);
ofColor winter_day_green = ofColor(171, 156, 90);
ofColor winter_night_green = ofColor(129, 118, 68);
ofColor day_green = winter_day_green;
ofColor night_green = winter_night_green;

ofColor flower_land;
ofColor day_flower_land = ofColor(222, 184, 135);
ofColor night_flower_land = ofColor(184, 158, 124);

float hue;
float fake_hue;

float len_day = 10;
float len_night = 10;
float trans_day_night = 6;
float len_total_day = len_day + len_night + 2*trans_day_night;
float count_day;

bool start_day = false;
bool start_d2n = false;
bool start_night = false;
bool start_n2d = false;

float day_cottage_light_y = 0;
float night_cottage_light_y = 850;
float cottage_light_y = day_cottage_light_y;

float day_sunlight_x = 10;
float night_sunlight_x = -100;
float sunlight_x = day_sunlight_x;

float x, y;

ofColor c1 = ofColor(255, 207, 163);
ofColor c2 = ofColor(41, 34, 28);
ofColor c3 = ofColor(255, 207, 163);
ofColor c4 = ofColor(41, 34, 28);
ofColor c5 = ofColor(239, 208, 189);
ofColor c6 = ofColor(63, 50, 43);
ofColor c7 = ofColor(36, 48, 68);
ofColor c8 = ofColor(143, 178, 230);
ofColor c9 = ofColor(30, 43, 75);
ofColor c10 = ofColor(147, 194, 226);
ofColor c11 = ofColor(25, 46, 69);
ofColor c12 = ofColor(150, 189, 219);
ofColor c13 = ofColor(35, 49, 64);
ofColor c14 = ofColor(65, 53, 45);

float len_winter = 96;
float len_spring = 96;
float len_year = len_winter+len_spring; // 160; 0-159
float count_year;
ofColor sky_color;
bool is_winter = true;

float p1 = 10;
float p2 = 6;

float amp_spring = 11;
float amp_winter = 0;
float lake_amp = amp_winter;

float ice_height = 40;
float ice_alpha;
float farm_daylight_z = -160;
float farm_nightlight_z = -500;
float farm_light_z = farm_daylight_z;

ofBoxPrimitive all;
ofVec3f all_pos = ofVec3f(300, 350, 330);
float box_w = 2000;
float box_h = 1200;
float box_d = 1300;

vector<ofVec2f> star_side;
vector<ofVec2f> star_front;

float current_num_of_star; // 这个和时间有关
float num_star = 200; // 变的是这个
float max_star = 600;

vector<Snow> snow_list;
vector<Snow> snow_on_floor;

float current_num_of_snow;
float num_snow = 300;
float max_snow = 2000;
float count_snow = 0;
float current_snow_on_floor = count_snow;

float theata;
int time_status;
vector<Flower> flower_list;
vector<ofColor> flower_c_day;
vector<ofColor> flower_c_night;

float fl_w = 200;
float fl_h = 10;
float fl_d = 300;
ofVec3f fl_pos;

float count_flower;
vector<int> flower_color_index;
float current_flower_num = 0;

float sum_x = 0;
float sum_y = 0;
float countt = 0;
float avg_x = 0;
float avg_y = 0;
float scale_pos_x = 0;
float scale_pos_y = 0;

ofVec3f camera_pos = ofVec3f(-45, 0, 865);
ofVec3f camera_lookat = ofVec3f(0.0523, 0, -0.9986);

float blob_x;
float blob_y;
ofVec2f blob_pos;

bool look_around = false;



//--------------------------------------------------------------
void ofApp::setup(){

    
    ofBackground(255, 218, 185);
    
    fl_pos.set(-370, -37, 620);
    
    for (int i = 0; i < max_snow; i++){
        
        ofVec3f snow_pos;
        snow_pos.x = all_pos.x+ofRandom(-box_w/2, box_w/2);
        snow_pos.y = all_pos.y+ofRandom(0, box_h/2);
        snow_pos.z = all_pos.z+ofRandom(-box_d/2, box_d/2);
        
        Snow snow = Snow(snow_pos, 3);
        snow_list.push_back(snow);
    }
    
    for (int i = 0; i < max_star; i++){
        ofVec2f front_s;
        front_s.x = ofRandom(-box_w/2, box_w/2);
        front_s.y = ofRandom(-box_h/2, box_h/2);
        star_front.push_back(front_s);
        ofVec2f side_s;
        side_s.x = ofRandom(-box_h/2, box_h/2);
        side_s.y = ofRandom(-box_d/2, box_d/2);
        star_side.push_back(side_s);
    }
    
    lake_top = day_lake_top;
    lake_down = day_lake_down;
    ground = day_ground;
    green = day_green;
    brown_land = day_brown;
    flower_land = day_flower_land;
    
    ofPushMatrix();
    ofRotateDeg(180, 0, -95, 100);
    camera.rotateDeg(-3, 0,1,0);
    ofPopMatrix();
    
    lake.setup(920, 1000, 100, 100);
    lake.noise_scale = glm::vec2(0.008, 0.007);
    lake.noise_freq = 0.5;
    lake.noise_amp = lake_amp;
    lake.top_color = lake_top;
    lake.down_color = lake_down;

    /*    --------------------------
     //    lake.top_color = ofColor(50, 93, 154);
     //    lake.down_color = ofColor(78, 132, 150);
     -------------------------- */
    
    lake.update_noise();
    lake.update_color();

    
    cottage.loadModel("chata/chata.obj");
    mountain.loadModel("mountain/mountain.obj");
    farm.loadModel("Farm/Farm.3ds");
    
    
    
    for (int i = 0; i < cottage.getMeshCount(); i++){
        cottage_orig_mesh.push_back(cottage.getMesh(i));
        cottage_materials.push_back(cottage.getMaterialForMesh(i));
        cottage_textures.push_back(cottage.getTextureForMesh(i));
    }
    
    for (int i = 0; i < mountain.getMeshCount(); i++){
        mountain_orig_mesh.push_back(mountain.getMesh(i));
        mountain_materials.push_back(mountain.getMaterialForMesh(i));
        mountain_textures.push_back(mountain.getTextureForMesh(i));
    }

    cottage_meshes = cottage_orig_mesh;
    mountain_meshes = mountain_orig_mesh;
    
//    for (int i=0; i<model.getMeshCount(); i++)
//    {
//        orig_mesh.push_back(model.getMesh(i));
//        materials.push_back(model.getMaterialForMesh(i));
//        textures.push_back(model.getTextureForMesh(i));
//    }
//
//    meshes = orig_mesh;
    
    ofSetSmoothLighting(true);
    
    cottage_color_light.setDirectional();
    cottage_color_light.setPosition(-400, -200, -500);
    //cottage_color_light.lookAt(glm::vec3(0));
    //cottage_color_light.lookAt(glm::vec3(0, 850, 0));
    cottage_color_light.lookAt(glm::vec3(0, cottage_light_y, 0));
    cottage_color_light.setDiffuseColor(ofColor(253, 245, 230));
    
    /*    --------------------------
     cottage_color_light.lookAt(glm::vec3(0, z, 0));
     day：0
     night：850
     z value
     -------------------------- */
    
    sunlight.setDirectional();
    sunlight.setPosition(0, -200, 300);
    //sunlight.lookAt(glm::vec3(-50, -100, 400)); // to adjust the brightness, change the x value
    //sunlight.lookAt(glm::vec3(-250, -100, 200));
    sunlight.lookAt(glm::vec3(sunlight_x, -100, 450+sunlight_x));
    
    /*    --------------------------
     sunlight.lookAt(glm::vec3(z, -100, 450+z)); // to adjust the brightness, change the x value
     //sunlight.lookAt(glm::vec3(-250, -100, 200));
     day：10
     night：-250
     z value
     -------------------------- */
    
    sunlight.setDiffuseColor(ofColor::snow);
    
    farm_light.setDirectional();
    farm_light.lookAt(glm::vec3(213, -699, farm_light_z));
    farm_light.setDiffuseColor(ofColor::cornsilk);
    
    all = ofBoxPrimitive(box_w, box_h, box_d);
    all.setPosition(all_pos);
    
    flower_c_day.push_back(ofColor(255, 228, 225));
    flower_c_day.push_back(ofColor(240, 255, 240));
    flower_c_day.push_back(ofColor(255, 248, 220));
    flower_c_night.push_back(ofColor(205, 155, 155));
    flower_c_night.push_back(ofColor(155, 205, 155));
    flower_c_night.push_back(ofColor(238, 207, 161));

    
    for (int c = fl_pos.z-fl_d/2+10; c <= fl_pos.z+fl_d/2-10; c += 40){
        for (int r = fl_pos.x-fl_w/2 + 10; r <= fl_pos.x+fl_w/2-10; r+= 30){
            float size = ofRandom(1.5, 3);
            //Flower f = Flower(glm::vec3(-400, -26, 600), 2.5);
            
            Flower f = Flower(glm::vec3(r, -26, c), size);
            flower_list.push_back(f);
            count_flower++;
        }
    }
    for (int i = 0; i < count_flower; i++){
        flower_color_index.push_back(ofRandom(0,3));
    }
    
    kinect.open();
    img.allocate(521,424, OF_IMAGE_COLOR);
    
    ofSetVerticalSync(true);
    finder.setup("haarcascade_upperbody.xml");
    finder.setup("haarcascade_frontalface_default.xml");
    finder.setPreset(ObjectFinder::Fast);
    finder.getTracker().setSmoothingRate(.3);
    cam.setup(640, 480);
    ofEnableAlphaBlending();
    
//    camera.lookAt(camera_lookat);
//    camera.setPosition(camera_pos);
    
}

ofColor ofApp::get_current_color(float current_time, float min_time, float max_time, ofColor c_bgn, ofColor c_end){
    ofColor current_color;
    current_color.r = ofMap(current_time, min_time, max_time, c_bgn.r, c_end.r);
    current_color.g = ofMap(current_time, min_time, max_time, c_bgn.g, c_end.g);
    current_color.b = ofMap(current_time, min_time, max_time, c_bgn.b, c_end.b);
    return current_color;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    kinect.update();
    if(kinect.isFrameNew()){
        texture.loadData(kinect.getRawDepthPixels());
        
        sum_x = 0;
        sum_y = 0;
        countt = 0;
        avg_x = 0;
        avg_y = 0;
        scale_pos_x = 0;
        scale_pos_y = 0;
        
        for (int y=0; y < texture.getHeight(); y++){
            for (int x=0; x < texture.getWidth(); x++){
                ofColor color = kinect.getDepthPixels().getColor(x, y);
                float brightness = color.getBrightness();
                
                if(brightness<20){
                    
                    if (y < texture.getHeight()-20){
                        if (x < texture.getWidth()-100 and x > 87){
                            int scale = 1;
                            if (x > 150 and x < 300 and y > 100 and y < 300){
                                scale = 2;
                            }
                            sum_x += x * scale;
                            sum_y += y * scale;
                            countt += scale;
                        }
                    }
                    
                }
            }
        }
        
        img.update();
        
        avg_x = sum_x/countt;
        avg_y = sum_y/countt;
    }
    
    cam.update();
    
    if(cam.isFrameNew()) {
        finder.update(cam);
        
        blob_x = 0;
        blob_y = 0;
        blob_pos.set(0, 0);
        
        for(int i = 0; i < finder.size(); i++) {
            ofRectangle object = finder.getObjectSmoothed(i);
           
            blob_x = object.x;
            blob_y = object.y;
            blob_pos = object.getPosition();
        }
    }
    
    if (is_winter and avg_y >= 50 and avg_y <= 315){
        
        num_snow = ofMap(avg_y, 50, 315, max_snow, 0);
    }
    if (!is_winter and avg_y >= 50 and avg_y <= 315){
        current_flower_num = ofMap(avg_y, 50, 315, 0, 8);
        current_flower_num = (int) current_flower_num * 7;
    }
    
    if (avg_x >= 50 and avg_x <= 345){
        num_star = ofMap(avg_x, 50, 345, 0, max_star);
    }
    
    if (look_around){
        
        float map_x_f = ofMap(blob_x, 0, 640, -12, 12);
        int map_x = (int)map_x_f;
        camera.lookAt(glm::vec3(camera_lookat.x - 250*map_x, 0, camera_lookat.z - 50*map_x));
        
        float map_area_f = ofMap(blob_x*blob_y, 32000, 81920, -12, 12);
        int map_area = (int) map_area_f;
        camera.setPosition(glm::vec3(camera_pos.x, camera_pos.y, camera_pos.z+23*map_area));
    }
    
    count_day = fmodf(ofGetElapsedTimef(), len_total_day);
    count_year = fmodf(ofGetElapsedTimef(), len_year);
    
    if (count_day < len_day){
        start_day = true;
        start_n2d = false;
        time_status = 1;
    }
    if (count_day < len_day+trans_day_night and count_day >= len_day){
        start_d2n = true;
        start_day = false;
        time_status = 2;
    }
    if (count_day < len_day+trans_day_night+len_night and count_day >= len_day+trans_day_night){
        start_night = true;
        start_d2n = false;
        time_status = 3;
    }
    if (count_day < len_total_day and count_day >= len_day+trans_day_night+len_night){
        start_n2d = true;
        start_night = false;
        time_status = 4;
    }
    
    if (start_day){
        lake_top = day_lake_top;
        lake_down = day_lake_down;
        ground = day_ground;
        green = day_green;
        brown_land = day_brown;
        flower_land = day_flower_land;
        cottage_light_y = day_cottage_light_y;
        sunlight_x = day_sunlight_x;
        farm_light_z = farm_daylight_z;
        current_num_of_star = 0;
    }
    if (start_night){
        lake_top = night_lake_top;
        lake_down = night_lake_down;
        ground = night_ground;
        green = night_green;
        brown_land = night_brown;
        flower_land = night_flower_land;
        cottage_light_y = night_cottage_light_y;
        sunlight_x = night_sunlight_x;
        farm_light_z = farm_nightlight_z;
        current_num_of_star = num_star;
    }
    if (start_d2n){
        lake_top = get_current_color(count_day, len_day, len_day+trans_day_night, day_lake_top, night_lake_top);
        lake_down = get_current_color(count_day, len_day, len_day+trans_day_night, day_lake_down, night_lake_down);
        ground = get_current_color(count_day, len_day, len_day+trans_day_night, day_ground, night_ground);
        green = get_current_color(count_day, len_day, len_day+trans_day_night, day_green, night_green);
        brown_land = get_current_color(count_day, len_day, len_day+trans_day_night, day_brown, night_brown);
        flower_land = get_current_color(count_day, len_day, len_day+trans_day_night, day_flower_land, night_flower_land);
        cottage_light_y = ofMap(count_day, len_day, len_day+trans_day_night, day_cottage_light_y, night_cottage_light_y);
        sunlight_x = ofMap(count_day, len_day, len_day+trans_day_night, day_sunlight_x, night_sunlight_x);
        farm_light_z = ofMap(count_day, len_day, len_day+trans_day_night, farm_daylight_z, farm_nightlight_z);
        current_num_of_star = ofMap(count_day, len_day, len_day+trans_day_night, 0, num_star);
    }
    if (start_n2d){
        lake_top = get_current_color(count_day, len_day+len_night+trans_day_night, len_total_day, night_lake_top, day_lake_top);
        lake_down = get_current_color(count_day, len_day+len_night+trans_day_night, len_total_day, night_lake_down, day_lake_down);
        ground = get_current_color(count_day, len_day+len_night+trans_day_night, len_total_day, night_ground, day_ground);
        green = get_current_color(count_day, len_day+len_night+trans_day_night, len_total_day, night_green, day_green);
        brown_land = get_current_color(count_day, len_day+len_night+trans_day_night, len_total_day, night_brown, day_brown);
        flower_land = get_current_color(count_day, len_day+len_night+trans_day_night, len_total_day, night_flower_land, day_flower_land);
        cottage_light_y = ofMap(count_day, len_day+len_night+trans_day_night, len_total_day, night_cottage_light_y, day_cottage_light_y);
        sunlight_x = ofMap(count_day, len_day+len_night+trans_day_night, len_total_day, night_sunlight_x, day_sunlight_x);
        farm_light_z = ofMap(count_day, len_day+len_night+trans_day_night, len_total_day, farm_nightlight_z, farm_daylight_z);
        current_num_of_star = ofMap(count_day, len_day+len_night+trans_day_night, len_total_day, num_star, 0);
    }
    
    
    cottage_color_light.lookAt(glm::vec3(0, cottage_light_y, 0));
    sunlight.lookAt(glm::vec3(sunlight_x, -100, 450+sunlight_x));
    farm_light.lookAt(glm::vec3(213, -699, farm_light_z));
    

    
    // --------------------------------------------------- season
    
    if (count_year >= 85 and count_year < 181){
        is_winter = false;
    }
    else{
        is_winter = true;
    }
    
    if (count_year >= 0 and count_year < p1){
        sky_color = c1;
        lake_amp = 0;
        ice_height = ofMap(count_year, 0, p1, 25, 30);
        ice_alpha = ofMap(count_year, 0, p1, 10, 40);
        day_green = get_current_color(count_year, 0, p1+p2, soring_day_green, winter_day_green);
        day_brown = get_current_color(count_year, 0, p1+p2, spring_day_brown_land, winter_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
       
    }
    if (count_year >= p1 and count_year < p1+p2){
        sky_color = get_current_color(count_year, p1, p1+p2, c1, c2);
        lake_amp = 0;
        ice_height = ofMap(count_year, p1, p1+p2, 30, 45);
        ice_alpha = ofMap(count_year, p1, p1+p2, 40, 80);
        day_green = get_current_color(count_year, 0, p1+p2, soring_day_green, winter_day_green);
        day_brown =get_current_color(count_year, 0, p1+p2, spring_day_brown_land, winter_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
        
    }
    if (count_year >= p1+p2 and count_year < p1*2+p2){
        sky_color = c2;
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = ofMap(count_year, p1+p2, p1*2+p2, 80, 120);
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = ofMap(count_year, p1+p2, p1*2+p2*2, 0, num_snow);
        current_snow_on_floor = count_snow;
        
    }
    if (count_year >= p1*2+p2 and count_year < p1*2+p2*2){
        sky_color = get_current_color(count_year, p1*2+p2, p1*2+p2*2, c2, c3);
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = 120;
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = ofMap(count_year, p1+p2, p1*2+p2*2, 0, num_snow);
        current_snow_on_floor = count_snow;
    }
    if (count_year >= p1*2+p2*2 and count_year < p1*3+p2*2){
        sky_color = c3;
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = 120;
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = num_snow;
        current_snow_on_floor = count_snow;
    }
    if (count_year >= p1*3+p2*2 and count_year < p1*3+p2*3){
        sky_color = get_current_color(count_year, p1*3+p2*2, p1*3+p2*3, c3, c4);
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = 120;
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = num_snow;
        current_snow_on_floor = count_snow;
    }
    if (count_year >= p1*3+p2*3 and count_year < p1*4+p2*3){
        sky_color = c4;
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = 120;
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = num_snow;
        current_snow_on_floor = count_snow;
    }
    if (count_year >= p1*4+p2*3 and count_year < p1*4+p2*4){
        sky_color = get_current_color(count_year, p1*4+p2*3, p1*4+p2*4, c4, c5);
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = ofMap(count_year, p1*4+p2*3, p1*4+p2*4, 120, 60);
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = num_snow;
        current_snow_on_floor = ofMap(count_year, p1*4+p2*3, p1*5+p2*4, count_snow, 0);
    }
    if (count_year >= p1*4+p2*4 and count_year < p1*5+p2*4){
        sky_color = c5;
        lake_amp = 0;
        ice_height = 45;
        ice_alpha = ofMap(count_year, p1*4+p2*4, p1*5+p2*4, 60, 30);
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = ofMap(count_year, p1*4+p2*4, p1*5+p2*5+0.2*p1, num_snow, 0);
        current_snow_on_floor = ofMap(count_year, p1*4+p2*3, p1*5+p2*4, count_snow, 0);
    }
    if (count_year >= p1*5+p2*4 and count_year < p1*5+p2*5){
        sky_color = get_current_color(count_year, p1*5+p2*4, p1*5+p2*5, c5, c6);
        lake_amp = 0;
        ice_alpha = ofMap(count_year, p1*5+p2*4, p1*5+p2*5, 30, 0);
        ice_height = ofMap(count_year, p1*5+p2*4, p1*5+p2*5, 45, 40);
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = ofMap(count_year, p1*4+p2*4, p1*5+p2*5+0.2*p1, num_snow, 0);
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*5+p2*5 and count_year < p1*5+p2*5+0.2*p1){
        sky_color = c6;
        lake_amp = 0.5;
        ice_alpha = 0;
        ice_height = ofMap(count_year, p1*5+p2*5, p1*5+p2*5+0.2*p1, 40, 35);
        day_green = winter_day_green;
        day_brown = winter_day_brown_land;
        current_num_of_snow = ofMap(count_year, p1*4+p2*4, p1*5+p2*5+0.2*p1, num_snow, 0);
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*5+p2*5+0.2*p1 and count_year <  p1*5+p2*5+0.8*p1){
        sky_color = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*5+p2*5+0.8*p1, c6, c7);
        lake_amp = 1;
        ice_height = ofMap(count_year, p1*5+p2*5+0.2*p1, p1*5+p2*5+0.8*p1, 35, 10);
        ice_alpha = 0;
        day_green = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_green, soring_day_green);
        day_brown = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_brown_land, spring_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*5+p2*5+0.8*p1 and count_year < p1*6+p2*5){
        sky_color = c7;
        lake_amp = 3;
        day_green = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_green, soring_day_green);
        day_brown = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_brown_land, spring_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
        count_snow = 0;
    }
    if (count_year >= p1*6+p2*5 and count_year < p1*6+p2*6){
        sky_color = get_current_color(count_year, p1*6+p2*5, p1*6+p2*6, c7, c8);
        lake_amp = 5;
        day_green = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_green, soring_day_green);
        day_brown = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_brown_land, spring_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*6+p2*6 and count_year < p1*7+p2*6){
        sky_color = c8;
        lake_amp = 7;
        day_green = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_green, soring_day_green);
        day_brown = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_brown_land, spring_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*7+p2*6 and count_year < p1*7+p2*7){
        sky_color = get_current_color(count_year, p1*7+p2*6, p1*7+p2*7, c8, c9);
        lake_amp = 9;
        day_green = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_green, soring_day_green);
        day_brown = get_current_color(count_year, p1*5+p2*5+0.2*p1, p1*7+p2*7, winter_day_brown_land, spring_day_brown_land);
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*7+p2*7 and count_year < p1*8+p2*7){
        sky_color = c9;
        lake_amp = 11;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*8+p2*7 and count_year < p1*8+p2*8){
        sky_color = get_current_color(count_year, p1*8+p2*7, p1*8+p2*8, c9, c10);
        lake_amp = 11;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*8+p2*8 and count_year < p1*9+p2*8){
        sky_color = c10;
        lake_amp = 11;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*9+p2*8 and count_year < p1*9+p2*9){
        sky_color = get_current_color(count_year, p1*9+p2*8, p1*9+p2*9, c10, c11);
        lake_amp = 11;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*9+p2*9 and count_year < p1*10+p2*9){
        sky_color = c11;
        lake_amp = 7;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*10+p2*9 and count_year < p1*10+p2*10){
        sky_color = get_current_color(count_year, p1*10+p2*9, p1*10+p2*10, c11, c12);
        lake_amp = 5;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*10+p2*10 and count_year < p1*11+p2*10){
        sky_color = c12;
        lake_amp = 3;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*11+p2*10 and count_year < p1*11+p2*11){
        sky_color = get_current_color(count_year, p1*11+p2*10, p1*11+p2*11, c12, c13);
        lake_amp = 2;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*11+p2*11 and count_year < p1*11+p2*11+p1*0.2){
        sky_color = c13;
        lake_amp = 1;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*11+p2*11+p1*0.2 and count_year < p1*11+p2*11+p1*0.8){
        sky_color = get_current_color(count_year, p1*11+p2*11+p1*0.2, p1*11+p2*11+p1*0.8, c13, c14);
        lake_amp = 0.5;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*11+p2*11+p1*0.8 and count_year < p1*12+p2*11){
        sky_color = c14;
        lake_amp = 0;
        ice_alpha = 0;
        ice_height = 15;
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    if (count_year >= p1*12+p2*11 and count_year < p1*12+p2*12){
        sky_color = get_current_color(count_year, p1*12+p2*11, len_year, c14, c1);
        lake_amp = 0;
        ice_alpha = ofMap(count_year, p1*12+p2*11, p1*12+p2*12, 0, 10);
        ice_height = ofMap(count_year, p1*12+p2*11, p1*12+p2*12, 15, 25);
        day_green = soring_day_green;
        day_brown = spring_day_brown_land;
        current_num_of_snow = 0;
        current_snow_on_floor = 0;
    }
    
    lake.noise_amp = lake_amp;
    lake.top_color = lake_top;
    lake.down_color = lake_down;
    
    lake.update_noise();
    lake.update_color();
    lake.setPosition(lake_pos);
    lake.setScale(1.0);
    
    
    glm::vec3 gravity(0, -0.05, 0);
    
    for (int i = 0; i < current_num_of_snow; i++){
        snow_list[i].apply_force(gravity);
        snow_list[i].update();
        
        float lower_bound = ofRandom(-40, 0);
        if (!snow_list[i].in_box(lower_bound)){
            float update_y = all_pos.y + ofRandom(50, box_h/2);
            snow_list[i].reset(update_y);
            count_snow += 2;
        }
    }
    
    for (int i = 0; i < current_snow_on_floor; i++){
        float x = 100+ofRandom(-1300/2, 1300/2);
        float y = -40;
        float z = 600+ofRandom(-750/2, 750/2);
        
        float delta = 0;
        if (ofDist(x, z, -400, 600) <= 250){
            delta = 5;
        }
        if (ofDist(x, z, -80, 420) <= 80){
            delta = 5;
        }
        if (ofDist(x, z, -130, 500) <= 80){
            delta = 5;
        }
        if (x > fl_pos.x-fl_w/2 and x < fl_pos.y+fl_w/2 and z > fl_pos.z-fl_d/2 and z < fl_pos.z+fl_d/2){
            delta = fl_h;
        }
        glm::vec3 floor_pos = glm::vec3(x, y+delta, z);
        
        Snow floor_snow = Snow(floor_pos, 0.5);
        snow_on_floor.push_back(floor_snow);
    }

    theata += PI/1080;
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(sky_color);
    
    camera.begin();
    ofEnableDepthTest();
    
    ofPushMatrix();
    for (int i = 0; i < current_num_of_star; i++){
        ofSetColor(255, sin(theata*i/TWO_PI)*255);
        ofPushStyle();
        ofFill();
        ofDrawSphere(all_pos.x+star_front[i].x, all_pos.y+star_front[i].y, all_pos.z-box_d/2, 1.5);
        ofDrawSphere(all_pos.x-box_w/2, all_pos.y+star_side[i].y, all_pos.z+star_side[i].x, 1.5);
        ofDrawSphere(all_pos.x+box_w/2, all_pos.y+star_side[z-1-i].x, all_pos.z+star_side[z-1-i].y, 1.5);
        ofNoFill();
        ofPopStyle();
    }
    ofPopMatrix();
    
    ofPushMatrix();
    for (int i = 0; i < current_num_of_snow; i++){
        snow_list[i].display();
    }
    for (int i = 0; i < current_snow_on_floor; i++){
        snow_on_floor[i].display();
    }
    ofPopMatrix();
    
//    ofBoxPrimitive lower_bound = ofBoxPrimitive(box_w, 1, box_d);
//    lower_bound.setPosition(all_pos.x, -40, all_pos.z);
//    lower_bound.draw();

    
//    all.drawWireframe();
//    of3dPrimitive ball;
//    ball = ofSpherePrimitive(1300, 50);
//    ball.setPosition(300, 0, 330);
//    ball.drawWireframe();
    
    ofPushMatrix();
    ofRotateDeg(180, 0, -95, 100);
    lake.draw();
    ofPopMatrix();
    
    
    ofPushStyle();
    
    float height_pos;
    int step = 5;
    
    float lake_r = 350;
    ofVec3f lake_center;
    lake_center.set(300, 0, 650);
    
    if (is_winter){
        ofPushMatrix();
        ofRotateDeg(-6, 100, -95, 0);
        ofPushStyle();
        ofSetColor(240, 248, 255, ice_alpha);
        of3dPrimitive ice = ofCylinderPrimitive(lake_r+50, ice_height, 200, 200);
        ice.setPosition(lake_center.x, -110, lake_center.z);
        ice.draw();
        ofSetColor(240, 248, 255);
        ice.drawWireframe();
        ofPopStyle();
        ofPopMatrix();
    }
    
    for (int i = lake_center.x-lake_r; i < lake_center.x; i += step){
        for (int j = lake_center.z+lake_r; j > 240; j -= step){
            
            if (i == 20){
                ofSetColor(brown_land);
            }
            else{
                ofSetColor(ground);
            }
            
            height_pos = ofMap(j, lake_center.z-lake_r, lake_center.z+lake_r, -60, -20);
            
            if (ofDist(i, 0, j, lake_center.x, 0, lake_center.z) >= lake_r){
                ofDrawBox(i-step, height_pos, j-step, step, 15, step);
            }
            if (i == lake_center.x-lake_r){
                ofDrawBox(i-2.5-step, height_pos, j-step, 5, 15, step);
            }
        }
    }
    
    
    ofPopStyle();
    
    ofPushStyle();
    
    ofSetColor(ground);
    ofDrawBox(lake_center.x-lake_r-400, -40, lake_center.z+lake_r+200, 800, 1, 400);
    ofDrawBox(-350, -40, 620, 590, 1, 760);
    ofDrawBox(-50, -50, 300, 110, 15, 100);
    
    ofPushStyle();
    ofSetColor(brown_land);
    of3dPrimitive land1 = ofCylinderPrimitive(250, 5, 10, 20);
    land1.setPosition(-400, -40, 600);
    land1.draw();
    
    of3dPrimitive land2 = ofCylinderPrimitive(80, 5, 10, 20);
    land2.setPosition(-80, -40, 420);
    land2.draw();
    
    of3dPrimitive land3 = ofCylinderPrimitive(80, 5, 10, 20);
    land3.setPosition(-130, -40, 500);
    land3.draw();
    
    ofSetColor(flower_land);
    of3dPrimitive flower_land1 = ofBoxPrimitive(fl_w, fl_h, fl_d);
    flower_land1.setPosition(fl_pos);
    flower_land1.draw();

    ofPopStyle();
    
    
    ofEnableLighting();
    sunlight.enable();
    
    ofSetColor(green);
    
    of3dPrimitive land4 = ofCylinderPrimitive(100, 20, 200, 200);
    land4.setPosition(-160, -43, 600);
    land4.draw();
    
    //ofSetColor(240, 250, 240);
    ofDrawSphere(-100, -40, 720, 20);
    ofDrawSphere(-270, -300, 750, 305);
    ofDrawSphere(-370, -105, 880, 120);
    ofPopStyle();
    
    
    ofPushMatrix();
    ofTranslate(650, 0, 20);
    ofRotateDeg(30, 0, 1, 0);
    ofSetColor(255);
    float scale = mountain.getNormalizedScale();
    
    // --------------------------------------- mountain 0 ----------
    ofPushMatrix();
    ofTranslate(-390, -80, -110);
    
    //float scale = model.getNormalizedScale();
    ofScale(scale/1.3, scale/3.7, scale);
    
    for (int i = 0; i < mountain_meshes.size(); i++){
        
        mountain_textures[i].bind();
        mountain_meshes[i].draw();
        mountain_textures[i].unbind();
    }
    ofPopMatrix();
    // --------------------------------------- mountain 1 ----------
    ofPushMatrix();
    ofTranslate(-360, -80, -100);
    
    ofScale(scale/1.3, scale/3.7, scale);
    
    for (int i = 0; i < mountain_meshes.size(); i++){
        mountain_textures[i].bind();
        mountain_meshes[i].draw();
        mountain_textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 2 ----------
    ofPushMatrix();
    ofTranslate(-150, -100, -50);

    ofScale(scale, scale/5, scale/1.5);
    
    for (int i = 0; i < mountain_meshes.size(); i++){
        mountain_textures[i].bind();
        mountain_meshes[i].draw();
        mountain_textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 3 ----------
    ofPushMatrix();
    ofTranslate(100, -100, 30);
    ofRotateDeg(80, 0, 1, 0);

    ofScale(scale, scale/4.5, scale/2);
    
    for (int i = 0; i < mountain_meshes.size(); i++){
        mountain_textures[i].bind();
        mountain_meshes[i].draw();
        mountain_textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 4 ----------
    ofPushMatrix();
    ofTranslate(150, -100, 30);
    ofTranslate(-80, 0, 500);
    ofRotateDeg(120, 0, 1, 0);

    ofScale(scale, scale/4.5, scale/2);
    
    for (int i = 0; i < mountain_meshes.size(); i++){
        mountain_textures[i].bind();
        mountain_meshes[i].draw();
        mountain_textures[i].unbind();
    }
    ofPopMatrix();
    
    // --------------------------------------- mountain 5 ----------
    ofPushMatrix();
    ofTranslate(350, -100, 30);
    ofTranslate(-300, 0, 800);
    ofRotateDeg(80, 0, 1, 0);


    ofScale(scale/1.1, scale/2.8, scale/1.5);

    for (int i = 0; i < mountain_meshes.size(); i++){
        mountain_textures[i].bind();
        mountain_meshes[i].draw();
        mountain_textures[i].unbind();
    }
    ofPopMatrix();
    
    ofPopMatrix();
    
    
    if (!is_winter){
        for (int i = 0; i < current_flower_num; i++){
            flower_list[i].display(theata, time_status, flower_c_day[flower_color_index[i]], flower_c_night[flower_color_index[i]], count_day);
        }
    }

    
    sunlight.disable();
    
    
    cottage_color_light.enable();
    float cottage_scale = cottage.getNormalizedScale();

    vector<ofColor> color_list;
    color_list.push_back(ofColor::seaShell);
    color_list.push_back(ofColor::oldLace);
    color_list.push_back(ofColor::cornsilk);
    color_list.push_back(ofColor::mintCream);
    color_list.push_back(ofColor::aliceBlue);
    color_list.push_back(ofColor::lavender);
    ofPushMatrix();
    ofTranslate(-240, -30, 550);
    ofRotateDeg(270, 0, 1, 0);
    for (int i = 0; i < 6; i++){
        ofPushMatrix();
        ofTranslate(200, -120, 250);
        ofTranslate(210-i*125, 0, 0);
        ofRotateDeg(180, 0, 10, 10);
        ofScale(cottage_scale/5, cottage_scale/7, cottage_scale/5);
        ofSetColor(color_list[5-i]);
        ofFill();
        for (int i = 0; i < cottage_meshes.size(); i++){
            cottage_textures[i].bind();
            cottage_meshes[i].draw();
            cottage_textures[i].unbind();
        }
        ofPopMatrix();
    }
    ofPopMatrix();
    
    cottage_color_light.disable();
    
    if (!start_night){
        farm_light.enable();
    }
    ofPushMatrix();
    ofRotateDeg(180, 10, 0, 0);
    ofRotateDeg(270, 0, 1, 0);
    ofTranslate(-300, 40, 250);
    farm.setScale(0.7, 0.7, 0.7);
    farm.drawFaces();
    ofPopMatrix();
    if (!start_night){
        farm_light.disable();
    }


    ofDisableLighting();
    
    
    ofDisableDepthTest();
    camera.end();

    
    string info = "Press the key to move around in this world with your upper body";
//    info += to_string(camera.getPosition().x) + " ";
//    info += to_string(camera.getPosition().y) + " ";
//    info += to_string(camera.getPosition().z) + " ";
//    info += "\n";
//    info += to_string(camera.getLookAtDir().x) + " ";
//    info += to_string(camera.getLookAtDir().y) + " ";
//    info += to_string(camera.getLookAtDir().z) + " ";
//
//    info += to_string(z);
//    info += "\n hue: " + to_string((int)hue);
//    info += "\n fake hue: " + to_string((int)fake_hue);
//    info += "\n count day: " + to_string((int)count_day);
//    info += "\n x: " + to_string((int)x) + " ; y: " + to_string((int)y);
//    info += "\n count year: " + to_string((int)count_year);
//    info += " current num of snow: " + to_string((int) current_num_of_snow);
//    info += "\n current num of STAR: " + to_string((int) num_star);
//    info += "\n num of snow on floor: " + to_string((int) count_snow);
//    info += "\n current num of flower: " + to_string((int) current_flower_num);
//
//    ofDrawBitmapStringHighlight(info, 20,20);
    
//    ofPushMatrix();
//    ofTranslate(blob_pos);
//    ofPushStyle();
//    ofSetColor(255, 0, 0);
//    ofDrawCircle(blob_x/2, blob_y/2, 10, 10);
//    ofPopStyle();
//    ofDrawBitmapStringHighlight(ofToString(finder.getLabel(i)), 0, 0);
//    ofDrawLine(ofVec2f(), toOf(finder.getVelocity(i)) * 10);
//    ofPopMatrix();
    
//    string info;
//    info += "\n" + to_string(blob_x);
//    info += "\n" + to_string(blob_y);
    
    ofDrawBitmapStringHighlight(info, 20,20);
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' '){
        look_around = !look_around;
    }

}

void ofApp::exit(){
    kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

