#pragma once

#include "BaseMotionManager.h"
#include "BaseMotion.h"

// OBJECT
class CubeObj{
public:
    CubeObj(){};
    CubeObj(ofVec3f pos,
            ofVec3f size,
            const ofColor  & col = ofColor::white){
        this->pos = pos;
        this->size = size;
        this->color = col;
    }
    ofVec3f pos;
    ofVec3f size;
    ofColor color;
};

//MOTION
class CubeMotion : public BaseMotion<CubeObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofDrawBox(getValue().pos, getValue().size.x, getValue().size.y, getValue().size.z);
    }
};
class CubeParticleManager : public BaseMotionManager<CubeObj, CubeMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

