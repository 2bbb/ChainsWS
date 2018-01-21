#pragma once

#include "BaseMotionManager.h"
#include "BaseMotion.h"

// OBJECT
class CubeObj{
public:
    CubeObj():x(0),y(0), z(0), w(0), h(0), d(0), color(ofColor::white){}
    CubeObj(float x, float y, float z,
            float w, float h, float d,
            const ofColor  & col = ofColor::white){
        this->x = x;
        this->y = y;
        this->z = z;
        
        this->w = w;
        this->h = h;
        this->d = d;
        
        this->color = col;
    }
    float x, y, z;
    float w, h, d;
    ofColor color;
};

//MOTION
class CubeMotion : public BaseMotion<CubeObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofDrawBox(getValue().x, getValue().y, getValue().z, getValue().w, getValue().h, getValue().d);
    }
};
class CubeParticleManager : public BaseMotionManager<CubeObj, CubeMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

