#include "ofApp.h"
#include "ofxPubSubOsc.h"
#include "ofxJsonUtils.h"

//MOTION
#include "ofxChoreograph.h"
#include "CubeParticleManager.h"

using namespace ofxChoreograph;

// circle particle
CubeParticleManager cube_m;
ofMesh cube;
ofEasyCam cam;
float cube_size = 400;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBoxPrimitive tmpcube(cube_size, cube_size, cube_size);
    cube = tmpcube.getMesh();
    cube_m.setup();
    
    ofJson setting = ofLoadJson("setting.json");
    ofJson osc_setting = setting["osc"];
    std::uint16_t osc_port = osc_setting["port"];
    
    ofxSubscribeOsc(osc_port, "/transaction", [=](std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size) {
        float s = log(input)/3.;
        float hue = ofMap(log10(input), 0,  10, 0, 255);
        
        ofVec3f start = ofVec3f(0, -cube_size/2., 0);
        ofVec3f goal = ofVec3f(0, cube_size/2., 0);
        ofVec3f h(cube_size, s, cube_size);
        ofColor col = ofColor::fromHsb(hue, 255, 255, 100);
        cube_m.emit({start, h, col},
                      {goal, h, col},
                      10,
                      easeNone);
    });
    
    ofEnableDepthTest();
    ofSetFrameRate(60);
}

//--------------------------------------------------------------
void ofApp::update(){
    cube_m.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    cam.begin();
    ofPushMatrix();
    ofRotateY(ofGetElapsedTimef()*10);
    ofRotateX(-1.);
    ofRotateY(-1.);
    cube_m.draw();
    
    ofSetColor(255, 255, 255, 100);
    cube.drawWireframe();
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


