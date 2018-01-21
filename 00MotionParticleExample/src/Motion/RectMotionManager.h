#pragma once
#include "ofMain.h"
#include "BaseMotionManager.h"
#include "BaseMotion.h"

// OBJECT
class RectObj{
public:
    RectObj():x(0),y(0),w(0), h(0){}
    RectObj(float x, float y, float z,float w, float h, const ofColor  & col = ofColor::white){
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
        this->h = h;
        this->color = col;
    }
    float x;
    float y;
    float z;
    float w,h;
    ofColor color;
};

//MOTION
class RectMotion : public BaseMotion<RectObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofDrawRectangle(getValue().x, getValue().y, getValue().z, getValue().w, getValue().h);
    }
};

//MANAGER
class RectMotionManager : public BaseMotionManager<RectObj, RectMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
    //NEED TO MAKE A CUSTOM FUNCTION
    void custom_emit(const RectObj & start, const RectObj & end, float dur);
    void procedure_emit();
};

