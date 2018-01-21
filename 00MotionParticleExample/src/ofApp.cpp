#include "ofApp.h"

static ofColor randomColor(){
    return ofColor::fromHsb(ofRandom(255), 255, 255);
}
ofEasyCam cam;
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
    if(key == '1'){
        circle_m.emit({ofRandomWidth(), ofRandomHeight(), 0, 100, randomColor()},
                      {ofRandomWidth(), ofRandomHeight(), 0, 170, randomColor()},
                      1);
    }
    //rect
    // x, y, z, w, h, radius, color
    else if(key == '2'){
        rect_m.emit({ofRandomWidth(), ofRandomHeight(), 0, 100, 100, randomColor()},
                      {ofRandomWidth(), ofRandomHeight(), 0, 10, 10, randomColor()}, 1);
    }
    // arc
    // x, y, z, radius, width, angle begin, angle end , color
    else if(key == '3'){
        arc_m.emit({ofRandomWidth(), ofRandomHeight(), 0, 100, 100, 0, ofRandom(360), randomColor()},
                      {ofRandomWidth(), ofRandomHeight(), 0, 10, 10, 0, ofRandom(360), randomColor()},
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
    // x, y, z, w, h, d, color
    else if(key == '5'){
        cube_m.emit({ofRandomWidth(), ofRandomHeight(), 0, 100, 100, 100, randomColor()},
                      {ofRandomWidth(), ofRandomHeight(), 0, 0, 0, 0, randomColor()},
                      1);
    }
    // shpere
    // x, y, z, radius, color
    else if(key == '6'){
        sphere_m.emit({ofRandomWidth(), ofRandomHeight(), 110 , 100, randomColor()},
                    {ofRandomWidth(), ofRandomHeight(), 0, 0, randomColor()},
                    1);
    }
    else if(key == '7'){
        sphere_m.emit({static_cast<float>(ofGetWidth()/2.0), static_cast<float>(ofGetHeight()/2.0), 0 , 5, randomColor()},
                      {ofRandomWidth(), ofRandomHeight(), 1, 0, randomColor()},
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
