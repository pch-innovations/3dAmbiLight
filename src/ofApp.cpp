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
	
	cout << "Setting up Artnet connection from " << MY_IP << " to " << CONTROLLER_IP << endl;
	artnet.setup( MY_IP );
	ledPixelsL.allocate(LED_WIDTH_L, 1, OF_IMAGE_COLOR);
	ledPixelsC.allocate(LED_WIDTH_C, 1, OF_IMAGE_COLOR);
	ledPixelsR.allocate(LED_WIDTH_R, 1, OF_IMAGE_COLOR);
	ledStrip.allocate(LED_STRIP_LENGTH, 1, OF_IMAGE_COLOR);
    
	// UDP for Sync Signal

	cout << "Listening to UDP sync signal on port " << UDP_PORT << endl;
	udpConnection.Create();
	udpConnection.Bind(UDP_PORT);
	udpConnection.SetNonBlocking(true);
    
    // MOVIE PLAYER
    
	cout << "Loading movies..." << endl;
	playerL.loadMovie("movies/ambilight-sequenz1.mp4" );
	playerL.play();
	cout << "Left: " << playerL.getMoviePath() << ", " << playerL.getWidth() << "x" << playerL.getHeight() << "px, " << playerL.getDuration() << "s" << endl;
    playerC.loadMovie( "movies/ambilight-sequenz1.mp4" );
	playerC.play();
	cout << "Left: " << playerC.getMoviePath() << ", " << playerC.getWidth() << "x" << playerC.getHeight() << "px, " << playerC.getDuration() << "s" << endl;
	playerR.loadMovie( "movies/ambilight-sequenz1.mp4" );
	playerR.play();
	cout << "Left: " << playerR.getMoviePath() << ", " << playerR.getWidth() << "x" << playerR.getHeight() << "px, " << playerR.getDuration() << "s" << endl;

    // GUI

    gui.setup("3D Ambilight");
    bShowGui = true;

	gui.add( bArtnet.set( "LED Lights", false ) );
	gui.add( bUdpSync.set( "Video Sync", false ) );
    
    gui.add( brightnessL.set( "Brightness Left", 1.0, 0, 10 ) );
    gui.add( saturationL.set( "Saturation Left", 1.0, 0, 5 ) );
    gui.add( scanYL.set( "Scan Row Left", playerL.getHeight() / 2, 0, playerL.getHeight() ) );
    
    gui.add( brightnessC.set( "Brightness Center", 1.0, 0, 10 ) );
    gui.add( saturationC.set( "Saturation Center", 1.0, 0, 5 ) );
    gui.add( scanYC.set( "Scan Row Center", playerC.getHeight() / 2, 0, playerC.getHeight() ) );
    
    gui.add( brightnessR.set( "Brightness Right", 1.0, 0, 10 ) );
    gui.add( saturationR.set( "Saturation Right", 1.0, 0, 5 ) );
    gui.add( scanYR.set( "Scan Row Right", playerR.getHeight() / 2, 0, playerR.getHeight() ) );
 
	cout << "Setup finished." << endl;
}

//--------------------------------------------------------------
void ofApp::update() {
    ofSetWindowTitle( ofToString( ofGetFrameRate(), 2 ) );

	if (bUdpSync) {
		char udpMessage[1000];
		udpConnection.Receive(udpMessage, 1000);
		string message = udpMessage;
		if (message != "") {
			cout << "UDP MESSAGE " << message << endl;
			float target = 0;
			target = ofToFloat(message);
			syncPlayers(target);
		}
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
    
    
    int scaleL = 6;
    playerL.draw( 0, 20, playerL.getWidth() * scaleL, playerL.getHeight() * scaleL);
    ledPixelsL.draw( 0, 400, LED_WIDTH_L*scaleL, 1*scaleL );
    
    ofPushStyle();
    ofSetColor( ofColor::white );
    ofNoFill();
    ofRect( 0, 20 + scanYL * scaleL, LED_WIDTH_L * scaleL, scaleL );
    ofPopStyle();
    
    
    int scaleC = 6;
    playerC.draw(400, 20, playerC.getWidth() * scaleC,  playerC.getHeight() * scaleC);
    ledPixelsC.draw( 400, 400, LED_WIDTH_C*scaleC, 1*scaleC );
    
    ofPushStyle();
    ofSetColor( ofColor::white );
    ofNoFill();
    ofRect( 400, 20 + scanYC * scaleC, LED_WIDTH_C * scaleC, scaleC );
    ofPopStyle();
    
    
    int scaleR = 6;
    playerR.draw(800, 20, playerR.getWidth() * scaleR,  playerR.getHeight() * scaleR);
    ledPixelsR.draw( 800, 400, LED_WIDTH_R*scaleR, 1*scaleR );
    
    ofPushStyle();
    ofSetColor( ofColor::white );
    ofNoFill();
    ofRect( 800, 20 + scanYR * scaleR, LED_WIDTH_R * scaleR, scaleR );
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
		case 's':
			bUdpSync = !bUdpSync;
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
