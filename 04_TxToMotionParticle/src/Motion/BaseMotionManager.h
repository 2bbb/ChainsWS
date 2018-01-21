#pragma once
#include "ofMain.h"
#include "ofxChoreograph.h"
#include <array>
using namespace ofxChoreograph;

template<typename T1, typename T2>
class BaseMotionManager
{
public:
    using LerpFn = std::function<T1 (const T1&, const T1&, float)>;
    LerpFn lerp_function;
    using MotionPtr = shared_ptr<T2>;
    vector<MotionPtr>motions;
    const vector<MotionPtr> & getMotions(){
        return motions;
    }
    int size(){
        return motions.size();
    }
    
    void update(){
        for(auto &v:motions){
            v->update();
        }
        auto erase_func = [](MotionPtr p){return p->empty();};
        motions.erase(remove_if(begin(motions), end(motions), erase_func), end(motions));
    }
    void draw(){
        for(auto &v: motions){
            v->draw();
        }
    }
    void emit(const T1 & start, const T1 & end, Time dur, const EaseFn &ease_fn = &easeNone){
        MotionPtr c = make_shared<T2>();
        c->applyRampTo(start, 0, ease_fn, lerp_function);
        c->appendRampTo(end, dur, ease_fn, lerp_function);
        motions.emplace_back(c);
    }
};

