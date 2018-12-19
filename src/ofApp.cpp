#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
    //ofSetFullscreen(1);
    // toggle these for dev mode ?

    setFrameSizeFromFile();

    receiver.setup(8000);
    sender.setup("localhost", 9000);

    hasCapture = false;
    capturePreview = false;
    captureRecord = false;

    aPlayer.setup("a");
    bPlayer.setup("b");
    cPlayer.setup("c");

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
        //ofClear(0, 0, 0, 0);
        if (capturePreview){ // && videoGrabber.isFrameNew()){
            //videoGrabber.draw(0,0,640,480);
            videoGrabber.draw();
            }
        else{
            drawPlayerIfPlayingOrPaused(aPlayer);
            drawPlayerIfPlayingOrPaused(bPlayer);
            drawPlayerIfPlayingOrPaused(cPlayer);
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
            shader.setUniform1f("u_x" + ofToString(i), shaderParams[i]);
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

void ofApp::setFrameSizeFromFile(){

    xmlSettings.loadFile("settings.xml");
    bool isDevMode = xmlSettings.getValue("settings:isDevMode", true);

    if(isDevMode){
        //ofSetFullscreen(0);
        ofSetWindowShape(300,200);
        ofSetWindowPosition(50,500);
        fbo.allocate(ofGetWidth(), ofGetHeight());
        }
    else{
        ofSetFullscreen(1);
        fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight());
        }
}

void ofApp::drawPlayerIfPlayingOrPaused(videoPlayer player){
  
    if ( player.status == "PLAYING" || player.status == "PAUSED" ){
        
        player.update();
        ofEnableAlphaBlending();
        ofSetColor(255, 255, 255, player.alpha);
        player.draw(0, 0, ofGetWidth(), ofGetHeight());
        ofDisableAlphaBlending();
        }
}

void ofApp::receiveMessages(){
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        if(m.getAddress() == "/player/a/load"){
            aPlayer.loadPlayer(m.getArgAsString(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3) );
            updateStatus(aPlayer, "LOADING");
        }
        else if(m.getAddress() == "/player/b/load"){
            bPlayer.loadPlayer(m.getArgAsString(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3) );
            updateStatus(bPlayer, "LOADING");
        }
        else if(m.getAddress() == "/player/c/load"){
            cPlayer.loadPlayer(m.getArgAsString(0), m.getArgAsFloat(1), m.getArgAsFloat(2), m.getArgAsFloat(3) );
            updateStatus(cPlayer, "LOADING");
        }
        else if(m.getAddress() == "/player/a/play"){
            aPlayer.playPlayer();
            updateStatus(aPlayer, "PLAYING");
        }
        else if(m.getAddress() == "/player/b/play"){
            bPlayer.playPlayer();            
            updateStatus(bPlayer, "PLAYING");
        }
        else if(m.getAddress() == "/player/c/play"){
            cPlayer.playPlayer();            
            updateStatus(cPlayer, "PLAYING");
        }
        else if(m.getAddress() == "/player/a/pause"){
            aPlayer.setPaused(true);
            updateStatus(aPlayer, "PAUSED");
        }
        else if(m.getAddress() == "/player/b/pause"){
            bPlayer.setPaused(true);
            updateStatus(bPlayer, "PAUSED");
        }
        else if(m.getAddress() == "/player/c/pause"){
            cPlayer.setPaused(true);
            updateStatus(cPlayer, "PAUSED");
        }
        else if(m.getAddress() == "/player/a/alpha"){
            aPlayer.alpha = m.getArgAsInt(0);
        }
        else if(m.getAddress() == "/player/b/alpha"){
            bPlayer.alpha = m.getArgAsInt(0);
        }
        else if(m.getAddress() == "/player/c/alpha"){
            cPlayer.alpha = m.getArgAsInt(0);
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
            aPlayer.setSpeedTo(m.getArgAsFloat(0));            
            //aSpeed = m.getArgAsFloat(0);
            //aPlayer.setSpeed(aSpeed);
            //ofLog(OF_LOG_NOTICE, "the new speed is " + ofToString(aPlayer.getSpeed()));
        }
        else if(m.getAddress() == "/player/b/speed"){
            bPlayer.setSpeedTo(m.getArgAsFloat(0));            
            //bSpeed = m.getArgAsFloat(0);
            //bPlayer.setSpeed(bSpeed);
            //ofLog(OF_LOG_NOTICE, "the new speed is " + ofToString(bPlayer.getSpeed()));
        }
        else if(m.getAddress() == "/player/c/speed"){
            cPlayer.setSpeedTo(m.getArgAsFloat(0));            
            //cSpeed = m.getArgAsFloat(0);
            //cPlayer.setSpeed(cSpeed);
            //ofLog(OF_LOG_NOTICE, "the new speed is " + ofToString(cPlayer.getSpeed()));
        }
        else if(m.getAddress() == "/player/a/quit"){
            aPlayer.quitPlayer();
            //aPlayer.stop();
            updateStatus(aPlayer, "STOPPED");
            //aPlayer.close();
        }
        else if(m.getAddress() == "/player/b/quit"){
            bPlayer.quitPlayer();            
            //bPlayer.stop();            
            updateStatus(bPlayer, "STOPPED");
            //bPlayer.close();
        }
        else if(m.getAddress() == "/player/c/quit"){
            cPlayer.quitPlayer();            
            //cPlayer.stop();   
            updateStatus(cPlayer, "STOPPED");         
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
        else if(m.getAddress() == "/capture/setup"){
            ofLog(OF_LOG_NOTICE, "setting up the capture type" + m.getArgAsString(0) );
            setupCapture(m.getArgAsString(0));

        }
        else if(m.getAddress() == "/capture/preview/start"){
            if(hasCapture){
                if (!videoGrabber.isReady()){
                    videoGrabber.setup(omxCameraSettings);
                    videoGrabber.reset();
                    }
                ofLog(OF_LOG_NOTICE, "starting the capture" );
                capturePreview = true;
            }
        }
        else if(m.getAddress() == "/capture/preview/stop"){
            if(hasCapture){
            ofLog(OF_LOG_NOTICE, "stopping the capture" );
            capturePreview = false;
            ofLog(OF_LOG_NOTICE, "is ready " +  ofToString((videoGrabber.isReady())));
                if(!captureRecord){
                    ofLog(OF_LOG_NOTICE, "closing the capture" );
                    videoGrabber.close();
                }
            }
        }
        else if(m.getAddress() == "/capture/record/start"){
            if(hasCapture){
            ofLog(OF_LOG_NOTICE, "starting record" );
                videoGrabber.startRecording();
            }
        }
        else if(m.getAddress() == "/capture/record/stop"){
            if(hasCapture){
            ofLog(OF_LOG_NOTICE, "stopping record" );
                videoGrabber.stopRecording();
                if(!capturePreview){
                    //videoGrabber.close();
                }
            }
        }
        else if(m.getAddress() == "/dev_mode"){
            ofLog(OF_LOG_NOTICE, "switching the resolution" );
            xmlSettings.setValue("settings:isDevMode", m.getArgAsBool(0));
            xmlSettings.saveFile("settings.xml");
            setFrameSizeFromFile();
        }
        else if(m.getAddress() == "/exit"){
            ofLog(OF_LOG_NOTICE, "should exit now" );
            ofExit();
        }
    }
}

void ofApp::setupCapture(string captureType){
    //omxCameraSettings.width = ofGetWidth();
    //omxCameraSettings.height = ofGetHeight();
    //omxCameraSettings.width = 640;
    //omxCameraSettings.height = 480;
    //omxCameraSettings.framerate = 30;
    //omxCameraSettings.sensorMode = 5;
    //omxCameraSettings.enableTexture = true;
    omxCameraSettings.recordingFilePath = "/home/pi/Videos/raw.h264";

    videoGrabber.setup(omxCameraSettings);
    if(captureType == "piCaptureSd1"){
        videoGrabber.setWhiteBalance("Off");
        videoGrabber.setWhiteBalanceGains(1,1);
        videoGrabber.setExposurePreset("off");
    }
    //videoGrabber.setShutterSpeed(1000);
    //videoGrabber.saveStateToFile();
    //videoGrabber.setAutoShutter(false);
    //videoGrabber.getSensorMode();
    //videoGrabber.getSensorModeAgain();

    videoGrabber.reset();
    ofLog(OF_LOG_NOTICE, "the videoGrabber state is " + ofToString(videoGrabber.isReady()) );
    if(videoGrabber.isReady()){
        hasCapture = true;
        }
    sendFloatMessage("/capture/is_setup", hasCapture );

    }

void ofApp::checkPlayerStatuses(){
    bool aIsLoaded = aPlayer.ifLoading();
    if(aIsLoaded){updateStatus(aPlayer, "LOADED");}
    bool bIsLoaded = bPlayer.ifLoading();
    if(bIsLoaded){updateStatus(bPlayer, "LOADED");}
    bool cIsLoaded = cPlayer.ifLoading();
    if(cIsLoaded){updateStatus(cPlayer, "LOADED");}

    bool aIsFinished = aPlayer.ifPlaying();
    if(aIsFinished){updateStatus(aPlayer, "FINISHED");}
    bool bIsFinished = bPlayer.ifPlaying();
    if(bIsFinished){updateStatus(bPlayer, "FINISHED");}
    bool cIsFinished = cPlayer.ifPlaying();
    if(cIsFinished){updateStatus(cPlayer, "FINISHED");}
}

void ofApp::updateStatus(videoPlayer& player, string statusValue){
    player.status = statusValue;
    sendStringMessage("/player/" + player.name + "/status", statusValue);
    }

void ofApp::checkPlayerPositions(){
    if((int)ofGetElapsedTimef() > lastTime ){
        if(aPlayer.status == "PLAYING"){
            sendFloatMessage("/player/a/position", aPlayer.getPosition());
        }
        if(bPlayer.status == "PLAYING"){
            sendFloatMessage("/player/b/position", bPlayer.getPosition());
        }
        if(cPlayer.status == "PLAYING"){
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


