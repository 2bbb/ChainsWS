#pragma once
#include "ofMain.h"
#include "BaseMotionManager.h"
#include "BaseMotion.h"

// OBJECT
class CircleObj{
public:
    CircleObj():x(0),y(0),radius(0){}
    CircleObj(float x, float y, float z, float radius, const ofColor  & col = ofColor::white){
        this->x = x;
        this->y = y;
        this->z = z;
        this->radius = radius;
        this->color = col;
    }
    float x;
    float y;
    float z;
    float radius;
    ofColor color;
};

//MOTION
class CircleMotion : public BaseMotion<CircleObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofDrawCircle(getValue().x, getValue().y, getValue().z, getValue().radius);
    }
};

//MANAGER
class CircleMotionManager : public BaseMotionManager<CircleObj, CircleMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
    void custom_emit();
};

