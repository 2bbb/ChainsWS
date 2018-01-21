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
//        ofMesh mesh;
//
//        ofVec3f v1 = getValue().v1;
//        ofVec3f v2 = getValue().v2;
//        ofVec3f v3 = getValue().v3;
//        ofVec3f v4 = (v1 + center) /2.0;
//        ofVec3f v5 = (v2 + center) /2.0;
//        ofVec3f v6 = (v3 + center) /2.0;
//
//        mesh.addVertex(v1);
//        mesh.addVertex(v2);
//        mesh.addVertex(v3);
//        mesh.addVertex(v4);
//        mesh.addVertex(v5);
//        mesh.addVertex(v6);
//
//        mesh.addIndex(0);
//        mesh.addIndex(1);
//        mesh.addIndex(3);
//
//        mesh.addIndex(3);
//        mesh.addIndex(1);
//        mesh.addIndex(4);
//
//        mesh.addIndex(5);
//        mesh.addIndex(4);
//        mesh.addIndex(1);
//
//        mesh.addIndex(5);
//        mesh.addIndex(1);
//        mesh.addIndex(2);
//
//        mesh.addIndex(0);
//        mesh.addIndex(3);
//        mesh.addIndex(5);
//
//        mesh.addIndex(0);
//        mesh.addIndex(5);
//        mesh.addIndex(2);
//
//        mesh.draw();
        
        ofDrawTriangle(getValue().v1, getValue().v2, getValue().v3);
        ofPopMatrix();
    }
};
class TriParticleManager : public BaseMotionManager<TriObj, TriMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
    void custom_emit(const TriObj& start, const TriObj&end, float duration);
    void custom_emit(const TriObj& start, const TriObj&mid, float duration1,
                     const TriObj&end, float duration2);
};

