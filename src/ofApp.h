#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxGui.h"
#include "ofxUDPManager.h"


class ofApp : public ofBaseApp{
    
public:

    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

	void syncPlayers(float pct);
    
    ofxArtnet artnet;
	bool bArtnet;

	ofxUDPManager udpConnection;
    
    ofImage ledStrip, ledPixelsL, ledPixelsC, ledPixelsR;
    ofVideoPlayer playerL, playerC, playerR;
    
    ofParameter<float> brightnessL, brightnessC, brightnessR;
    ofParameter<float> saturationL, saturationC, saturationR;
    ofParameter<int> scanYL, scanYC, scanYR;
    
    ofxPanel gui;
    bool bShowGui;
    
};
