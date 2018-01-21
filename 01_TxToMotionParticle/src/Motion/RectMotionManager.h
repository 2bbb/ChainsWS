#pragma once
#include "ofMain.h"
#include "BaseMotionManager.h"
#include "BaseMotion.h"

// OBJECT
class RectObj{
public:
    RectObj(){};
    RectObj(ofVec3f pos,float w, float h, const ofColor  & col = ofColor::white){
        this->pos = pos;
        this->w = w;
        this->h = h;
        this->color = col;
    }
    ofVec3f pos;
    float w,h;
    ofColor color;
};

//MOTION
class RectMotion : public BaseMotion<RectObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofDrawRectangle(getValue().pos, getValue().w, getValue().h);
    }
};

//MANAGER
class RectMotionManager : public BaseMotionManager<RectObj, RectMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

