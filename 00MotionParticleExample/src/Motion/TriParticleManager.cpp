#include "TriParticleManager.h"

void TriParticleManager::setup(){
    lerp_function = [] (const TriObj &lhs, const TriObj &rhs, float mix){
        return TriObj{
            ch::lerpT( lhs.v1, rhs.v1, mix ),
            ch::lerpT( lhs.v2, rhs.v2, mix ),
            ch::lerpT( lhs.v3, rhs.v3, mix ),
            ch::lerpT( lhs.rot, rhs.rot, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}

void TriParticleManager::custom_emit(const TriObj& start, const TriObj&end, float duration){
    MotionPtr c = make_shared<TriMotion>();
    c->applyRampTo(start,0, EaseNone(),lerp_function);
    c->appendRampTo(end,  duration, EaseNone(),lerp_function);
    motions.push_back(c);
}

void TriParticleManager::custom_emit(const TriObj& start, const TriObj&mid, float duration1,
                                      const TriObj& end, float duration2){
    MotionPtr c = make_shared<TriMotion>();
    c->applyRampTo(start,0, EaseNone(),lerp_function);
    c->appendRampTo(mid,  duration1, EaseNone(),lerp_function);
    c->appendRampTo(end,  duration2, EaseNone(),lerp_function);
    motions.push_back(c);
}
