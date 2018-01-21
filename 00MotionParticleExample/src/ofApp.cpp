#include "ofApp.h"

static ofColor randomColor(){
    return ofColor::fromHsb(ofRandom(255), 255, 255);
}
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(90);
    circle_m.setup();
    rect_m.setup();
    cube_m.setup();
    arc_m.setup();
    triangle_m.setup();
    sphere_m.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    circle_m.update();
    rect_m.update();
    cube_m.update();
    arc_m.update();
    triangle_m.update();
    sphere_m.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    circle_m.draw();
    rect_m.draw();
    cube_m.draw();
    arc_m.draw();
    triangle_m.draw();
    sphere_m.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // circle
    // x, y, z, radius, color
    ofVec3f begin_pos(ofGetWidth()/2.0, ofGetHeight()/2.0, 0);
    ofVec3f end_pos(ofRandomWidth(), ofRandomHeight(), 0);
    ofColor begin_color = randomColor();
    ofColor end_color = randomColor();
    ofVec3f begin_size(100,100,100);
    ofVec3f end_size(10,10,10);
    float begin_radius = 100;
    float end_radius = 10;
    if(key == '1'){
        circle_m.emit({begin_pos, begin_radius, begin_color},
                      {end_pos, end_radius, end_color},
                      1);
    }
    //rect
    // pos, w, h, radius, color
    else if(key == '2'){
        rect_m.emit({begin_pos, begin_radius, begin_radius, begin_color},
                      {end_pos, end_radius, end_radius, end_color}, 1);
    }
    // arc
    // pos, radius, width, angle begin, angle end , color
    else if(key == '3'){
        arc_m.emit({begin_pos, begin_radius, 10, 0, ofRandom(360), begin_color},
                      {end_pos, end_radius, 10, 0, ofRandom(360), end_color},
                      1);
    }
    // triangle
    // triangle vertex1,triangle vertex2,triangle vertex3, rotation, color
    else if(key == '4'){
        triangle_m.emit(
        //start triangle
        {
            ofVec3f(ofRandomWidth(), ofRandomHeight(), 0),
            ofVec3f(ofRandomWidth(), ofRandomHeight(), 0),
            ofVec3f(ofRandomWidth(), ofRandomHeight(), 0),
            ofVec3f(ofRandom(360),ofRandom(360),ofRandom(360)),
            randomColor()
        }
                      ,
        {
            ofVec3f(ofRandomWidth(), ofRandomHeight(), 0),
            ofVec3f(ofRandomWidth(), ofRandomHeight(), 0),
            ofVec3f(ofRandomWidth(), ofRandomHeight(), 0),
            ofVec3f(ofRandom(360),ofRandom(360),ofRandom(360)),
            randomColor()
        }
                      ,
                      1
                      );
    }
    // cube
    // pos, size, color
    else if(key == '5'){
        cube_m.emit({begin_pos, begin_size, randomColor()},
                      {end_pos, end_size, randomColor()},
                      1);
    }
    // shpere
    // pos, radius, color
    else if(key == '6'){
        sphere_m.emit({begin_pos, begin_radius, randomColor()},
                    {end_pos, end_radius, randomColor()},
                    1);
    }
    // pos, radius, color
    else if(key == '7'){
        sphere_m.emit({begin_pos, 5,randomColor()},
                      {end_pos, 0, randomColor()},
                      10);
    }

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
