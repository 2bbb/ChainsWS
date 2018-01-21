#pragma once
#include "ofMain.h"
#include "BaseMotionManager.h"
#include "BaseMotion.h"

// OBJECT
class CircleObj{
public:
    CircleObj(){};
    CircleObj(ofVec3f pos, float radius, const ofColor  & col = ofColor::white){
        this->pos = pos;
        this->radius = radius;
        this->color = col;
    }
    ofVec3f pos;
    float radius;
    ofColor color;
};

//MOTION
class CircleMotion : public BaseMotion<CircleObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofDrawCircle(getValue().pos, getValue().radius);
    }
};

//MANAGER
class CircleMotionManager : public BaseMotionManager<CircleObj, CircleMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

