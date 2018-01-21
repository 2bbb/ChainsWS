//
//  AllMotionManager.hpp
//  00MotionParticleExample
//
//  Created by rhizomacbookproretina20 on 2018/01/21.
//

#pragma once
#include <stdio.h>

#include "CircleMotionManager.h"
#include "RectMotionManager.h"
#include "CubeParticleManager.h"
#include "ArcMotionManager.h"
#include "TriParticleManager.h"
#include "SphereParticleManager.h"

class AllMotionManager{
public:
    void setup(){
        circle_m.setup();
        rect_m.setup();
        cube_m.setup();
        arc_m.setup();
        triangle_m.setup();
        sphere_m.setup();
    }
    void update(){
        circle_m.update();
        rect_m.update();
        cube_m.update();
        arc_m.update();
        triangle_m.update();
        sphere_m.update();

    }
    void draw(){
        circle_m.draw();
        rect_m.draw();
        cube_m.draw();
        arc_m.draw();
        triangle_m.draw();
        sphere_m.draw();
    }
    // circle particle
    CircleMotionManager circle_m;
    RectMotionManager rect_m;
    CubeParticleManager cube_m;
    ArcMotionManager arc_m;
    TriParticleManager triangle_m;
    SphereParticleManager sphere_m;
};
