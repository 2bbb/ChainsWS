#include "ArcMotionManager.h"

void ArcMotionManager::setup(){
    lerp_function = [] (const ArcObj &lhs, const ArcObj &rhs, float mix){
        return ArcObj{
            ch::lerpT( lhs.pos, rhs.pos, mix ),
            ch::lerpT( lhs.radius, rhs.radius, mix ),
            ch::lerpT( lhs.width, rhs.width, mix ),
            ch::lerpT( lhs.angleBegin, rhs.angleBegin, mix ),
            ch::lerpT( lhs.angleEnd, rhs.angleEnd, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}
