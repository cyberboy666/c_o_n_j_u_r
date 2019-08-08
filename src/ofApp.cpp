#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
	ofBackground(0, 0, 0);
	ofSetVerticalSync(false);
    ofHideCursor();    
    //ofSetFullscreen(1);
    // toggle these for dev mode ?
    framerate = 30;
    ofSetFrameRate(framerate);


    setFrameSizeFromFile();

    receiver.setup(8000);
    sender.setup("localhost", 9000);

    hasCapture = false;
    captureType = "";
    capturePreview = false;
    captureRecord = false;

    aPlayer.setup(playerType, "a");
    bPlayer.setup(playerType, "b");
    cPlayer.setup(playerType, "c");

    lastTime = 0;
    useShader = false;
    processShader = false;
    // detour demo
    isDetour = false;
    effectShaderInput = false;
    thisDetour.setup();

    mixConjur.setup();
    mixConjur.shaderParams[0] = 0.5;
    effectConjur.setup();
    effectInput = {};
    
    in_texture.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    detour_texture.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);

    in_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);    
    out_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    mix_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
        
    fbo.begin();
        ofClear(0, 0, 0, 0);
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    receiveMessages();
    checkPlayerStatuses();
    checkPlayerPositions();

    aPlayer.update();
    bPlayer.update();
    cPlayer.update();
    videoGrabber.update();

    }

//--------------------------------------------------------------
void ofApp::draw(){

    if(!isDetour){
        if(useShader){
            effectInput = {};
            drawCaptureAndPlayers();
            fbo = effectConjur.apply(effectInput);
             }
        else{
             fbo.begin();
                drawCaptureAndPlayers();
             fbo.end();
        }
    fbo.draw(0,0,ofGetWidth(), ofGetHeight());
    }
    else{
        if(useShader && effectShaderInput){
            effectInput = {};
            drawCaptureAndPlayers();
            fbo = effectConjur.apply(effectInput);
             }
        else{
             fbo.begin();
                drawCaptureAndPlayers();
             fbo.end();
        }
    detourUpdate();
    out_fbo.draw(0,0,ofGetWidth(), ofGetHeight());
    }
}

void ofApp::detourUpdate(){
    fbo.readToPixels(in_frame);
    in_frame.resize(ofGetWidth(), ofGetHeight());
    detour_frame = thisDetour.getFrame();

    in_texture.loadData(in_frame.getData(), in_frame.getWidth(), in_frame.getHeight(), GL_RGB);
    detour_texture.loadData(detour_frame.getData(), detour_frame.getWidth(), detour_frame.getHeight(), GL_RGB);

    vector<ofTexture> mixInput = {in_texture, detour_texture};
    mix_fbo = mixConjur.apply(mixInput);
    if(useShader && !effectShaderInput){
        ofTexture mix_texture = mix_fbo.getTexture();
        vector<ofTexture> effectInput = {mix_texture};
        out_fbo = effectConjur.apply(effectInput);
    }

    else{out_fbo = mix_fbo;}
    if(thisDetour.is_recording){
        out_fbo.readToPixels(out_frame);
        thisDetour.checkMemory();
        thisDetour.addFrame(out_frame); 
        }
}

//--------------------------------------------------------------

void ofApp::drawCaptureAndPlayers(){
    if (capturePreview){ // && videoGrabber.isFrameNew()){
        if(useShader){ 
            effectInput.push_back(videoGrabber.getTexture());
            //ofLog() << "capture is texture " << effectInput.size(); 
        }
    }
 
    drawPlayerIfPlayingOrPaused(cPlayer);
    drawPlayerIfPlayingOrPaused(bPlayer);
    drawPlayerIfPlayingOrPaused(aPlayer);
if (capturePreview){
        videoGrabber.draw(0,0,ofGetWidth(), ofGetHeight());
    }
}

void ofApp::keyPressed(int key){
if (key == 'q'){
        ofExit();
        }
    }

void ofApp::setFrameSizeFromFile(){

    xmlSettings.loadFile("settings.xml");
    playerType = xmlSettings.getValue("settings:playerType", "");
    bool isDevMode = xmlSettings.getValue("settings:isDevMode", true);

    if(isDevMode){
        ofSetFullscreen(0);
        ofSetWindowShape(600,400);
        ofSetWindowPosition(50,500);
        fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
        
        }
    else{
        ofSetFullscreen(1);
        fbo.allocate(ofGetScreenWidth(), ofGetScreenHeight(), GL_RGB);
        
        //fbo.allocate(640, 480);
        }
}

void ofApp::drawPlayerIfPlayingOrPaused(recurVideoPlayer& player){
  
    if (player.alpha > 0 && ( player.status == "PLAYING" || player.status == "PAUSED" ) ){
        player.draw(0, 0, ofGetWidth(), ofGetHeight());
        if(useShader && effectInput.size() < 2){
            effectInput.push_back(player.getTexture());
            //ofLog() << "player " << player.name << " is texture " << effectInput.size();
            }
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
            aPlayer.pausePlayer();
            updateStatus(aPlayer, "PAUSED");
        }
        else if(m.getAddress() == "/player/b/pause"){
            bPlayer.pausePlayer();
            updateStatus(bPlayer, "PAUSED");
        }
        else if(m.getAddress() == "/player/c/pause"){
            cPlayer.pausePlayer();
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
            effectConjur.loadShaderFiles("/home/pi/r_e_c_u_r/Shaders/default.vert", m.getArgAsString(0));
            processShader = m.getArgAsBool(1);
            }
        else if(m.getAddress() == "/shader/param"){
            effectConjur.shaderParams[m.getArgAsInt(0)] = m.getArgAsFloat(1);
        }
        else if(m.getAddress() == "/shader/start"){
            useShader = true;
        }
        else if(m.getAddress() == "/shader/stop"){
            useShader = false;
        }
        else if(m.getAddress() == "/capture/setup"){
            ofLog(OF_LOG_NOTICE, "setting up the capture type" + m.getArgAsString(0) );
            captureType = m.getArgAsString(0);

        }
        else if(m.getAddress() == "/capture/preview/start"){

            ofLog(OF_LOG_NOTICE, "the videoGrabber state is " + ofToString(videoGrabber.isReady()) );
            if (!videoGrabber.isReady()){
                videoGrabber.setup(captureType, ofGetWidth(), ofGetHeight(), framerate);
                //videoGrabber.reset();
                }
            ofLog(OF_LOG_NOTICE, "starting the capture" );
            //videoGrabber.printSensorModesInfo();
            //videoGrabber.PrintSensorModes(videoGrabber.engine.camera);
            capturePreview = true;
        }

        else if(m.getAddress() == "/capture/preview/stop"){

            ofLog(OF_LOG_NOTICE, "stopping the capture" );
            capturePreview = false;
            ofLog(OF_LOG_NOTICE, "is ready " +  ofToString((videoGrabber.isReady())));
                if(!captureRecord){
                    ofLog(OF_LOG_NOTICE, "closing the capture" );
                    videoGrabber.close();
                }
            }

        else if(m.getAddress() == "/capture/record/start"){
            if (!videoGrabber.isReady()){
                videoGrabber.setup(captureType, ofGetWidth(), ofGetHeight(), framerate);
                //videoGrabber.reset();
                }
            ofLog(OF_LOG_NOTICE, "starting the capture" );
            ofLog(OF_LOG_NOTICE, "starting record" );
                videoGrabber.startRecording();
            }
        else if(m.getAddress() == "/capture/record/stop"){

            ofLog(OF_LOG_NOTICE, "stopping record" );
                videoGrabber.stopRecording();
            ofLog(OF_LOG_NOTICE, "stopped record" );
            while(videoGrabber.isRecording()){
                //wait for video to stop before closing;
            }
            ofLog() << "sending the message that it is done now";
            sendFloatMessage("/capture/recording_finished", 0.0);
            if(!capturePreview){videoGrabber.close();}
            }
        else if(m.getAddress() == "/detour/start"){
                ofLog() << "detour on !";
                effectShaderInput = m.getArgAsBool(0);
                isDetour = true;
            }
        else if(m.getAddress() == "/detour/end"){
                ofLog() << "detour off !";
                isDetour = false;
            }
        else if(m.getAddress() == "/detour/is_playing"){
                thisDetour.is_playing = m.getArgAsBool(0);
            }
        else if(m.getAddress() == "/detour/is_recording"){
                ofLog() << "it is setting recording to " << m.getArgAsBool(0); 
                thisDetour.is_recording = m.getArgAsBool(0);
            }
        else if(m.getAddress() == "/detour/record_loop"){
                thisDetour.record_loop = m.getArgAsBool(0);
            }
        else if(m.getAddress() == "/detour/clear_this_detour"){
                thisDetour.detour_start = 0;
                thisDetour.detour_end = 0;
                thisDetour.detour_position_part = 0;
                thisDetour.detour_position = 0;
                thisDetour.detours[thisDetour.current_detour].clear();
            }
        else if(m.getAddress() == "/detour/set_speed_position"){
                float value = m.getArgAsFloat(0);
                if(thisDetour.is_playing){thisDetour.setSpeed(value);}
                else {thisDetour.setPosition(value);}
            }
        else if(m.getAddress() == "/detour/set_start"){
                thisDetour.setStart(m.getArgAsFloat(0));
             }
        else if(m.getAddress() == "/detour/set_end"){
                thisDetour.setEnd(m.getArgAsFloat(0));
             }
        else if(m.getAddress() == "/detour/set_mix"){
                thisDetour.mix_position = m.getArgAsFloat(0);
                mixConjur.shaderParams[0] = thisDetour.mix_position;
             }
        else if(m.getAddress() == "/detour/switch_to_detour_number"){
                thisDetour.current_detour = m.getArgAsInt(0);
                thisDetour.detour_start = 0;
                thisDetour.detour_end = 0;
                thisDetour.detour_position = 0;
                thisDetour.detour_position_part = 0;
             }
        else if(m.getAddress() == "/detour/load_mix"){
                mixConjur.loadShaderFiles("/home/pi/r_e_c_u_r/Shaders/default.vert", m.getArgAsString(0));
             }
        else if(m.getAddress() == "/dev_mode"){
            ofLog(OF_LOG_NOTICE, "switching the resolution" );
            setFrameSizeFromFile();
        }
        else if(m.getAddress() == "/exit"){
            ofLog(OF_LOG_NOTICE, "should exit now" );
            ofExit();
        }
    }
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

void ofApp::updateStatus(recurVideoPlayer& player, string statusValue){
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
        if(isDetour){
            sendDetourMessage(thisDetour.detour_position, thisDetour.detour_start, thisDetour.detour_end, thisDetour.detours[thisDetour.current_detour].size(), thisDetour.detour_speed, thisDetour.mix_position, thisDetour.memory_full);
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

void ofApp::sendDetourMessage(int position, int start, int end, int size, float speed, float mix, bool memory_full ){
    ofxOscMessage response;
    response.setAddress("/detour/detour_info");
    response.addIntArg(position);
    response.addIntArg(start);
    response.addIntArg(end);
    response.addIntArg(size);
    response.addFloatArg(speed);
    response.addFloatArg(mix);
    response.addBoolArg(memory_full);

    sender.sendMessage(response, true);
}

