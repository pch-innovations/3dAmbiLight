#pragma once

#include "ofMain.h"
#include "ofxArtnet.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{
    
    const char* MY_IP = "10.0.0.1";
    const char* CONTROLLER_IP = "10.7.159.92";
    
    const int LED_WIDTH_L = 40; // number of leds for strip 1
    const int LED_WIDTH_C = 40;
    const int LED_WIDTH_R = 40;
    const int LED_STRIP_LENGTH = 120;
    
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
    
    ofxArtnet artnet;
    
    ofImage ledStrip, ledPixelsL, ledPixelsC, ledPixelsR;
    ofVideoPlayer playerL, playerC, playerR;
    
    ofParameter<float> brightnessL, brightnessC, brightnessR;
    ofParameter<float> saturationL, saturationC, saturationR;
    ofParameter<int> scanYL, scanYC, scanYR;
    
    ofxPanel gui;
    bool bShowGui;
    
};
