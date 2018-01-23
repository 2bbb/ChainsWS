#include "ofApp.h"
#include "ofxPubSubOsc.h"
#include "ofxJsonUtils.h"

//MOTION
#include "ofxChoreograph.h"
#include "ArcMotionManager.h"

using namespace ofxChoreograph;

ArcMotionManager arc_m;
ofEasyCam cam;
float arc_radius = 400;
//--------------------------------------------------------------
void ofApp::setup(){
    
    arc_m.setup();
    
    ofJson setting = ofLoadJson("setting.json");
    ofJson osc_setting = setting["osc"];
    std::uint16_t osc_port = osc_setting["port"];
    
    ofxSubscribeOsc(osc_port, "/transaction", [=](std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size) {
        ofVec3f start(0, 0, -700);
        ofVec3f goal(0, 0, 0);
        float width = log10(input) * 3.;
        float hue = ofMap(log10(input), 0,  10, 0, 255);
        ofColor col_start = ofColor::fromHsb(hue, 255, 255, 200);
        ofColor col_end = ofColor::fromHsb(hue, 255, 255, 0);
        arc_m.emit({start, 1         , width, 1, 2, col_start},
                   {goal , arc_radius, width, 1, 360, col_end},
                    10,
                      easeOutSine);
    });
    
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    arc_m.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    cam.begin();
    ofPushMatrix();
    arc_m.draw();
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}


