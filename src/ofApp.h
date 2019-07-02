#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofAppEGLWindow.h"
#include "ofxOMXVideoGrabber.h"
#include "OMX_Maps.h"
#include "ofxXmlSettings.h"
#include "videoPlayer.h"
#include "captur.h"
#include "detour.h"
#include "conjur.h"

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


    captur videoGrabber;
    bool hasCapture;
    string captureType;
    bool capturePreview;
    bool captureRecord;


    ofShader 		shader;
    bool useShader;
    bool processShader;
    int lastTime;
// === detour demo
    void sendDetourMessage(int position, int start, int end, int size, float speed, float mix, bool memory_full );
    void detourUpdate();
    bool isDetour;
    bool effectShaderInput;
    detour thisDetour;
    conjur mixConjur;
    conjur effectConjur;
    vector<ofTexture> effectInput;
    ofPixels in_frame;
    ofPixels detour_frame;
    ofPixels out_frame;
    ofTexture in_texture;
    ofTexture detour_texture;
    ofFbo in_fbo;
    ofFbo out_fbo;
    ofFbo mix_fbo;


};
