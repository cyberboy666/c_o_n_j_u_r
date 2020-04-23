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
#include "ofxAssimpModelLoader.h"
#include "ofxJSON.h"
#include "ofxAutoReloadedShader.h"
#include "recurNode.h"
// #inlucde "ofxAutoReloadShader"
#define UNIFORM_F_INIT 0.0
typedef string Id; 
enum Action {LOAD_FILE, NOTHING, UPDATE_UNIFORM, ROTATE, TOGGLE_ACTIVE };
typedef unordered_map<Id, Action> actionMap;
typedef unordered_map<Id, shaderNode> recurGraph;
static actionMap actions = { { { "LOAD_FILE", LOAD_FILE}, {"UPDATE_UNIFORM", UPDATE_UNIFORM}, {"TOGGLE_ACTIVE", TOGGLE_ACTIVE} } };
class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		void drawScreen();
		void keyPressed(int key);

  recurGraph graph;
  string sceneConfigPath;
  ofxJSONElement sceneConfig;
  vector<Id> nodeOrder;
  void setupGraph();

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
    ofImage img;
   unordered_map<string, string> addressMap;
    vector<shaderNode> threeShaderLayers;
  unordered_map<Id, ofTexture> textureMap;
  unordered_map<Id, int> textureCount;
    vector<ofTexture> effectInput;
    ofPixels in_frame;
    ofPixels detour_frame;
    ofPixels out_frame;
    ofTexture in_texture;
    ofTexture detour_texture;
    ofFbo in_fbo;
    ofFbo out_fbo;
    ofFbo mix_fbo;
// ======================
//    3D  Stuff
  ofTexture modelTex;
  ofMesh mesh;
  ofxAssimpModelLoader model;
  ofEasyCam camera;
  ofxAutoReloadedShader modelShader;
  bool use3D;
  bool modelWireframe;
  vector<float> modelUniforms;
  array<int, 3>  sceneTranslation;
  array<int, 3>  cameraPosition;
  float cameraDistance;
  array<float, 3>  ofRotation;
  array<int, 3>  lightColor;
  array<float, 3> ofScaler;
  bool translateZero; // whether to zero after each translation (i.e. position state)
  ofLight light;
  bool lightTiedToCamera;
  bool lightOn;
  float ofRotationAngle;

  //    ofMesh mesh;
  //    ofxAssimpModelLoader model;
  //    ofEasyCam camera;

};

//typedef unordered_map<Id, string> Attributes;
//struct ThreeD {
//  int x; int y; int z;
//};
//enum shape3D {SHPERE,CUBE,CYLINDER,MODEL};
//struct opt3D {
//  //    ThreeD translate;
//  //    ThreeD rotate;
//  //    ThreeD scale;
//  // ofMesh* mesh;
//    ofxAssimpModelLoader* model;
//    string modelFile;
//    ofEasyCam* camera;
//    shape3D shape;
//    vector<int> shapePoints;
//  ofTexture tex;
//  string configFilePath;
  // opt3D(ThreeD translate, ThreeD rotate, ThreeD scale, ofMesh* mesh, ofxAssimpModelLoader* model, string modelFile, ofEasyCam* camera, shape3D shape, vector<int> shapePoints, ofTexture tex) {}
  //  opt3D() {
  //    ThreeD translate;
  //    ThreeD rotate;
  //    ThreeD scale;
  //    ofMesh* mesh;
  //    ofxAssimpModelLoader* model;

  //    string modelFile;
  //    ofEasyCam* camera;
  //    shape3D shape;
  //    vector<int> shapePoints;
  //  ofTexture tex;
  //
  //  }

  //  void setMesh(ofMesh* mesh) {
  //    mesh = m;
  //  }
// } ;

  // unordered_map<string, float> modelUniforms;
  // ofxAutoReloadShader modelShader;
//
//class Command {
//public:
//  Action commandType;
//  Id sourceId; // allows us to lookup the shader/whatever to use by string (or int could work)
//  Id arg1; // use ints or strings again to look up shader files, for exmaple
//  Id arg2; // use ints or strings again to look up shader files, for exmaple
//};
