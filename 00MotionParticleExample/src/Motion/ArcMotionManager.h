#pragma once
#include "ofMain.h"
#include "BaseMotionManager.h"
#include "BaseMotion.h"
#include "ofxPoly.h"

// OBJECT
// ONLY CLOCK WISE
class ArcObj{
public:
    ArcObj():x(0),y(0),radius(0){}
    ArcObj(float x, float y, float z, float radius, float width, float angleBegin, float angleEnd, const ofColor  & col = ofColor::white){
        this->x = x;
        this->y = y;
        this->z = z;
        this->radius = radius;
        this->angleBegin = angleBegin;
        this->angleEnd = angleEnd;
        this->color = col;
        this->width = width;
    }
    ofPolyline poly;
    float x;
    float y;
    float z;

    float width;
    float radius;
    float angleBegin;
    float angleEnd;
    ofColor color;
};

//MOTION
class ArcMotion : public BaseMotion<ArcObj>{
public:
    void draw(){
        int res = 50;
        ofPolyline poly;
        poly.arc(ofPoint(getValue().x, getValue().y, getValue().z), getValue().radius,
                  getValue().radius,
                  getValue().angleBegin, getValue().angleEnd,true,res);
        
        ofFloatColor fc(getValue().color.r/255.,
                        getValue().color.g/255.,
                        getValue().color.b/255.,
                        getValue().color.a/255.);
        ofMesh m;
        ofxPolyToMesh(m,poly,getValue().width);
        ofSetColor(fc);
        m.draw();
    }
    
    void draw2(){
        
    }
};

//MANAGER
class ArcMotionManager : public BaseMotionManager<ArcObj, ArcMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

