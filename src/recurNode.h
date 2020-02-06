#pragma once
#include "stdio.h"
#include <vector>
#include <string>
#include "captur.h"
#include "conjur.h"
#include "recurVideoPlayer.h"

//enum fragType {ZERO,ONE,TWO};
//
//class shaderNode  {
//public:
//  ofTexture render(int width, int height, std::vector<ofTexture> textures) {
//    ofLogNotice("at an attempt at rendering") << ofToString(shader.getTime());
//     ofFbo fbo = shader.apply(textures);
//     return fbo.getTexture();
// }
//  fragType inputs;
//  int outEdges;
//  vector<string> deps;
//  vector<string> getDeps() { return deps; };
//  //void setup() {std::cout << "setting up";};
//  shaderNode() {};
//  shaderNode(conjur sh, fragType i, int oe, vector<string> ds) { shader = sh; inputs = i; outEdges = oe; deps = ds; };
//
//  void build(conjur sh, fragType i, int oe, vector<string> ds) { shader = sh; inputs = i; outEdges = oe; deps = ds; };
// conjur shader;
//};

//class recurNode {
//public:
//  virtual ofTexture render(int width, int height, std::vector<ofTexture> textures) = 0;
//  vector<string>* deps;
//  vector<string>* getDeps() { return deps; };
//  //void setup(string file) = 0;
//};
//enum fragType {ZERO,ONE,TWO};
//
//class shaderNode : public recurNode {
//public:
//  ofTexture render(int width, int height, std::vector<ofTexture> textures) {
//     ofFbo fbo = shader.apply(textures);
//     return fbo.getTexture();
// }
//  fragType inputs;
//  int outEdges;
//  // vector<string> deps;
//  //void setup() {std::cout << "setting up";};
//  shaderNode(conjur sh, fragType i, int oe, vector<string>* ds) { shader = sh; inputs = i; outEdges = oe; deps = ds; };
//private: conjur shader;
//};
//
//class videoNode : public recurNode {
//public:
//  ofTexture render(int width, int height, std::vector<ofTexture> textures) {
//    if (player.alpha > 0 && ( player.status == "PLAYING" || player.status == "PAUSED" ) ){
//        player.draw(0, 0, width, height);
//        return player.getTexture();
//  }
//}
//  //void setup() {std::cout << "setting up";};
//  videoNode(recurVideoPlayer pl) { player = pl; };
//  private: recurVideoPlayer player;
//};
//
//class captureNode : public recurNode {
//public:
//  ofTexture render(int width, int height, std::vector<ofTexture> textures) {
//        videoGrabber.draw(0,0, width, height);
//        return videoGrabber.getTexture();
//}
//  //void setup() {std::cout << "setting up";};
//  // captureNode(captur gr) { videoGrabber = gr; };
// private:
//   captur videoGrabber;
//};
//
//class imageNode : public recurNode {
//public:
//  ofTexture render(int width, int height, std::vector<ofTexture> textures) {
//    //     ofPixels pixels = img.getPixels();
//    //     ofTexture outTexture;
//    //     outTexture.loadData(pixels.getData(), pixels.getWidth(), pixels.getHeight(), GL_RGB);
//     img.draw(0, 0, width, height);
//     return img.getTexture();
// }
//  //void setup() {std::cout << "setting up";};
//  imageNode(ofImage im) { img = im; };
//
//private: ofImage img;
//  };
//// maybe `setup` should accept a json object that would be nice
