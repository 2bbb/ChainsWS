#include "CircleMotionManager.h"

void CircleMotionManager::setup(){
    lerp_function = [] (const CircleObj &lhs, const CircleObj &rhs, float mix){
        return CircleObj{
            ch::lerpT( lhs.pos, rhs.pos, mix ),
            ch::lerpT( lhs.radius, rhs.radius, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}

