#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofAppEGLWindow.h"
#include "ofxRPiCameraVideoGrabber.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
        void receiveMessages();
        void checkPlayerStatuses();
        void checkPlayerPositions();
        void sendFloatMessage(string address, float value);
        void sendStringMessage(string address, string value);
        void drawPlayerWithAlpha(ofVideoPlayer player, int alpha);
        void updateStatus(string playerName, string status);
        void setupCapture();

    ofxOscReceiver receiver;
    ofxOscSender sender;

    ofGLESWindowSettings   settings;

    ofFbo fbo;

    ofVideoPlayer 		aPlayer;
    ofVideoPlayer 		bPlayer;
    ofVideoPlayer 		cPlayer;
    int aAlpha;
    int bAlpha;
    int cAlpha;
    float aEnd;
    float bEnd;
    float cEnd;
    float aStart;
    float bStart;
    float cStart;
    string aStatus;
    string bStatus;
    string cStatus;

    ofxRPiCameraVideoGrabber videoGrabber;
    OMXCameraSettings omxCameraSettings;
    bool capturePreview;

    ofShader 		shader;
    bool useShader;
    bool processShader;
    float shaderParams[8];
    int paramNum;

    int lastTime;

};
