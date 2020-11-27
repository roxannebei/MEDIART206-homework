//
//  Box.hpp
//  snow scene
//
//  Created by Rongqi Bei on 2020/11/25.
//

class Box{
    
public:
          
    Box(glm::vec3 _pos = glm::vec3(0,0,0), float _size = 2000)
    :
        pos     (_pos),
        size    (_size)
    {
    }
    
    inline void draw() {
        ofDrawBox(pos, size);
    }
    
    inline float getLeft() {
        return pos.x - size * 0.5;
    }
    inline float getRight() {
        return pos.x + size * 0.5;
    }
    inline float getTop() {
        return pos.y + size * 0.5;
    }
    inline float getBottom() {
        return pos.y - size * 0.5;
    }
    inline float getFront() {
        return pos.z - size * 0.5;
    }
    inline float getBack() {
        return pos.z + size * 0.5;
    }
    
    glm::vec3 pos;
    float size  = 2000;    //
    
};


