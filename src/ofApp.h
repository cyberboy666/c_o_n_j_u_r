#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void gotMessage(ofMessage msg);
        void receiveMessages();
        void checkPlayerStatuses();
        void checkPlayerPositions();
        void sendFloatMessage(string address, float value);
        void sendStringMessage(string address, string value);
        void drawPlayerWithAlpha(ofVideoPlayer player, int alpha);
        void updateStatus(string playerName, string status);

    ofxOscReceiver receiver;
    ofxOscSender sender;

    ofGLESWindowSettings   settings;
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
    int lastTime;
    ofShader 		nowShader;
    ofFbo fbo;
};
