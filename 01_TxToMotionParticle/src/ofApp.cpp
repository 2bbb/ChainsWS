#include "ofApp.h"
#include "ofxPubSubOsc.h"
#include "ofxJsonUtils.h"

//MOTION
#include "ofxChoreograph.h"
#include "CircleMotionManager.h"

using namespace ofxChoreograph;

// circle particle
CircleMotionManager circle_m;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetCircleResolution(90);
    circle_m.setup();

    ofJson setting = ofLoadJson("setting.json");
    ofJson osc_setting = setting["osc"];
    std::uint16_t osc_port = osc_setting["port"];
    ofxSubscribeOsc(osc_port, "/transaction", [=](std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size) {
        float radius = log(input);
        circle_m.emit({ofVec3f(ofGetWidth()/2.0, ofGetHeight()/2.0, 0), radius, ofColor(255, 255, 255)},
                      {ofVec3f(ofRandomWidth(), ofRandomHeight(), 0), radius, ofColor(0, 0, 0)},
                      10);
    });

}

//--------------------------------------------------------------
void ofApp::update(){
    circle_m.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    circle_m.draw();
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
