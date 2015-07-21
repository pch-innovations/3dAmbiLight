#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);

    //at first you must specify the Ip address of this machine
    //make sure the firewall is deactivated at this point
    artnet.setup("10.0.0.1");
    
    ofSetFrameRate(40);
    fbo.allocate(512, 1, GL_RGB);
    
    movie.loadMovie("movies/fingers.mov");
    movie.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    //create send buffer by ofFbo
    {
        fbo.begin();
        
        ofClear(0);
         
        movie.update();
        movie.draw(0,0);
        
        fbo.end();
        fbo.readToPixels(testImage.getPixelsRef());
    }
    

    //list nodes for sending
    //with subnet / universe
    //artnet.sendDmx("10.7.159.92", 0xf, 0xf, testImage.getPixels(), 512);
    artnet.sendDmx("10.7.159.92", testImage.getPixels(), 512);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    movie.draw(0, 0);
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
