#include "SphereParticleManager.h"

void SphereParticleManager::setup(){
    lerp_function = [] (const SphereObj &lhs, const SphereObj &rhs, float mix){
        return SphereObj{
            ch::lerpT( lhs.x, rhs.x, mix ),
            ch::lerpT( lhs.y, rhs.y, mix ),
            ch::lerpT( lhs.z, rhs.z, mix ),
            ch::lerpT( lhs.r, rhs.r, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}

void SphereParticleManager::custom_emit(const SphereObj& start, const SphereObj&end, float duration){
    MotionPtr c = make_shared<SphereMotion>();
    c->applyRampTo(start,0, EaseNone(),lerp_function);
    c->appendRampTo(end,  duration, EaseNone(),lerp_function);
    motions.push_back(c);
}

void SphereParticleManager::custom_emit(const SphereObj& start, const SphereObj&mid, float duration1,
                                        const SphereObj& end, float duration2){
    MotionPtr c = make_shared<SphereMotion>();
    c->applyRampTo(start,0, EaseNone(),lerp_function);
    c->appendRampTo(mid,  duration1, EaseNone(),lerp_function);
    c->appendRampTo(end,  duration2, EaseNone(),lerp_function);
    motions.push_back(c);
}
