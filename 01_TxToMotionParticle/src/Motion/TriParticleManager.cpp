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

