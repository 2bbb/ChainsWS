#include "CubeParticleManager.h"

void CubeParticleManager::setup(){
    lerp_function = [] (const CubeObj &lhs, const CubeObj &rhs, float mix){
        return CubeObj{
            ch::lerpT( lhs.x, rhs.x, mix ),
            ch::lerpT( lhs.y, rhs.y, mix ),
            ch::lerpT( lhs.z, rhs.z, mix ),
            ch::lerpT( lhs.w, rhs.w, mix ),
            ch::lerpT( lhs.h, rhs.h, mix ),
            ch::lerpT( lhs.d, rhs.d, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}
