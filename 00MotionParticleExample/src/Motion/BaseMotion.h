#pragma once
#include "ofxChoreograph.h"
#include "ofMain.h"

using namespace ofxChoreograph;

template<typename T>
class BaseMotion{
    using LerpFn = std::function<T (const T&, const T&, float)>;
    
    Timeline timeline_;
    Output<T>output;
public:
    LerpFn lerp_function;
    void setLerpFunction(const LerpFn & lpfn){
        lerp_function = lpfn;
    }
    const LerpFn & getLerpFunction(){
        return lerp_function;
    }
    Timeline & timeline(){
        return timeline_;
    }
    const T & getValue() const{
        return output.value();
    }
    void set(T t){
        timeline().apply(&output).set(t);
    }
    void update(){
        timeline().step(ofGetLastFrameTime());
    }
    void step(Time dt){
        timeline().step(dt);
    }
    // -- time
    Time getLife() {
        return timeUntilFinish() / getDuration();
    }
    Time getOneMinusLife() {
        return 1.0f - getLife();
    }
    Time getDuration(){
        return timeline().getDuration();
    }
    Time timeUntilFinish(){
        timeline().timeUntilFinish();
    }
    
    // -- cue
    void cue(const std::function<void ()> &fn, Time delay){
        timeline().cue(fn, 0);
    }
    //------------loop
    void appendRepeat(const T start, const T end, Time time, float numLoops, const EaseFn & easy_fn = &easeNone, const LerpFn &lerp_fn = &lerpT<T>){
        PhraseRef<T> repeat = makeRamp( start, end, time, easy_fn, lerp_fn);
        timeline().apply(&output).then(makeRepeat(repeat, numLoops));
    }
    void appendPingPong(const T start, const T end, Time time, float numLoops, const EaseFn & easy_fn = &easeNone, const LerpFn &lerp_fn = &lerpT<T>){
        PhraseRef<T> repeat = makeRamp( start, end, time, easy_fn, lerp_fn);
        timeline().apply(&output).then(makePingPong(repeat, numLoops));
    }
    
    PhraseRef<T> appendReverce(const PhraseRef<T>&source){
        return std::make_shared<ReversePhrase<T>>( source);
    }
        
    //-------------append
    void appendSet(T t){
        timeline().append(&output).set(t);
    }
    void appendRampTo(const T goal, Time f, const EaseFn &ease_fn = &easeNone, const LerpFn &lerp_fn = &lerpT<T>){
        auto m = timeline().append(&output);
        m.template then<RampTo>(goal, f, ease_fn, lerp_fn);
    }
    void appendHold(Time f){
        auto m = timeline().append(&output);//
        m.template hold(f);
    }
    void appendProcedure(const typename ProceduralPhrase<T>::Function &fn, Time f){
        auto m = timeline().append(&output);
        m.then(makeProcedure<T>(f, fn));
    }
    
    //--------------apply
    void applySet(T t){
        timeline().apply(&output).set(t);
    }
    
    void applyRampTo(const T goal, Time f, const EaseFn &ease_fn = &easeNone,  const LerpFn &lerp_fn = &lerpT<T>){
        auto m = timeline().apply(&output);
        m.template then<RampTo>(goal, f, ease_fn, lerp_fn);
    }
    void applyHold(Time f){
        auto m = timeline().apply(&output);//
        m.template hold(f);
    }
    void applyProcedure(const typename ProceduralPhrase<T>::Function &fn, Time f){
        auto m = timeline().apply(&output);
        m.then(makeProcedure<T>(f, fn));
    }
    
    bool empty(){
        return timeline().empty();
    }
    void clear(){
        timeline().clear();
    }
};

