#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofAppEGLWindow.h"
#include "ofxOMXVideoGrabber.h"
#include "OMX_Maps.h"
#include "ofxXmlSettings.h"
#include "videoPlayer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
        void receiveMessages();
        void setFrameSizeFromFile();
        void checkPlayerStatuses();
        void checkPlayerPositions();
        void sendFloatMessage(string address, float value);
        void sendStringMessage(string address, string value);
        void drawCaptureAndPlayers();
        void drawPlayerIfPlayingOrPaused(videoPlayer player);
        void updateStatus(videoPlayer& player, string statusValue);
        void setupCapture(string captureType);

    ofxOscReceiver receiver;
    ofxOscSender sender;

    ofGLESWindowSettings   settings;
    ofxXmlSettings xmlSettings;

    ofFbo fbo;
    ofFbo fboTwo;

    videoPlayer 		aPlayer;
    videoPlayer 		bPlayer;
    videoPlayer 		cPlayer;


    ofxOMXVideoGrabber videoGrabber;
    ofxOMXCameraSettings omxCameraSettings;
    bool hasCapture;
    bool capturePreview;
    bool captureRecord;


    ofShader 		shader;
    bool useShader;
    bool processShader;
    float shaderParams[8];
    int paramNum;
    int shaderInputCount;
    int lastTime;

};
