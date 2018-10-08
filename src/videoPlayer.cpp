#include "videoPlayer.h"

void videoPlayer::setup(string nameValue){
    name = nameValue;
    status = "EMPTY";
    alpha = 255;
    end = 1;
    start = 0;
    speed = 1;
}

void videoPlayer::loadPlayer(string pathValue, float startValue, float endValue, float speedValue){
    loadAsync(pathValue); 
    start = startValue;
    end = endValue;
    speed = speedValue;
}
void videoPlayer::playPlayer(){
        setPaused(false);
        alpha = 255;    
}
void videoPlayer::pausePlayer(){
        setPaused(true);
}
void videoPlayer::setSpeedTo(float speedValue){
        if(speedValue == 0){ speed = 0.001;}
        else{speed = speedValue;}
        setSpeed(speed);
        ofLog(OF_LOG_NOTICE, "the player speed is " + ofToString(getSpeed()) + "but it should be " + ofToString(speed));   
}
void videoPlayer::quitPlayer(){
            //stop();
            //close();
}
bool videoPlayer::ifLoading(){
    if( status == "LOADING"){
        if(isLoaded()){
    //get begin point based on direction
            float beginPoint = start;
            if(speed < 0 ){
            //    beginPoint = end;
                }
            setPaused(false);
            ofLog(OF_LOG_NOTICE, "the playing position is " + ofToString(getPosition()));
            if(getPosition() > 0){
                setPaused(true);
                if(beginPoint != 0){setPosition(beginPoint);}
                ofLog(OF_LOG_NOTICE, "the position is " + ofToString(getPosition()) + "it should be " + ofToString(beginPoint));
                //aPlayer.setSpeed(aSpeed);
                //updateStatus("a", "LOADED");
                return true;
                }
            }
        }
return false;
}
bool videoPlayer::ifPlaying(){
    if(status == "PLAYING"){
        //get end point based on direction
        //if(getSpeed() != speed ){setSpeed(speed);}
          
        bool isAtEndPoint;
        if(speed >= 0){
            isAtEndPoint = getPosition() > end || getCurrentFrame() > getTotalNumFrames() - 5;
            }
        else{
            //isAtEndPoint = getPosition() < start || getCurrentFrame() < 5;
            }
        if(isAtEndPoint){
            setPaused(true);
            return true;
            //updateStatus("a", "FINISHED");
            }
        }
return false;
}
