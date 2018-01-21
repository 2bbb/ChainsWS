#include "CubeParticleManager.h"

void CubeParticleManager::setup(){
    lerp_function = [] (const CubeObj &lhs, const CubeObj &rhs, float mix){
        return CubeObj{
            ch::lerpT( lhs.pos, rhs.pos, mix ),
            ch::lerpT( lhs.size, rhs.size, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}
