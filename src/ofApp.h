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
// #inlucde "ofxAutoReloadShader"
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
struct ThreeD {
  int x; int y; int z;
};
enum shape3D {SHPERE,CUBE,CYLINDER,MODEL};  
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
// unordered_map<string, float>  shaderUniformsF;
// unordered_map<string, bool>  shaderUniformsB;
enum Action {LOAD_FILE, NOTHING, UPDATE_UNIFORM, ROTATE, TOGGLE_ACTIVE };
typedef unordered_map<Id, ofxNode> Nodemap;
typedef unordered_map<Id, Action> actionMap;
// shaderMap shaders;
// typedef unordered_map<Id, ofxAutoReloadedShader> shaderMap;
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
  void setup3D(); 
  ofTexture modelTex; 
  string sceneConfigPath;
  ofxJSONElement sceneConfig;
  ofMesh mesh;
  ofxAssimpModelLoader model;
  ofEasyCam camera;
  ofxAutoReloadedShader modelShader;
  bool use3D;
  bool modelWireframe;
  vector<float> modelUniforms;
  // unordered_map<string, float> modelUniforms; 
  // ofxAutoReloadShader modelShader;
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
  // unordered_map<Id 
    vector<int> nodeOrder;
    ofxOscReceiver receiver;
    ofxOscSender sender;
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
  // unordered_map<int, conjur> shaderMap;
    vector<conjur> shaderMap;
  //    conjur effectShader0;
  //    conjur effectShader1;
  //    conjur effectShader2;
  //    bool effectShader0active;
  //    bool effectShader1active;
  //    bool effectShader2active;

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

  //    ofMesh mesh;
  //    ofxAssimpModelLoader model;
  //    ofEasyCam camera;

};
