#include "ofApp.h"
#include "ofxPubSubOsc.h"
#include "ofxJsonUtils.h"

//MOTION
#include "ofxChoreograph.h"
#include "SphereParticleManager.h"

using namespace ofxChoreograph;

// circle particle
SphereParticleManager sphere_m;
ofMesh sphere;
ofEasyCam cam;
//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSpherePrimitive tmpsphere( 300, 20, OF_PRIMITIVE_TRIANGLES );
    sphere = tmpsphere.getMesh();
    
    sphere_m.setup();
    
    ofJson setting = ofLoadJson("setting.json");
    ofJson osc_setting = setting["osc"];
    std::uint16_t osc_port = osc_setting["port"];
    ofxSubscribeOsc(osc_port, "/transaction", [=](std::uint64_t time, std::uint64_t tx_id, double input, double output, std::size_t size) {
        float radius = log(input) /  5.;
        
        int num_vertices = sphere.getNumVertices();
        ofVec3f goal = sphere.getVertices()[ofRandom(num_vertices)];
        ofVec3f start = ofVec3f::zero();
        
        sphere_m.emit({start, radius, ofColor(255, 255, 255, 255)},
                      {goal, radius, ofColor(255, 255, 255, 0)},
                      30, 
                      easeOutQuint);
    });
    
    ofSetFrameRate(60);
    
    ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update(){
    sphere_m.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    
    cam.begin();
    ofPushMatrix();
    ofRotateY(ofGetElapsedTimef()*10.);
    sphere_m.draw();
    auto motions = sphere_m.getMotions();
    for(auto &&motion :motions){
        ofSetColor(motion->getValue().color);
        ofDrawLine(ofVec3f::zero(), motion->getValue().pos);
    }
    
    ofSetColor(255, 255, 255, 50);
    sphere.drawWireframe();
    
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

