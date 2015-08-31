#include "ofApp.h"


/*
 
 TODO:
 
 - Sync
 
 */


const char* MY_IP = "10.0.0.1";
const char* CONTROLLER_IP = "10.7.159.92";
const int UDP_PORT = 3839;
    
const int LED_WIDTH_L = 40; // number of leds for strip 1
const int LED_WIDTH_C = 40;
const int LED_WIDTH_R = 40;
const int LED_STRIP_LENGTH = 120;


//--------------------------------------------------------------
void ofApp::setup() {
    
    ofSetVerticalSync( true );

	ofSetFrameRate(30);


	// ARTNET / DMX
    // make sure the firewall is deactivated at this point
    
	artnet.setup( MY_IP );
	bArtnet = false;
	ledPixelsL.allocate(LED_WIDTH_L, 1, OF_IMAGE_COLOR);
	ledPixelsC.allocate(LED_WIDTH_C, 1, OF_IMAGE_COLOR);
	ledPixelsR.allocate(LED_WIDTH_R, 1, OF_IMAGE_COLOR);
	ledStrip.allocate(LED_STRIP_LENGTH, 1, OF_IMAGE_COLOR);
    
	// UDP for Sync Signal

	udpConnection.Create();
	udpConnection.Bind(UDP_PORT);
	udpConnection.SetNonBlocking(true);
    
    // MOVIE PLAYER
    
	playerL.loadMovie("movies/ambilight-blue.mp4" );
	playerL.play();
    playerC.loadMovie( "movies/boost_blue_320.mp4" );
	playerC.play();
    playerR.loadMovie( "movies/boost_blue_320.mp4" );
	playerR.play();
    
    // GUI

    gui.setup("3D Ambilight");
    bShowGui = true;
    
    gui.add( brightnessL.set( "Brightness Left", 1.0, 0, 10 ) );
    gui.add( saturationL.set( "Saturation Left", 1.0, 0, 5 ) );
    gui.add( scanYL.set( "Scan Row Left", playerL.getHeight() / 2, 0, playerL.getHeight() ) );
    
    gui.add( brightnessC.set( "Brightness Center", 1.0, 0, 10 ) );
    gui.add( saturationC.set( "Saturation Center", 1.0, 0, 5 ) );
    gui.add( scanYC.set( "Scan Row Center", playerC.getHeight() / 2, 0, playerC.getHeight() ) );
    
    gui.add( brightnessR.set( "Brightness Right", 1.0, 0, 10 ) );
    gui.add( saturationR.set( "Saturation Right", 1.0, 0, 5 ) );
    gui.add( scanYR.set( "Scan Row Right", playerR.getHeight() / 2, 0, playerR.getHeight() ) );
 
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetWindowTitle( ofToString( ofGetFrameRate(), 2 ) );

	char udpMessage[1000];
	udpConnection.Receive(udpMessage, 1000);
	string message = udpMessage;
	if (message != "") {
		cout << "UDP MESSAGE " << message << endl;
		float target = 0;
		target = ofToFloat(message);
		syncPlayers(target);
	}
    
	playerL.update();
    playerC.update();
    playerR.update();
    
    //playerL.getPixelsRef().resizeTo( ledPixelsL, OF_INTERPOLATE_NEAREST_NEIGHBOR );
    playerL.getPixelsRef().cropTo( ledPixelsL, 0, scanYL, LED_WIDTH_L, 1);
    playerC.getPixelsRef().cropTo( ledPixelsC, 0, scanYL, LED_WIDTH_C, 1);
    playerR.getPixelsRef().cropTo( ledPixelsR, 0, scanYL, LED_WIDTH_R, 1);
    
    
    for (int i = 0; i < LED_WIDTH_L; i++) {
        ofColor c = ledPixelsL.getColor( i, 0 );
        c.setBrightness( c.getBrightness() * brightnessL );
        c.setSaturation( c.getSaturation() * saturationL );
        ledPixelsL.setColor( i, 0, c );
    }
    for (int i = 0; i < LED_WIDTH_C; i++) {
        ofColor c = ledPixelsC.getColor( i, 0 );
        c.setBrightness( c.getBrightness() * brightnessC );
        c.setSaturation( c.getSaturation() * saturationC );
        ledPixelsC.setColor( i, 0, c );
    }
    for (int i = 0; i < LED_WIDTH_R; i++) {
        ofColor c = ledPixelsR.getColor( i, 0 );
        c.setBrightness( c.getBrightness() * brightnessR );
        c.setSaturation( c.getSaturation() * saturationR );
        ledPixelsR.setColor( i, 0, c );
    }
    
    ledPixelsL.update();
    ledPixelsC.update();
    ledPixelsR.update();
    
    ledPixelsL.getPixelsRef().pasteInto(ledStrip, 0, 0 );
    ledPixelsC.getPixelsRef().pasteInto(ledStrip, LED_WIDTH_L, 0 );
    ledPixelsR.getPixelsRef().pasteInto(ledStrip, LED_WIDTH_L + LED_WIDTH_C, 0 );
    
    ledStrip.update();
    
	if (bArtnet) {
		artnet.sendDmx(CONTROLLER_IP,
			ledStrip.getPixels(),
			LED_STRIP_LENGTH * 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    
    int scaleL = 8;
    playerL.draw( 0, 20, playerL.getWidth() * 8, playerL.getHeight() * 8);
    ledPixelsL.draw( 0, 400, LED_WIDTH_L*8, 1*8 );
    
    ofPushStyle();
    ofSetColor( ofColor::white );
    ofNoFill();
    ofRect( 0, 20 + scanYL * 8, LED_WIDTH_L * 8, 8 );
    ofPopStyle();
    
    
    int scaleC = 1;
    playerC.draw(400, 20, playerC.getWidth() * scaleC,  playerC.getHeight() * scaleC);
    ledPixelsC.draw( 400, 400, LED_WIDTH_C*8, 1*8 );
    
    ofPushStyle();
    ofSetColor( ofColor::white );
    ofNoFill();
    ofRect( 400, 20 + scanYC * scaleC, LED_WIDTH_C * scaleC, 8 );
    ofPopStyle();
    
    
    int scaleR = 1;
    playerR.draw(800, 20, playerR.getWidth() * scaleR,  playerR.getHeight() * scaleR);
    ledPixelsR.draw( 800, 400, LED_WIDTH_R*8, 1*8 );
    
    ofPushStyle();
    ofSetColor( ofColor::white );
    ofNoFill();
    ofRect( 800, 20 + scanYR * scaleR, LED_WIDTH_R * scaleR, 8 );
    ofPopStyle();
    
    
    
    if ( bShowGui )
        gui.draw();
    
}

void ofApp::syncPlayers(float pct) {
	playerL.setPosition(0);
	playerC.setPosition(0);
	playerR.setPosition(0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
		case 'a':
			bArtnet = !bArtnet;
			break;
        case 'f':
            ofToggleFullscreen();
            break;
		case 'r':
			syncPlayers( 0 );
			break;
        case OF_KEY_TAB:
            bShowGui = !bShowGui;
            break;
        default:
            break;
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
