#pragma once
#include "recurnode.h"
#include "ofxAutoReloadedShader.h"
#include "ofMain.h"


void shaderNode::graphSetup(vector<string> ds) {
      for (auto& s: ds) deps.push_back(s);
    }
void shaderNode::setup(){
    //init the params and setup fbo (not sure if needed)
    isActive = true;
    shaderParams = {0, 0, 0, 0};
    paramNum = 0;
    speed = 1;
    time = 0;
    lastElapsedTime = 0;
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();
}

void shaderNode::loadShader(string shaderPath){
    //this method isnt used ??
    shader.load(shaderPath);
}

void shaderNode::loadShaderFiles(string shaderPathFrag, string shaderPathVert){
    shader.load(shaderPathFrag, shaderPathVert, "");
}

ofFbo shaderNode::apply(vector<ofTexture> textures){
    float time = getTime();
    if(isActive){
        fbo.begin();
            shader.begin();
                setDefaultParams(textures, time);
                setAltParams(textures, time);
                if(textures.size() > 0 ){
                    textures[0].draw(0, 0, ofGetWidth(), ofGetHeight());
                }
                else{
                    ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
                }
            shader.end();
        fbo.end();
    }
    else{
        fbo.begin();
            textures[0].draw(0, 0, ofGetWidth(), ofGetHeight());
        fbo.end();
    }
    return fbo;
}

void shaderNode::setDefaultParams(vector<ofTexture> textures, float time){
    shader.setUniform1f("u_time", time);
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    for( int i = 0; i < shaderParams.size(); i = i + 1){
        shader.setUniform1f("u_x" + ofToString(i), shaderParams[i]);
        }
    for( int i = 0; i <  textures.size(); i = i + 1){
        shader.setUniformTexture("u_tex" + ofToString(i), textures[i], i);
    }
}

void shaderNode::setAltParams(vector<ofTexture> textures, float time){
    shader.setUniform1f("ftime", (time) - (long)time);
    shader.setUniform1i("itime", ceil(time));
    shader.setUniform2f("tres", ofGetWidth(), ofGetHeight());
    shader.setUniform4f("fparams", shaderParams[0], shaderParams[1], shaderParams[2], shaderParams[3] );
    shader.setUniform4i("iparams",0,0,0,0);

    for( int i = 0; i <  textures.size(); i = i + 1){
        if(i == 0){
            shader.setUniformTexture("tex", textures[i], i);
        }
        else{
            shader.setUniformTexture("tex" + ofToString(i + 1), textures[i], i);
        }
    }
}

void shaderNode::setSpeed(float value){
    speed = -2.0 + 4.0*value;
}

void shaderNode::setPlay(bool play){
    float time = getTime(); // resets the time diff if stopping and starting
    if(play){ speed = 1; }
    else{ speed = 0; }
}

float shaderNode::getTime(){
    float currentElapsedTime = ofGetElapsedTimef();
    float diff = lastElapsedTime - currentElapsedTime;
    time = time + (speed*diff);
    lastElapsedTime = currentElapsedTime;
    return time;
}
