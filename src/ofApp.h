#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofAppEGLWindow.h"
#include "ofxXmlSettings.h"
#include "videoPlayer.h"
#include "captur.h"
#include "detour.h"
#include "conjur.h"
#include "recurVideoPlayer.h"

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
        ofFbo applyEffectShaderChain(vector<ofTexture> effectInput);
        void drawPlayerIfPlayingOrPaused(recurVideoPlayer& player);
        void updateStatus(recurVideoPlayer& player, string statusValue);
        void setupCapture(string captureType);

    ofxOscReceiver receiver;
    ofxOscSender sender;

    ofGLESWindowSettings   settings;
    ofxXmlSettings xmlSettings;

    ofFbo fbo;
    
    string playerType;
    recurVideoPlayer 		aPlayer;
    recurVideoPlayer 		bPlayer;
    recurVideoPlayer 		cPlayer;


    captur videoGrabber;
    bool hasCapture;
    string captureType;
    bool capturePreview;
    bool captureRecord;
    int framerate;

    ofShader 		shader;
    bool useShader;
    int lastTime;
// === detour demo
    void sendDetourMessage(int position, int start, int end, int size, float speed, float mix, bool memory_full );
    void detourUpdate();
    bool isDetour;
    bool isDetourDelay;
    bool isFeedback;
    bool effectShaderInput;
    detour thisDetour;
    conjur mixShader;
    conjur effectShader0;
    conjur effectShader1;
    conjur effectShader2;
    bool effectShader0active;
    bool effectShader1active;
    bool effectShader2active;
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
