#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    

    receiver.setup(8000);
    sender.setup("localhost", 9000);


    aStatus = "EMPTY";
    bStatus = "EMPTY";
    cStatus = "EMPTY";
    aAlpha = 255;
    bAlpha = 255;
    cAlpha = 255;
    aEnd = 0.99;
    bEnd = 0.99;
    cEnd = 0.99;
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
//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}


//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

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
            updateStatus("a", "LOADING");
        }
        else if(m.getAddress() == "/player/b/load"){
            bPlayer.loadAsync(m.getArgAsString(0));
            updateStatus("b", "LOADING");
        }
        else if(m.getAddress() == "/player/c/load"){
            cPlayer.loadAsync(m.getArgAsString(0));
            updateStatus("c", "LOADING");
        }
        else if(m.getAddress() == "/player/a/play"){
            aPlayer.setPaused(! m.getArgAsBool(0));
            if (m.getArgAsBool(0)){
                aAlpha = 255;
                updateStatus("a", "PLAYING");
            }
            else{
                updateStatus("a", "PAUSED");
            }
        }
        else if(m.getAddress() == "/player/b/play"){
            bPlayer.setPaused(! m.getArgAsBool(0));
            if (m.getArgAsBool(0)){
                bAlpha = 255;
                updateStatus("b", "PLAYING");
            }
            else{
                updateStatus("b", "PAUSED");
            }
        }
        else if(m.getAddress() == "/player/c/play"){
            cPlayer.setPaused(! m.getArgAsBool(0));
            if (m.getArgAsBool(0)){
                cAlpha = 255;
                updateStatus("c", "PLAYING");
            }
            else{
                updateStatus("c", "PAUSED");
            }
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
            //aPlayer.setPosition(aStart);
            updateStatus("a", "LOADED");
            }
        }
    else if(aStatus == "PLAYING"){
        if(aPlayer.getPosition() > aEnd){
            aPlayer.setPaused(true);
            //aAlpha = 0;
            updateStatus("a", "FINISHED");
            }
        }
    //b player
    if( bStatus == "LOADING"){
        if(bPlayer.isLoaded()){
            updateStatus("b", "LOADED");
            }
        }
    else if(bStatus == "PLAYING"){
        if(bPlayer.getPosition() > bEnd){
            bPlayer.setPaused(true);
            //bAlpha = 0;
            updateStatus("b", "FINISHED");
            }
        }
    //c player
    if( cStatus == "LOADING"){
        if(cPlayer.isLoaded()){
            updateStatus("c", "LOADED");
            }
        }
    else if(cStatus == "PLAYING"){
        if(cPlayer.getPosition() > cEnd){
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


