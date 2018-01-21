#include "CircleMotionManager.h"

void CircleMotionManager::setup(){
    lerp_function = [] (const CircleObj &lhs, const CircleObj &rhs, float mix){
        return CircleObj{
            ch::lerpT( lhs.x, rhs.x, mix ),
            ch::lerpT( lhs.y, rhs.y, mix ),
            ch::lerpT( lhs.z, rhs.z, mix ),

            ch::lerpT( lhs.radius, rhs.radius, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}
void CircleMotionManager::custom_emit(){
    float duration = 1.0f;
    std::function<CircleObj (float t1, float t2)> fnc = [](float t1, float t2){
        return CircleObj{ofGetWidth()/2.f, ofGetHeight()/2.f, 0, 0, ofColor::black};
    };
    MotionPtr c = make_shared<CircleMotion>();
    c->applyProcedure(fnc, duration);
    motions.push_back(c);
}
