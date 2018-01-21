#include "SphereParticleManager.h"

void SphereParticleManager::setup(){
    lerp_function = [] (const SphereObj &lhs, const SphereObj &rhs, float mix){
        return SphereObj{
            ch::lerpT( lhs.pos, rhs.pos, mix ),
            ch::lerpT( lhs.r, rhs.r, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}

