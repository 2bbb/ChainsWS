#pragma once

#include "BaseMotionManager.h"
#include "BaseMotion.h"

class SphereObj{
public:
    
    SphereObj():x(0),y(0), z(0), r(0), color(ofColor::white){}
    SphereObj(float x, float y, float z,
            float r,
            const ofColor  & col = ofColor::white){
        this->x = x;
        this->y = y;
        this->z = z;
        
        this->r = r;
        
        this->color = col;
    }
    SphereObj(const ofVec3f & pos,
            const float & r,
            const ofColor  & col = ofColor::white){
        this->x = pos.x;
        this->y = pos.y;
        this->z = pos.z;
        
        this->r = r;
        
        this->color = col;
    }
    
    float x, y, z;
    float r;
    ofColor color;
};

//MOTION
class SphereMotion : public BaseMotion<SphereObj>{
public:
    void draw(){
        ofSetColor(getValue().color);
        ofPushMatrix();
//        billboard();
//        ofDrawCircle(getValue().x, getValue().y, getValue().z, getValue().r);
        ofDrawSphere(getValue().x, getValue().y, getValue().z, getValue().r);
        ofPopMatrix();
    }
//    inline void billboard()
//    {
//        GLfloat m[16];
//        glGetFloatv(GL_MODELVIEW_MATRIX, m);
//
//        float inv_len;
//
//        m[8] = -m[12];
//        m[9] = -m[13];
//        m[10] = -m[14];
//        inv_len = 1. / sqrt(m[8] * m[8] + m[9] * m[9] + m[10] * m[10]);
//        m[8] *= inv_len;
//        m[9] *= inv_len;
//        m[10] *= inv_len;
//
//        m[0] = -m[14];
//        m[1] = 0.0;
//        m[2] = m[12];
//        inv_len = 1. / sqrt(m[0] * m[0] + m[1] * m[1] + m[2] * m[2]);
//        m[0] *= inv_len;
//        m[1] *= inv_len;
//        m[2] *= inv_len;
//
//        m[4] = m[9] * m[2] - m[10] * m[1];
//        m[5] = m[10] * m[0] - m[8] * m[2];
//        m[6] = m[8] * m[1] - m[9] * m[0];
//
//        glLoadMatrixf(m);
//    }
};
class SphereParticleManager : public BaseMotionManager<SphereObj, SphereMotion>{
public:
    //NEED TO MAKE A CUSTOM LERP FUNCTION
    void setup();
    void custom_emit(const SphereObj& start, const SphereObj&end, float duration);
    void custom_emit(const SphereObj& start, const SphereObj&mid, float duration1,
                     const SphereObj& end, float duration2);
};

