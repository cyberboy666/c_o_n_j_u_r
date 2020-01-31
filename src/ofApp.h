#pragma once
// #define TARGET_RASPBERRY_PI 0
#include "ofMain.h"
#include "ofxOsc.h"
#ifdef TARGET_RASPBERRY_PI
#include "ofAppEGLWindow.h"
#endif
#include "ofxXmlSettings.h"
#include "videoPlayer.h"
#include "captur.h"
#include "detour.h"
#include "conjur.h"
#include "recurVideoPlayer.h"
#include <unordered_map>
#define UNIFORM_F_INIT 0.0
// #include "ofxGui.h"
// struct fxNode {
//   conjur shader;
//   fxNode next;
//   bool isActive ;
//   vector<fxNode> toVector();
//   void setup();
//   
// }
typedef string Id; 
typedef unordered_map<Id, string> Attributes;
// typedef unordered_map<Id, Command> Nodemap;
class ofxNode {

public: 
  Attributes attr;
  Id id;
  conjur shader;
  bool isActive;
  ofxNode(Attributes att, Id i, conjur s, bool isa) {
    attr = att;
    id = i;
    shader = s;
    isActive = isa;
  }
  ofxNode() {
    conjur shader;
    attr = {{}};
    id = "NOID";
    shader = shader;
    isActive = true;
  }
};
enum Action {LOAD_FILE, NOTHING, UPDATE_UNIFORM, ROTATE, TOGGLE_ACTIVE };
typedef unordered_map<Id, ofxNode> Nodemap;
typedef unordered_map<Id, Action> actionMap;
// typedef unordered_map<Id, string> OSCmap;


class Command {
public:
  Action commandType;
  Id sourceId; // allows us to lookup the shader/whatever to use
  int arg1; // use ints again to look up shader files, for exmaple
  int arg2; // use ints again to look up shader files, for exmaple

};

class ofApp : public ofBaseApp{
	public:
                Nodemap nodes;
		void setup();
		void update();
		void draw();
		void drawScreen();
		void keyPressed(int key);
  void printStatus();
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

    vector<Id> nodeOrder;
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
    int strobe;

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

  //    vector<fxNode> orderedFX;
  //    vector<vxNode> fxTree;
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
