#pragma once

#include "BaseMotionManager.h"
#include "BaseMotion.h"

class SphereObj{
public:
    SphereObj(){};
    SphereObj(ofVec3f pos,
            float r,
            const ofColor  & col = ofColor::white){
        this->pos = pos;
        this->r = r;
        this->color = col;
    }
    ofVec3f pos;
    float r;
    ofColor color;
};

//MOTION
class SphereMotion : public BaseMotion<SphereObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofPushMatrix();
        ofDrawSphere(getValue().pos, getValue().r);
        ofPopMatrix();
    }
};

class SphereParticleManager : public BaseMotionManager<SphereObj, SphereMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

