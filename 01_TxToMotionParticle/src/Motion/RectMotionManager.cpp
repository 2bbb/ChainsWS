#include "RectMotionManager.h"

void RectMotionManager::setup(){
    lerp_function = [] (const RectObj &lhs, const RectObj &rhs, float mix){
        return RectObj{
            ch::lerpT( lhs.pos, rhs.pos, mix ),
            ch::lerpT( lhs.w, rhs.w, mix ),
            ch::lerpT( lhs.h, rhs.h, mix ),
            ch::lerpT( lhs.color, rhs.color, mix)
        };
    };
}

