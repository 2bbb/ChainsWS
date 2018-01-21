#include "RectMotionManager.h"

void RectMotionManager::setup(){
    lerp_function = [] (const RectObj &lhs, const RectObj &rhs, float mix){
        return RectObj{
            ch::lerpT( lhs.x, rhs.x, mix ),
            ch::lerpT( lhs.y, rhs.y, mix ),
            ch::lerpT( lhs.z, rhs.z, mix ),
            ch::lerpT( lhs.w, rhs.w, mix ),
            ch::lerpT( lhs.h, rhs.h, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}
void RectMotionManager::custom_emit(const RectObj & start, const RectObj & end, float dur){
    MotionPtr c = make_shared<RectMotion>();
    c->applyRampTo(start, 0, EaseInOutQuad(), lerp_function);
    c->appendRampTo(end, dur, EaseInOutQuad(), lerp_function);
    motions.push_back(c);
}

void RectMotionManager::procedure_emit(){
    float duration = 1.0f;
    std::function<RectObj (float t1, float t2)> fnc = [](float t1, float t2){
        return RectObj{0,1,2,3,4};
    };
    MotionPtr c = make_shared<RectMotion>();
    c->applyProcedure(fnc, duration);
    motions.push_back(c);
}
