#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
    //ofSetFullscreen(0);
    // toggle these for dev mode ?
    ofSetWindowShape(300,200);
    ofSetWindowPosition(50,500);

    receiver.setup(8000);
    sender.setup("localhost", 9000);


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
	//Uncomment this to show movies with alpha channels
	//aPlayer.setPixelFormat(OF_PIXELS_RGBA);
    
    fbo.allocate(ofGetWidth(), ofGetHeight());
        
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();

    //nowShader.load("shaderExample");

    


}

//--------------------------------------------------------------
void ofApp::update(){

    receiveMessages();
    checkPlayerStatuses();
    checkPlayerPositions();

    fbo.begin();
        ofClear(0, 0, 0, 0);
        //nowShader.begin();
        //    nowShader.setUniformTexture("tex0", aPlayer.getTexture(), 0);//, aPlayer.getTexture().getTextureData().textureID);
        //    nowShader.setUniform1f("time", ofGetElapsedTimef());
        //    nowShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
            if ( aStatus == "PLAYING" || aStatus == "PAUSED" ){
                aPlayer.update();
                bPlayer.update();
                cPlayer.update();
                drawPlayerWithAlpha(aPlayer, aAlpha);
                }
            if ( bStatus == "PLAYING" || bStatus == "PAUSED" ){
                aPlayer.update();
                bPlayer.update();
                cPlayer.update();
                drawPlayerWithAlpha(bPlayer, bAlpha);
                }
            if ( cStatus == "PLAYING" || cStatus == "PAUSED" ){
                aPlayer.update();
                bPlayer.update();
                cPlayer.update();
                drawPlayerWithAlpha(cPlayer, cAlpha);
                }
              
            //}
        //nowShader.end();            
    fbo.end();  
}

//--------------------------------------------------------------
void ofApp::draw(){
    fbo.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
if (key == 'q'){
        ofExit();
    }
}


void ofApp::drawPlayerWithAlpha(ofVideoPlayer player, int alpha){
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, alpha);
    player.draw(0, 0, ofGetWidth(), ofGetHeight());
    ofDisableAlphaBlending();
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
            ofLog(OF_LOG_NOTICE, "the start and end are " + ofToString(aStart) + " " + ofToString(aEnd));
            updateStatus("a", "LOADING");
        }
        else if(m.getAddress() == "/player/b/load"){
            bPlayer.loadAsync(m.getArgAsString(0));
            //bPlayer.load(m.getArgAsString(0));
            bStart = m.getArgAsFloat(1);
            bEnd = m.getArgAsFloat(2);
            ofLog(OF_LOG_NOTICE, "the start and end are " + ofToString(bStart) + " " + ofToString(bEnd));
            updateStatus("b", "LOADING");
        }
        else if(m.getAddress() == "/player/c/load"){
            cPlayer.loadAsync(m.getArgAsString(0));
            //cPlayer.load(m.getArgAsString(0));
            cStart = m.getArgAsFloat(1);
            cEnd = m.getArgAsFloat(2);
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



    }
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
        if(aPlayer.getPosition() > aEnd - 0.1){
            aPlayer.setPaused(true);
            //aAlpha = 0;
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
        if(bPlayer.getPosition() > bEnd - 0.1){
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
        if(cPlayer.getPosition() > cEnd - 0.1){
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


