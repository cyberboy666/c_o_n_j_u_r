#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
    //ofSetFullscreen(1);
    // toggle these for dev mode ?
    ofSetWindowShape(300,200);
    ofSetWindowPosition(50,500);

    receiver.setup(8000);
    sender.setup("localhost", 9000);

    capturePreview = false;
    aStatus = "EMPTY";
    bStatus = "EMPTY";
    cStatus = "EMPTY";
    aAlpha = 255;
    bAlpha = 255;
    cAlpha = 255;
    aEnd = 1;
    bEnd = 1;
    cEnd = 1;
    aStart = 0;
    bStart = 0;
    cStart = 0;
    lastTime = 0;
    useShader = false;
    processShader = false;
    shaderParams[4] = { };
    paramNum = 0;
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
        
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();

}

//--------------------------------------------------------------
void ofApp::update(){

    receiveMessages();
    checkPlayerStatuses();
    checkPlayerPositions();

    fbo.begin();
        ofClear(0, 0, 0, 0);
        if (capturePreview){ // && videoGrabber.isFrameNew()){
            //videoGrabber.draw(0,0,640,480);
            videoGrabber.draw();
            }
            else{
            if ( aStatus == "PLAYING" || aStatus == "PAUSED" ){
                aPlayer.update();
                drawPlayerWithAlpha(aPlayer, aAlpha);
                }
            if ( bStatus == "PLAYING" || bStatus == "PAUSED" ){
                bPlayer.update();
                drawPlayerWithAlpha(bPlayer, bAlpha);
                }
            if ( cStatus == "PLAYING" || cStatus == "PAUSED" ){
                cPlayer.update();
                drawPlayerWithAlpha(cPlayer, cAlpha);
                }
            }
    fbo.end();  
    }

//--------------------------------------------------------------
void ofApp::draw(){
    if(useShader == true){
        shader.begin();
        shader.setUniform1f("u_time", ofGetElapsedTimef());
        shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
        for( int i = 0; i <  paramNum; i = i + 1){
            shader.setUniform1f("x" + i, shaderParams[i]);
            }

        if(true){
            shader.setUniformTexture("u_tex0", fbo.getTexture(), fbo.getTexture().getTextureData().textureID);
        //, aPlayer.getTexture().getTextureData().textureID);
            }

        fbo.draw(0, 0);
        shader.end();
        }
    else{
        fbo.draw(0,0);
        }
    }

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
if (key == 'q'){
        ofExit();
        }
    }


void ofApp::drawPlayerWithAlpha(ofVideoPlayer player, int alpha){
    //if(player.isFrameNew()){
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, alpha);
        player.draw(0, 0, ofGetWidth(), ofGetHeight());
        ofDisableAlphaBlending();
     //   }
}

void ofApp::receiveMessages(){
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/player/a/load"){
            aPlayer.loadAsync(m.getArgAsString(0)); 
            //aPlayer.load(m.getArgAsString(0)); 
            aStart = m.getArgAsFloat(1);
            aEnd = m.getArgAsFloat(2);
            aPlayer.setSpeed(m.getArgAsFloat(3));
            ofLog(OF_LOG_NOTICE, "the start and end are " + ofToString(aStart) + " " + ofToString(aEnd));
            updateStatus("a", "LOADING");
        }
        else if(m.getAddress() == "/player/b/load"){
            bPlayer.loadAsync(m.getArgAsString(0));
            //bPlayer.load(m.getArgAsString(0));
            bStart = m.getArgAsFloat(1);
            bEnd = m.getArgAsFloat(2);
            bPlayer.setSpeed(m.getArgAsFloat(3));
            ofLog(OF_LOG_NOTICE, "the start and end are " + ofToString(bStart) + " " + ofToString(bEnd));
            updateStatus("b", "LOADING");
        }
        else if(m.getAddress() == "/player/c/load"){
            cPlayer.loadAsync(m.getArgAsString(0));
            //cPlayer.load(m.getArgAsString(0));
            cStart = m.getArgAsFloat(1);
            cEnd = m.getArgAsFloat(2);
            cPlayer.setSpeed(m.getArgAsFloat(3));
            ofLog(OF_LOG_NOTICE, "the start and end are " + ofToString(cStart) + " " + ofToString(cEnd));
            updateStatus("c", "LOADING");
        }
        else if(m.getAddress() == "/player/a/play"){
            aPlayer.setPaused(false);
            aAlpha = 255;
            updateStatus("a", "PLAYING");
        }
        else if(m.getAddress() == "/player/b/play"){
            bPlayer.setPaused(false);
            bAlpha = 255;
            updateStatus("b", "PLAYING");
        }
        else if(m.getAddress() == "/player/c/play"){
            cPlayer.setPaused(false);
            cAlpha = 255;
            updateStatus("c", "PLAYING");
        }
        else if(m.getAddress() == "/player/a/pause"){
            aPlayer.setPaused(true);
            updateStatus("a", "PAUSED");
        }
        else if(m.getAddress() == "/player/b/pause"){
            bPlayer.setPaused(true);
            updateStatus("b", "PAUSED");
        }
        else if(m.getAddress() == "/player/c/pause"){
            cPlayer.setPaused(true);
            updateStatus("c", "PAUSED");
        }
        else if(m.getAddress() == "/player/a/alpha"){
            aAlpha = m.getArgAsInt(0);
        }
        else if(m.getAddress() == "/player/b/alpha"){
            bAlpha = m.getArgAsInt(0);
        }
        else if(m.getAddress() == "/player/c/alpha"){
            cAlpha = m.getArgAsInt(0);
        }
        else if(m.getAddress() == "/player/a/position"){
            aPlayer.setPosition(m.getArgAsFloat(0)); // this is a percentage...
        }
        else if(m.getAddress() == "/player/b/position"){
            bPlayer.setPosition(m.getArgAsFloat(0));
        }
        else if(m.getAddress() == "/player/c/position"){
            cPlayer.setPosition(m.getArgAsFloat(0));
        }
        else if(m.getAddress() == "/player/a/speed"){
            aPlayer.setSpeed(m.getArgAsFloat(0));
            ofLog(OF_LOG_NOTICE, "the new speed is " + ofToString(aPlayer.getSpeed()));
        }
        else if(m.getAddress() == "/player/b/speed"){
            bPlayer.setSpeed(m.getArgAsFloat(0));
            ofLog(OF_LOG_NOTICE, "the new speed is " + ofToString(bPlayer.getSpeed()));
        }
        else if(m.getAddress() == "/player/c/speed"){
            cPlayer.setSpeed(m.getArgAsFloat(0));
            ofLog(OF_LOG_NOTICE, "the new speed is " + ofToString(cPlayer.getSpeed()));
        }
        else if(m.getAddress() == "/player/a/quit"){
            aPlayer.stop();
            updateStatus("a", "STOPPED");
            //aPlayer.close();
        }
        else if(m.getAddress() == "/player/b/quit"){
            bPlayer.stop();            
            updateStatus("b", "STOPPED");
            //bPlayer.close();
        }
        else if(m.getAddress() == "/player/c/quit"){
            cPlayer.stop();   
            updateStatus("c", "STOPPED");         
            //cPlayer.close();
        }
        else if(m.getAddress() == "/player/a/get_position"){
            sendFloatMessage("/player/a/position", aPlayer.getPosition());
        }
        else if(m.getAddress() == "/player/b/get_position"){
            sendFloatMessage("/player/b/position", bPlayer.getPosition());
        }
        else if(m.getAddress() == "/player/c/get_position"){
            sendFloatMessage("/player/c/position", cPlayer.getPosition());
        }
        else if(m.getAddress() == "/shader/load"){
            shader.load("/home/pi/Shaders/default.vert",m.getArgAsString(0)); 
            processShader = m.getArgAsBool(1);
            paramNum = m.getArgAsInt(2);

            //shaderParams = { };
        }
        else if(m.getAddress() == "/shader/param"){
            shaderParams[m.getArgAsInt(0)] = m.getArgAsFloat(1);
        }
        else if(m.getAddress() == "/shader/start"){
            useShader = true;
        }
        else if(m.getAddress() == "/shader/stop"){
            useShader = false;
        }
        else if(m.getAddress() == "/capture/preview/start"){
            ofLog(OF_LOG_NOTICE, "starting the capture" );
            setupCapture();
            capturePreview = true;
        }
        else if(m.getAddress() == "/capture/preview/stop"){
            ofLog(OF_LOG_NOTICE, "stopping the capture" );
            videoGrabber.close();
            capturePreview = false;

        }
        else if(m.getAddress() == "/dev_mode"){
            ofLog(OF_LOG_NOTICE, "switching the resolution" );
            if(m.getArgAsBool(0)){
                ofSetFullscreen(0);
                ofSetWindowShape(300,200);
                ofSetWindowPosition(50,500);
                fbo.allocate(ofGetWidth(), ofGetHeight());
                }
            else{
                ofSetFullscreen(1);
                fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
                }
        }
        else if(m.getAddress() == "/exit"){
            ofLog(OF_LOG_NOTICE, "should exit now" );
            ofExit();
        }




    }
}

void ofApp::setupCapture(){
    //omxCameraSettings.width = ofGetWidth();
    //omxCameraSettings.height = ofGetHeight();
    //omxCameraSettings.width = 640;
    //omxCameraSettings.height = 480;
    omxCameraSettings.framerate = 30;
    //omxCameraSettings.enableTexture = true;
    omxCameraSettings.recordingFilePath = "/home/pi/Videos/";
    videoGrabber.setup(omxCameraSettings);
    //videoGrabber.setWhiteBalance("off");
    //videoGrabber.setShutterSpeed(1000);
    //videoGrabber.saveStateToFile();
    videoGrabber.setAutoShutter(false);
    videoGrabber.setExposurePreset("off");
    }

void ofApp::checkPlayerStatuses(){
    //a player
    if( aStatus == "LOADING"){
        if(aPlayer.isLoaded()){
            if(aStart > 0){
                aPlayer.setPaused(false);
                ofLog(OF_LOG_NOTICE, "the playing position is " + ofToString(aPlayer.getPosition()));
                if(aPlayer.getPosition() > 0){
                    aPlayer.setPaused(true);
                    aPlayer.setPosition(aStart);
                    ofLog(OF_LOG_NOTICE, "the position is " + ofToString(aPlayer.getPosition()) + "it should be " + ofToString(aStart));
                    updateStatus("a", "LOADED");
                    }
                }
            else{
                updateStatus("a", "LOADED");
                }
            }
        }
    else if(aStatus == "PLAYING"){
        if(aPlayer.getPosition() > aEnd || aPlayer.getCurrentFrame() > aPlayer.getTotalNumFrames() - 5){
            aPlayer.setPaused(true);
            updateStatus("a", "FINISHED");
            }
        }
    //b player
    if( bStatus == "LOADING"){
        if(bPlayer.isLoaded()){
            if(bStart > 0){
                bPlayer.setPaused(false);
                ofLog(OF_LOG_NOTICE, "the playing position is " + ofToString(bPlayer.getPosition()));
                if(bPlayer.getPosition() > 0){
                    bPlayer.setPaused(true);
                    bPlayer.setPosition(bStart);
                    ofLog(OF_LOG_NOTICE, "the position is " + ofToString(bPlayer.getPosition()) + "it should be " + ofToString(bStart));
                    updateStatus("b", "LOADED");
                    }
                }
            else{
                updateStatus("b", "LOADED");
                }
            }
        }
    else if(bStatus == "PLAYING"){
        if(bPlayer.getPosition() > bEnd || bPlayer.getCurrentFrame() > bPlayer.getTotalNumFrames() - 5){
            bPlayer.setPaused(true);
            //bAlpha = 0;
            updateStatus("b", "FINISHED");
            }
        }
    //c player
    if( cStatus == "LOADING"){
        if(cPlayer.isLoaded()){
            if(cStart > 0){
                cPlayer.setPaused(false);
                ofLog(OF_LOG_NOTICE, "the playing position is " + ofToString(cPlayer.getPosition()));
                if(cPlayer.getPosition() > 0){
                    cPlayer.setPaused(true);
                    cPlayer.setPosition(cStart);
                    ofLog(OF_LOG_NOTICE, "the position is " + ofToString(cPlayer.getPosition()) + "it should be " + ofToString(cStart));
                    updateStatus("c", "LOADED");
                    }
                }
            else{
                updateStatus("c", "LOADED");
                }
            }
        }
    else if(cStatus == "PLAYING"){
        if(cPlayer.getPosition() > cEnd || cPlayer.getCurrentFrame() > cPlayer.getTotalNumFrames() - 5){
            cPlayer.setPaused(true);
            //cAlpha = 0;
            updateStatus("c", "FINISHED");
            }
        }
            
}

void ofApp::updateStatus(string playerName, string status){
    if(playerName == "a"){
        aStatus = status;
        sendStringMessage("/player/a/status", status);
    }
    else if(playerName == "b"){
        bStatus = status;
        sendStringMessage("/player/b/status", status);
    }
    else if(playerName == "c"){
        cStatus = status;
        sendStringMessage("/player/c/status", status);
    }
}

void ofApp::checkPlayerPositions(){
    if((int)ofGetElapsedTimef() > lastTime ){
        if(aStatus == "PLAYING"){
            sendFloatMessage("/player/a/position", aPlayer.getPosition());
        }
        if(bStatus == "PLAYING"){
            sendFloatMessage("/player/b/position", bPlayer.getPosition());
        }
        if(cStatus == "PLAYING"){
            sendFloatMessage("/player/c/position", cPlayer.getPosition());
        }
        lastTime = (int)ofGetElapsedTimef();
    }
}

void ofApp::sendFloatMessage(string address, float value){
    ofxOscMessage response;
    response.setAddress(address);
    response.addFloatArg(value);

    sender.sendMessage(response, true);
}

void ofApp::sendStringMessage(string address, string value){
    ofxOscMessage response;
    response.setAddress(address);
    response.addStringArg(value);

    sender.sendMessage(response, true);
}


