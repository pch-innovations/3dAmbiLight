#include "ofApp.h"


/*
 
 TODO:
 
 - use FBO instead of ofImage, or at least ofPixels?
 - Sync
 - GUI for brightness, crop line
 
 */

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetVerticalSync( true );
    
    //at first you must specify the Ip address of this machine
    //make sure the firewall is deactivated at this point
    artnet.setup( MY_IP );
    
    ofSetFrameRate( 30 );
    
    
    ledPixelsL.allocate( LED_WIDTH_L, 1, OF_IMAGE_COLOR );
    ledPixelsC.allocate( LED_WIDTH_C, 1, OF_IMAGE_COLOR );
    ledPixelsR.allocate( LED_WIDTH_R, 1, OF_IMAGE_COLOR );
    ledStrip.allocate( LED_STRIP_LENGTH, 1, OF_IMAGE_COLOR );
    
    playerL.loadMovie( "movies/ambilight-blue.mp4" );
    playerL.play();
    
    playerC.loadMovie( "movies/boost_blue_320.mp4" );
    playerC.play();
    
    playerR.loadMovie( "movies/boost_blue_320.mp4" );
    playerR.play();
    
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetWindowTitle( ofToString( ofGetFrameRate(), 2 ) );
    
    playerL.update();
    playerC.update();
    playerR.update();
    
    //playerL.getPixelsRef().resizeTo( ledPixelsL, OF_INTERPOLATE_NEAREST_NEIGHBOR );
    playerL.getPixelsRef().cropTo( ledPixelsL, 0, 10, 40, 1);
    
    playerC.getPixelsRef().resizeTo( ledPixelsC, OF_INTERPOLATE_NEAREST_NEIGHBOR );
    playerR.getPixelsRef().resizeTo( ledPixelsR, OF_INTERPOLATE_NEAREST_NEIGHBOR );
    
    
    for (int i = 0; i < LED_WIDTH_L; i++) {
        ofColor c = ledPixelsL.getColor( i, 0 );
        c.setBrightness( c.getBrightness() * BRIGHTNESS_L );
        ledPixelsL.setColor( i, 0, c );
    }
    for (int i = 0; i < LED_WIDTH_C; i++) {
        ofColor c = ledPixelsC.getColor( i, 0 );
        c.setBrightness( c.getBrightness() * BRIGHTNESS_C );
        ledPixelsC.setColor( i, 0, c );
    }
    for (int i = 0; i < LED_WIDTH_R; i++) {
        ofColor c = ledPixelsR.getColor( i, 0 );
        c.setBrightness( c.getBrightness() * BRIGHTNESS_R );
        ledPixelsR.setColor( i, 0, c );
    }
    
    ledPixelsL.update();
    ledPixelsC.update();
    ledPixelsR.update();
    
    
    ledPixelsL.getPixelsRef().pasteInto(ledStrip, 0, 0 );
    ledPixelsC.getPixelsRef().pasteInto(ledStrip, LED_WIDTH_L, 0 );
    ledPixelsR.getPixelsRef().pasteInto(ledStrip, LED_WIDTH_L + LED_WIDTH_C, 0 );
     
    /*
    for (int i = 0; i < LED_WIDTH_L; i++) {
        ledStrip.setColor( i, 0, ledPixelsL.getColor( i, 0 ) );
    }
    for (int i = 0; i < LED_WIDTH_C; i++) {
        ledStrip.setColor( LED_WIDTH_L + i, 0, ledPixelsC.getColor( i, 0 ) );
    }
    for (int i = 0; i < LED_WIDTH_R; i++) {
        ledStrip.setColor( LED_WIDTH_L + LED_WIDTH_C + i, 0, ledPixelsR.getColor( i, 0 ) );
    }
     */

    
    ledStrip.update();
    
    artnet.sendDmx( CONTROLLER_IP,
                   ledStrip.getPixels(),
                   LED_STRIP_LENGTH * 3);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    //ledStrip.draw( 0, 0, LED_STRIP_LENGTH*8, 1*8 );
    
    playerL.draw(0, 20, playerL.getWidth() * 8, playerL.getHeight() * 8);
    ledPixelsL.draw( 0, 400, LED_WIDTH_L*8, 1*8 );
    
    playerC.draw(400, 20);
    ledPixelsC.draw( 400, 400, LED_WIDTH_C*8, 1*8 );
    
    playerR.draw(800, 20);
    ledPixelsR.draw( 800, 400, LED_WIDTH_R*8, 1*8 );
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
