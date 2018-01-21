#pragma once
#include "BaseMotionManager.h"
#include "BaseMotion.h"

class TriObj{
public:
    TriObj(){} 
    TriObj(const ofVec3f & v1,
           const ofVec3f & v2,
           const ofVec3f & v3,
           const ofVec3f & rot,
           const ofColor  & col = ofColor::white){
        this->v1 = v1;
        this->v2 = v2;
        this->v3 = v3;
        this->rot = rot;
        this->color = col;
    }

    ofColor color;
    ofVec3f v1,v2,v3;
    ofVec3f rot;
};

//MOTION
class TriMotion : public BaseMotion<TriObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofPushMatrix();
        ofVec3f center = (getValue().v1 + getValue().v2 + getValue().v3) / 3.;
        
        ofTranslate(center);
        ofRotateX(getValue().rot.x);
        ofRotateY(getValue().rot.y);
        ofRotateZ(getValue().rot.z);
        ofTranslate(-center);
        ofDrawTriangle(getValue().v1, getValue().v2, getValue().v3);
        ofPopMatrix();
    }
};
class TriParticleManager : public BaseMotionManager<TriObj, TriMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
};

