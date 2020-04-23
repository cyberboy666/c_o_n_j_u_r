#pragma once

#include "ofMain.h"
#include "ofxAutoReloadedShader.h"

enum fragType {ZERO,ONE,TWO};
class shaderNode{

    public:
        void setup();
    void graphSetup(vector<string> ds);
    void loadShader(string shaderPath);
        void loadShaderFiles(string shaderPathFrag, string shaderPathVert);
        void setSpeed(float value);
        void setPlay(bool play);
        float getTime();
        void setDefaultParams(vector<ofTexture> textures, float time);
        void setAltParams(vector<ofTexture> textures, float time);
        ofFbo apply(vector<ofTexture> textures);
        fragType inputs;
        int outEdges;
        vector<string> deps;
        vector<string> getDeps() { return deps; };

    ofxAutoReloadedShader shader;
    ofFbo fbo;
    vector<float> shaderParams;
    float speed;
    float time;
    float lastElapsedTime;
    int paramNum;
    bool isActive;

};
